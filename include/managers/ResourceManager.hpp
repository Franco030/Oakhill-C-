#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>

class ResourceManager {
public:
  static SDL_Texture* loadTexture(const std::string& id, const std::string& path,
                                  SDL_Renderer* renderer);
  static SDL_Texture* getTexture(const std::string& id);
  static void clean();

private:
  static std::unordered_map<std::string, SDL_Texture*> textures;
};