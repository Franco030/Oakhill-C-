#pragma once

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

  bool isRunning;

  SDL_Window* window;
  SDL_Renderer* renderer;
};