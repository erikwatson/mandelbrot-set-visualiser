#pragma once

#include "SDL2/SDL.h"
#include "button.h"

struct Position {
  int x = 0;
  int y = 0;
};

struct MouseState {
  ButtonState left;
  ButtonState right;
  Position position;
};

namespace MouseFunctions {
  void processEvents(SDL_Event e, MouseState& input);
  void reset(MouseState& input);
}