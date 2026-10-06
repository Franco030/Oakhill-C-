#include "entities/Player.hpp"
#include "managers/ResourceManager.hpp"
#include "utils/Constants.hpp"

Player::Player(float startX, float startY) {
  position = Vector2D(startX, startY);
  texture = ResourceManager::getTexture("spr_player");
  speed = Constants::PLAYER_SPEED;

  destRect = {static_cast<int>(position.x), static_cast<int>(position.y), 0, 0};

  if (texture) {
    int width = 0;
    int height = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    destRect.w = static_cast<int>(width * Constants::RESIZE_FACTOR);
    destRect.h = static_cast<int>(height * Constants::RESIZE_FACTOR);
  }
}

Player::~Player() {}

void Player::update(float deltaTime) {
  const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

  Vector2D direction(0.0f, 0.0f);

  if (currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_UP]) {
    direction.y -= 1.0f;
  }
  if (currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_DOWN]) {
    direction.y += 1.0f;
  }
  if (currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_LEFT]) {
    direction.x -= 1.0f;
  }
  if (currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_RIGHT]) {
    direction.x += 1.0f;
  }

  direction.normalize();

  position = position + (direction * speed * deltaTime);

  destRect.x = (int)position.x;
  destRect.y = (int)position.y;
}

void Player::render(SDL_Renderer* renderer) {
  if (texture) {
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
  }
}