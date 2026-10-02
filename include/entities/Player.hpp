#pragma once

#include "utils/Vector2D.hpp"
#include <SDL2/SDL.h>
#include <string>

class Player {
public:
  Player(float startX, float startY);
  ~Player();

  void update(float deltaTime);
  void render(SDL_Renderer* renderer);

  Vector2D position;

private:
  SDL_Texture* texture;
  SDL_Rect destRect;

  float speed;
};