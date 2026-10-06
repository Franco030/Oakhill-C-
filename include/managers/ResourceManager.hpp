#pragma once

#include "utils/SDLPtrs.hpp"
#include <string>
#include <unordered_map>

class ResourceManager {
public:
  static void init(SDL_Renderer* renderer);
  static void loadManifest();

  static SDL_Texture* getTexture(const std::string& id);
  static void clean();

private:
  static SDL_Texture* loadFromDisk(const std::string& path);
  static SDL_Texture* placeholder();

  static SDL_Renderer* renderer;
  static std::unordered_map<std::string, std::string> assetMap;
  static std::unordered_map<std::string, TexturePtr> textures;
};