#include "SDL2/SDL.h"
#include "button.h"

namespace ButtonFunctions {
  void processEvents(SDL_Event e, ButtonState& button) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
      if (button.pressed == false) {
        button.justPressed = true;
      }

      button.pressed = true;
      button.released = false;
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
      if (button.released == false) {
        button.justReleased = true;
      }

      button.released = true;
      button.pressed = false;
    }
  }

  void reset(ButtonState& button) {
    button.justPressed = false;
    button.justReleased = false;
  }
}