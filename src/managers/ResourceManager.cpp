#include "managers/ResourceManager.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

std::unordered_map<std::string, TexturePtr> ResourceManager::textures;

SDL_Texture* ResourceManager::loadTexture(const std::string& id, const std::string& path,
                                          SDL_Renderer* renderer) {
  if (auto it = textures.find(id); it != textures.end()) {
    return it->second.get();
  }

  SDL_Texture* raw = IMG_LoadTexture(renderer, path.c_str());
  if (!raw) {
    std::cerr << "Error cargando textura '" << id << "' desde '" << path << "': " << IMG_GetError()
              << '\n';
    return nullptr;
  }

  textures.emplace(id, TexturePtr(raw));
  std::cout << "Textura cargada con exito: " << id << '\n';
  return raw;
}

SDL_Texture* ResourceManager::getTexture(const std::string& id) {
  if (auto it = textures.find(id); it != textures.end()) {
    return it->second.get();
  }

  std::cerr << "Advertencia: Se solicito textura no encontrada: " << id << '\n';
  return nullptr;
}

void ResourceManager::clean() {
  textures.clear();
  std::cout << "Recursos limpiados de la memoria.\n";
}