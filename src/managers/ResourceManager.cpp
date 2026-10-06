#include "managers/ResourceManager.hpp"
#include "utils/Paths.hpp"

#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>

SDL_Renderer* ResourceManager::renderer = nullptr;
std::unordered_map<std::string, std::string> ResourceManager::assetMap;
std::unordered_map<std::string, TexturePtr> ResourceManager::textures;

void ResourceManager::init(SDL_Renderer* r) { renderer = r; }

void ResourceManager::loadManifest() {
  const std::string path = Paths::resource("data/database/assets.json");

  std::ifstream file(path);
  if (!file) {
    std::cerr << "[ResourceManager] WARNING: Manifest not found at " << path << '\n';
    return;
  }

  nlohmann::json data;
  try {
    file >> data;
  } catch (const std::exception& e) {
    std::cerr << "[ResourceManager] Error loading manifest: " << e.what() << '\n';
    return;
  }

  static const char* categories[] = {"SPRITES", "ANIMATIONS", "SFX", "AMBIENCE", "MUSIC"};
  for (const char* category : categories) {
    if (!data.contains(category)) {
      continue;
    }
    for (auto& [id, value] : data[category].items()) {
      assetMap[id] = value.get<std::string>();
    }
  }

  std::cout << "[ResourceManager] Manifest loaded. " << assetMap.size() << " assets registered.\n";
}

SDL_Texture* ResourceManager::getTexture(const std::string& keyOrPath) {
  if (keyOrPath.empty() || keyOrPath == "None") {
    return nullptr;
  }

  auto it = assetMap.find(keyOrPath);
  const std::string& realPath = (it != assetMap.end()) ? it->second : keyOrPath;

  if (auto cached = textures.find(realPath); cached != textures.end()) {
    return cached->second.get();
  }

  const std::string fullPath = Paths::resource(realPath);
  if (!std::filesystem::exists(fullPath)) {
    std::cerr << "[ResourceManager] Error: File not found '" << fullPath << "' (Key: " << keyOrPath
              << ")\n";
    return placeholder();
  }

  SDL_Texture* loaded = loadFromDisk(fullPath);
  if (!loaded) {
    return placeholder();
  }

  textures.emplace(realPath, TexturePtr(loaded));
  return loaded;
}

SDL_Texture* ResourceManager::loadFromDisk(const std::string& path) {
  if (!renderer) {
    std::cerr << "[ResourceManager] getTexture called before init()\n";
    return nullptr;
  }

  SDL_Texture* raw = IMG_LoadTexture(renderer, path.c_str());
  if (!raw) {
    std::cerr << "[ResourceManager] Critical Error loading '" << path << "': " << IMG_GetError()
              << '\n';
    return nullptr;
  }

  return raw;
}

SDL_Texture* ResourceManager::placeholder() {
  constexpr const char* kPlaceholderKey = "__placeholder__";

  if (auto it = textures.find(kPlaceholderKey); it != textures.end()) {
    return it->second.get();
  }

  if (!renderer) {
    return nullptr;
  }

  SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
  if (!surface) {
    return nullptr;
  }

  SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, 255, 0, 255, 255));
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    return nullptr;
  }

  textures.emplace(kPlaceholderKey, TexturePtr(texture));
  return texture;
}

void ResourceManager::clean() {
  textures.clear();
  assetMap.clear();
  renderer = nullptr;
  std::cout << "[ResourceManager] Cache cleared.\n";
}