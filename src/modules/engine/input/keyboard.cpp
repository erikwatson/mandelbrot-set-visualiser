#include "SDL2/SDL.h"

#include "keyboard.h"
#include "button.h"

namespace KeyboardFunctions {
  void handleKeyboardEvent(SDL_Event e, ButtonState& key) {
    if (e.type == SDL_KEYDOWN) {
      if (!key.pressed) {
        key.justPressed = true;
      } else {
        key.justPressed = false;
      }

      key.pressed = true;
      key.released = false;
    }

    if (e.type == SDL_KEYUP) {
      if (!key.released) {
        key.justReleased = true;
      } else {
        key.justReleased = false;
      }
      
      key.released = true;
      key.pressed = false;
    }
  }

  void processEvents(SDL_Event e, KeyboardState& keyboard) {
    switch (e.key.keysym.sym) {
      case SDLK_a: handleKeyboardEvent(e, keyboard.A); break;
      case SDLK_b: handleKeyboardEvent(e, keyboard.B); break;
      case SDLK_c: handleKeyboardEvent(e, keyboard.C); break;
      case SDLK_d: handleKeyboardEvent(e, keyboard.D); break;
      case SDLK_e: handleKeyboardEvent(e, keyboard.E); break;
      case SDLK_f: handleKeyboardEvent(e, keyboard.F); break;
      case SDLK_g: handleKeyboardEvent(e, keyboard.G); break;
      case SDLK_h: handleKeyboardEvent(e, keyboard.H); break;
      case SDLK_i: handleKeyboardEvent(e, keyboard.I); break;
      case SDLK_j: handleKeyboardEvent(e, keyboard.J); break;
      case SDLK_k: handleKeyboardEvent(e, keyboard.K); break;
      case SDLK_l: handleKeyboardEvent(e, keyboard.L); break;
      case SDLK_m: handleKeyboardEvent(e, keyboard.M); break;
      case SDLK_n: handleKeyboardEvent(e, keyboard.N); break;
      case SDLK_o: handleKeyboardEvent(e, keyboard.O); break;
      case SDLK_p: handleKeyboardEvent(e, keyboard.P); break;
      case SDLK_q: handleKeyboardEvent(e, keyboard.Q); break;
      case SDLK_r: handleKeyboardEvent(e, keyboard.R); break;
      case SDLK_s: handleKeyboardEvent(e, keyboard.S); break;
      case SDLK_t: handleKeyboardEvent(e, keyboard.T); break;
      case SDLK_u: handleKeyboardEvent(e, keyboard.U); break;
      case SDLK_v: handleKeyboardEvent(e, keyboard.V); break;
      case SDLK_w: handleKeyboardEvent(e, keyboard.W); break;
      case SDLK_x: handleKeyboardEvent(e, keyboard.X); break;
      case SDLK_y: handleKeyboardEvent(e, keyboard.Y); break;
      case SDLK_z: handleKeyboardEvent(e, keyboard.Z); break;
      case SDLK_SPACE: handleKeyboardEvent(e, keyboard.SPACE); break;
      case SDLK_ESCAPE: handleKeyboardEvent(e, keyboard.ESC); break;
      case SDLK_UP: handleKeyboardEvent(e, keyboard.UP); break;
      case SDLK_DOWN: handleKeyboardEvent(e, keyboard.DOWN); break;
      case SDLK_LEFT: handleKeyboardEvent(e, keyboard.LEFT); break;
      case SDLK_RIGHT: handleKeyboardEvent(e, keyboard.RIGHT); break;
    }
  }

  void reset(KeyboardState& keyboard) {
    ButtonFunctions::reset(keyboard.A);
    ButtonFunctions::reset(keyboard.B);
    ButtonFunctions::reset(keyboard.C);
    ButtonFunctions::reset(keyboard.D);
    ButtonFunctions::reset(keyboard.E);
    ButtonFunctions::reset(keyboard.F);
    ButtonFunctions::reset(keyboard.G);
    ButtonFunctions::reset(keyboard.H);
    ButtonFunctions::reset(keyboard.I);
    ButtonFunctions::reset(keyboard.J);
    ButtonFunctions::reset(keyboard.K);
    ButtonFunctions::reset(keyboard.L);
    ButtonFunctions::reset(keyboard.M);
    ButtonFunctions::reset(keyboard.N);
    ButtonFunctions::reset(keyboard.O);
    ButtonFunctions::reset(keyboard.P);
    ButtonFunctions::reset(keyboard.Q);
    ButtonFunctions::reset(keyboard.R);
    ButtonFunctions::reset(keyboard.S);
    ButtonFunctions::reset(keyboard.T);
    ButtonFunctions::reset(keyboard.U);
    ButtonFunctions::reset(keyboard.V);
    ButtonFunctions::reset(keyboard.W);
    ButtonFunctions::reset(keyboard.X);
    ButtonFunctions::reset(keyboard.Y);
    ButtonFunctions::reset(keyboard.Z);
    ButtonFunctions::reset(keyboard.ESC);
    ButtonFunctions::reset(keyboard.SPACE);
    ButtonFunctions::reset(keyboard.UP);
    ButtonFunctions::reset(keyboard.DOWN);
    ButtonFunctions::reset(keyboard.LEFT);
    ButtonFunctions::reset(keyboard.RIGHT);
  }
}