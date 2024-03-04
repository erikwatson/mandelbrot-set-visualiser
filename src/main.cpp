#define GLM_ENABLE_EXPERIMENTAL

#include "modules/game/game.h"

#include "modules/engine/input.h"
#include "modules/engine/shader.h"
#include "modules/engine/opengl.h"
#include "modules/engine/sdl.h"
#include "modules/engine/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "glm/glm/gtx/string_cast.hpp"

enum ApplicationState {
  RENDERING_ERROR = 2,
  INITIALISATION_ERROR = 1,  
  SUCCESS = 0
};

int main(int argc, char* argv[]) {
  GameState game;
  SDL_Window* window;
  SDL_GLContext context;

  game.title = "Mandelbrot Set";
  game.width = 1920;
  game.height = 1080;

  if(!SDLFunctions::initialise(game.title, game.width, game.height, window, context)) {
    return ApplicationState::INITIALISATION_ERROR;
  }

  if(!OpenGLFunctions::initialise(game.width, game.height)) {
    return ApplicationState::INITIALISATION_ERROR;
  }

  if(!ImGUIFunctions::initialise(window, context)) {
    return ApplicationState::INITIALISATION_ERROR;
  }

  // Setup Shaders 
  ShaderPrograms shaders;

  if(!ShaderFunctions::initialise(shaders)) {
    return ApplicationState::INITIALISATION_ERROR;
  }

  // Set up vertex arrays and buffers 
  GLuint VAO;
  GLuint VBO;

  if(!OpenGLFunctions::initialiseBuffers(VAO, VBO, shaders.mandelbrot)) {
    return ApplicationState::INITIALISATION_ERROR;
  }

  GameFunctions::initialise(game); 

  WorldState world;

  glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(game.width), static_cast<float>(game.height), 0.0f, -1000.0f, 1000.0f);
  glm::mat4 viewMatrix = glm::mat4(1.0f);
  
  // Game loop 
  bool quit = false;
  Uint32 lastFrameTime = SDL_GetTicks();
  InputState input;
  float deltaTime;
  float totalTime = 0.0f;

  while (!quit) {
    deltaTime = GameFunctions::calculateDeltaTime(lastFrameTime);
    totalTime += deltaTime;
    
    GameFunctions::input(quit, input);
    GameFunctions::update(deltaTime, input);

    if (GameFunctions::render(window, shaders, projectionMatrix, viewMatrix, totalTime, game)) {
      return ApplicationState::RENDERING_ERROR;
    }

    if(input.keyboard.ESC.justPressed) {
      quit = true;
    }
  }

  GameFunctions::cleanup(window, VAO, VBO);

  // program closed successfully 
  return ApplicationState::SUCCESS;
}