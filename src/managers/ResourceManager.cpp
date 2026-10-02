#include "managers/ResourceManager.hpp"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> ResourceManager::textures;

SDL_Texture* ResourceManager::loadTexture(const std::string& id, const std::string& path,
                                          SDL_Renderer* renderer) {
  if (textures.find(id) != textures.end()) {
    return textures[id];
  }

  SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());

  if (newTexture == nullptr) {
    std::cerr << "Error cargando textura '" << id << "' desde '" << path << "': " << IMG_GetError()
              << '\n';
  } else {
    textures[id] = newTexture;
    std::cout << "Textura cargada con exito: " << id << '\n';
  }

  return newTexture;
}

SDL_Texture* ResourceManager::getTexture(const std::string& id) {
  if (textures.find(id) != textures.end()) {
    return textures[id];
  }

  std::cerr << "Advertencia: Se solicito textura no encontrada: " << id << '\n';
  return nullptr;
}

void ResourceManager::clean() {
  for (auto const& [id, texture] : textures) {
    SDL_DestroyTexture(texture);
  }

  textures.clear();
  std::cout << "Recursos limpiados de la memoria.\n";
}