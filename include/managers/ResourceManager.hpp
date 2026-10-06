#pragma once

#include "utils/SDLPtrs.hpp"
#include <string>
#include <unordered_map>

class ResourceManager {
public:
  static SDL_Texture* loadTexture(const std::string& id, const std::string& path,
                                  SDL_Renderer* renderer);
  static SDL_Texture* getTexture(const std::string& id);
  static void clean();

private:
  static std::unordered_map<std::string, TexturePtr> textures;
};