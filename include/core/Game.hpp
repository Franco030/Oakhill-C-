#pragma once

#include "utils/SDLPtrs.hpp"
#include <memory>

class Player;

class Game {
public:
  Game();
  ~Game();

  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  void run();

private:
  void handleEvents();
  void update(float deltaTime);
  void render();
  void toggleFullscreen();

  WindowPtr window;
  RendererPtr renderer;
  std::unique_ptr<Player> player;

  bool isRunning = false;
  bool isFullscreen = true;
};