#pragma once

#include "input/keyboard.h"
#include "input/mouse.h"

struct InputState {
  KeyboardState keyboard;
  MouseState mouse;
};

namespace InputFunctions {
  void processEvents(SDL_Event e, InputState& input);
  void reset(InputState& input);
}
