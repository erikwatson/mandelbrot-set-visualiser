#pragma once

struct ButtonState {
  bool pressed = false;
  bool justPressed = false;
  bool released = true;
  bool justReleased = false;
};

namespace ButtonFunctions {
  void reset(ButtonState& button);
  void processEvents(SDL_Event e, ButtonState& button);
}