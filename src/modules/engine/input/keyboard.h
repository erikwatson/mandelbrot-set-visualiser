#pragma once

#include "SDL2/SDL.h"
#include "button.h"

struct KeyboardState {
  ButtonState A;
  ButtonState B;
  ButtonState C;
  ButtonState D;
  ButtonState E;
  ButtonState F;
  ButtonState G;
  ButtonState H;
  ButtonState I;
  ButtonState J;
  ButtonState K;
  ButtonState L;
  ButtonState M;
  ButtonState N;
  ButtonState O;
  ButtonState P;
  ButtonState Q;
  ButtonState R;
  ButtonState S;
  ButtonState T;
  ButtonState U;
  ButtonState V;
  ButtonState W;
  ButtonState X;
  ButtonState Y;
  ButtonState Z;
  ButtonState UP;
  ButtonState DOWN;
  ButtonState LEFT;
  ButtonState RIGHT;
  ButtonState ESC;
  ButtonState SPACE;
};

namespace KeyboardFunctions {
  void handleKeyboardEvent(SDL_Event e, ButtonState& key);
  void processEvents(SDL_Event e, KeyboardState& input);
  void reset(KeyboardState& input);
}