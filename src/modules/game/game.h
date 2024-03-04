#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "glad/glad.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

#include "../engine/input.h"
#include "../engine/shader.h"

#include "glm/glm.hpp"

struct GameState {
  std::string title;
  int width;
  int height;
};

namespace GameFunctions {
  float calculateDeltaTime(Uint32& lastFrameTime);
  void initialise(GameState game);
  void input(bool& quit, InputState& input);
  void update(float dt, InputState& input);
  int render(SDL_Window* window, ShaderPrograms shaders, glm::mat4& projectionMatrix, glm::mat4& viewMatrix, float totalTime, GameState game);
  void cleanup(SDL_Window* window, GLuint VAO, GLuint VBO);
}

