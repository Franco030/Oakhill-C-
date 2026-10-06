#pragma once

#include <SDL2/SDL.h>
#include <filesystem>
#include <string>
#include <vector>

namespace Paths {

inline std::filesystem::path projectRoot() {
  static std::filesystem::path cached = [] {
    std::vector<std::filesystem::path> candidates;
    candidates.push_back(std::filesystem::current_path());

    if (char* base = SDL_GetBasePath()) {
      std::filesystem::path exeDir(base);
      SDL_free(base);
      candidates.push_back(exeDir);
      candidates.push_back(exeDir.parent_path());
    }

    for (const auto& candidate : candidates) {
      if (std::filesystem::exists(candidate / "data" / "database" / "assets.json")) {
        return candidate;
      }
    }

    return std::filesystem::current_path();
  }();

  return cached;
}

inline std::string resource(const std::string& relative) {
  return (projectRoot() / relative).string();
}

} // namespace Paths