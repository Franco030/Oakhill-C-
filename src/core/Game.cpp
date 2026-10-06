#include "core/Game.hpp"
#include "entities/Player.hpp"
#include "managers/ResourceManager.hpp"
#include "utils/Constants.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <iostream>

Game::Game() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cerr << "Error inicializando SDL: " << SDL_GetError() << '\n';
    return;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

  window.reset(
      SDL_CreateWindow("Oakhill", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT,
                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP));

  if (!window) {
    std::cerr << "Error creando la ventana: " << SDL_GetError() << '\n';
    return;
  }

  renderer.reset(
      SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  if (!renderer) {
    std::cerr << "Error creando el renderer: " << SDL_GetError() << '\n';
    return;
  }

  SDL_RenderSetLogicalSize(renderer.get(), Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
  SDL_RenderSetIntegerScale(renderer.get(), SDL_FALSE);
  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "Error inicializando SDL_Image: " << IMG_GetError() << '\n';
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "Error inicializando SDL_Mixer: " << Mix_GetError() << '\n';
  }

  if (TTF_Init() < 0) {
    std::cerr << "Error inicializando SDL_ttf: " << TTF_GetError() << '\n';
  }

  ResourceManager::loadTexture("spr_player", "assets/images/detective.png", renderer.get());
  player = std::make_unique<Player>(100.0f, 100.0f);

  isRunning = true;
}

Game::~Game() {
  player.reset();
  ResourceManager::clean();

  TTF_Quit();
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
  std::cout << "Juego cerrado correctamente.\n";
}

void Game::run() {
  Uint32 lastTime = SDL_GetTicks();

  while (isRunning) {
    const Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    deltaTime = std::min(deltaTime, Constants::MAX_DELTA_TIME);

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
    } else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      if (event.key.keysym.sym == SDLK_F11) {
        toggleFullscreen();
      }
    }
  }
}

void Game::toggleFullscreen() {
  isFullscreen = !isFullscreen;
  SDL_SetWindowFullscreen(window.get(), isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void Game::update(float deltaTime) {
  if (player) {
    player->update(deltaTime);
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderer.get());

  if (player) {
    player->render(renderer.get());
  }

  SDL_RenderPresent(renderer.get());
}