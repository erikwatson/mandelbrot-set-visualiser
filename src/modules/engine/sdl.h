#pragma once
#include <string>
#include <SDL2/SDL.h>

namespace SDLFunctions {
  bool initialise(std::string title, int width, int height, SDL_Window*& window, SDL_GLContext& context);
}