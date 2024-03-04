#include "SDL2/SDL.h"
#include <string>

namespace SDLFunctions {
  bool initialise(std::string title, int width, int height, SDL_Window*& window, SDL_GLContext& context) {
    // Initialise SDL 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("Error initializing SDL: %s\n", SDL_GetError());
      return false;
    }

    // Set OpenGL context attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    Uint32 createWindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    window = SDL_CreateWindow(
      title.c_str(), 
      SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 
      width, 
      height, 
      createWindowFlags
    );

    // Check if the window creation was a success 
    if (window == NULL) {
      printf("Error creating the window: %s\n", SDL_GetError());
      return false;
    }

    // Create an OpenGl context 
    context = SDL_GL_CreateContext(window);

    // Check if OpenGl context creation was a success 
    if (context == NULL) {
      printf("Error creating the context: %s\n", SDL_GetError());
      return false;
    }

    // Enable VSYNC 
    if (SDL_GL_SetSwapInterval(-1) < 0) {
      printf("Error enabling VSYNC: %s\n", SDL_GetError());
      return false;
    }

    return true;
  }
}