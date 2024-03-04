#include <SDL2/SDL.h>

#include "input.h"
#include "input/mouse.h"
#include "input/keyboard.h"

namespace InputFunctions {
  void processEvents(SDL_Event e, InputState& input) {
    MouseFunctions::processEvents(e, input.mouse);
    KeyboardFunctions::processEvents(e, input.keyboard);
  }

  void reset(InputState& input) {
    MouseFunctions::reset(input.mouse);
    KeyboardFunctions::reset(input.keyboard);
  }
}