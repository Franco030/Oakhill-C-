#include "core/Game.hpp"
#include "managers/ResourceManager.hpp"
#include "utils/Constants.hpp"
#include <iostream>

Game::Game() {
  isRunning = false;
  window = nullptr;
  renderer = nullptr;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Error inicializando SDL: " << SDL_GetError() << '\n';
    return;
  }

  window = SDL_CreateWindow("Oakhill", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "Error creando la ventana: " << SDL_GetError() << '\n';
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    std::cerr << "Error creando el renderer: " << SDL_GetError() << '\n';
  }

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    std::cerr << "Error inicializando SDL_Image: " << IMG_GetError() << '\n';
  }

  ResourceManager::loadTexture("spr_player", "assets/images/detective.png", renderer);

  player = new Player(100.0f, 100.0f);

  isRunning = true;
}

Game::~Game() { clean(); }

void Game::run() {
  Uint32 lastTime = SDL_GetTicks();

  while (isRunning) {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    handleEvents();
    update(deltaTime);
    render();
  }
}

void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
    }
  }
}

void Game::update(float deltaTime) {
  if (player) {
    player->update(deltaTime);
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  if (player) {
    player->render(renderer);
  }

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);

  if (player) {
    delete player;
    player = nullptr;
  }

  ResourceManager::clean();

  IMG_Quit();
  SDL_Quit();
  std::cout << "Juego cerrado correctamente.\n";
}