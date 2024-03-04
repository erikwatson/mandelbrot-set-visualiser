#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>

#include "glad/glad.h"
#include <cfloat> 

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../engine/input.h"
#include "../engine/graphics.h"
#include "../engine/shader.h"
#include "../engine/opengl.h"

#include "../engine/imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm/gtx/string_cast.hpp"

#include "../engine/entity.h"
#include "../engine/world.h"

#include <sstream>
#include "game.h"

struct MandelbrotState {
  float zoom;
  glm::vec2 offset;
};

// TODO: This is a bit confused, some of this is gameplay code and some of this is engine code - should separate these out
namespace GameFunctions {
  WorldState world;
  MandelbrotState mandelbrotState;

  float calculateDeltaTime(Uint32& lastFrameTime) {
    Uint32 currentFrameTime = SDL_GetTicks();
    float dt = (currentFrameTime - lastFrameTime) / 1000.0f;  // Convert milliseconds to seconds
    
    lastFrameTime = currentFrameTime;

    return dt;
  }

  void initialise(GameState game) {
    int width = game.width;
    int height = game.height;

    EntityState entity;
    
    entity.position.x = 0.0f;
    entity.position.y = 0.0f;
    entity.size.x = width;
    entity.size.y = height;
    entity.scale = 1.0f;
    entity.rotation = 0.0f;

    world.entities.push_back(entity);

    // initialise mandelbrot state
    mandelbrotState.zoom = 1.0f;
    mandelbrotState.offset = glm::vec2(0.0f, 0.0f);
  }

  void input(bool& quit, InputState& input) {
    SDL_Event e;

    InputFunctions::reset(input);

    while (SDL_PollEvent(&e) != 0) {
      ImGui_ImplSDL2_ProcessEvent(&e);

      // closing with the window decoration buttons 
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      InputFunctions::processEvents(e, input);
    }
  }

  void update(float dt, InputState& input) {

  }

  int render(SDL_Window* window, ShaderPrograms shaders, glm::mat4& projectionMatrix, glm::mat4& viewMatrix, float totalTime, GameState game) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    glUseProgram(shaders.mandelbrot);

    GLuint modelViewProjectionLoc = glGetUniformLocation(shaders.mandelbrot, "modelViewProjection");

    if (modelViewProjectionLoc == -1) {
      return 1;
    }

    glUniformMatrix4fv(modelViewProjectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix));

    glm::mat4 retrievedMatrix;
    glGetUniformfv(shaders.mandelbrot, modelViewProjectionLoc, glm::value_ptr(retrievedMatrix));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(EntityState& entity : world.entities) {
      OpenGLFunctions::bindMandelbrotUniforms(shaders.mandelbrot, totalTime, glm::vec2(game.width, game.height), mandelbrotState.zoom, mandelbrotState.offset);
      glm::mat4 modelMatrix = EntityFunctions::getModelMatrix(entity);
      glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

      glUniformMatrix4fv(modelViewProjectionLoc, 1, GL_FALSE, glm::value_ptr(mvp));
      GraphicsFunctions::drawRectangle(entity.size);
    }


    // Create a new window
    ImGui::Begin("Control Panel");

    // Add a slider to control the variable
    ImGui::SliderFloat("Zoom", &mandelbrotState.zoom, 0.0f, 8000.0f);
    ImGui::SliderFloat("X Position", &mandelbrotState.offset.x, -2.0f, 2.0f);
    ImGui::SliderFloat("Y Position", &mandelbrotState.offset.y, -2.0f, 2.0f);

    // Finish the window
    ImGui::End();

    // render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap the back buffer
    SDL_GL_SwapWindow(window);

    return 0;
  }

  void cleanup(SDL_Window* window, GLuint VAO, GLuint VBO) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  }  
}
