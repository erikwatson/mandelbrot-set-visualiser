#include "SDL2/SDL.h"
#include "button.h"
#include "mouse.h"
#include "../input.h"

namespace MouseFunctions {
  void processEvents(SDL_Event e, MouseState& mouse) {
    if (e.type == SDL_MOUSEMOTION) {
      mouse.position.x = e.motion.x;
      mouse.position.y = e.motion.y;
    }

    if (e.button.button == SDL_BUTTON_LEFT) {
      ButtonFunctions::processEvents(e, mouse.left);
    }

    if (e.button.button == SDL_BUTTON_RIGHT) {
      ButtonFunctions::processEvents(e, mouse.right);
    }
  }

  void reset(MouseState& mouse) {
    ButtonFunctions::reset(mouse.left);
    ButtonFunctions::reset(mouse.right);
  }
}