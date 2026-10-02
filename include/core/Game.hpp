#pragma once

#include "entities/Player.hpp"
#include <SDL2/SDL.h>

class Game {
public:
  Game();
  ~Game();

  void run();

private:
  void handleEvents();
  void update(float deltaTime);
  void render();
  void clean();

  Player* player;

  bool isRunning;

  SDL_Window* window;
  SDL_Renderer* renderer;
};