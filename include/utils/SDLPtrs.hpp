#pragma once

#include <SDL2/SDL.h>
#include <memory>

struct WindowDeleter {
  void operator()(SDL_Window* p) const {
    if (p)
      SDL_DestroyWindow(p);
  }
};

struct RendererDeleter {
  void operator()(SDL_Renderer* p) const {
    if (p)
      SDL_DestroyRenderer(p);
  }
};

struct TextureDeleter {
  void operator()(SDL_Texture* p) const {
    if (p)
      SDL_DestroyTexture(p);
  }
};

using WindowPtr = std::unique_ptr<SDL_Window, WindowDeleter>;
using RendererPtr = std::unique_ptr<SDL_Renderer, RendererDeleter>;
using TexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;