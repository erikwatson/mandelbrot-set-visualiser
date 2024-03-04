#!/bin/zsh

BASE_DIR="/Users/e.watson/personal-projects/mandelbrot-set-shader"

/usr/bin/clang++ -std=c++17 -g -o $BASE_DIR/output/application \
  -I$BASE_DIR/include \
  -I$BASE_DIR/include/glm \
  -I$BASE_DIR/include/imgui \
  -I/usr/local/include/SDL2 \
  $BASE_DIR/include/imgui/*.cpp \
  $BASE_DIR/include/imgui/backends/imgui_impl_opengl3.cpp \
  $BASE_DIR/include/imgui/backends/imgui_impl_sdl2.cpp \
  src/**/*.cpp src/*.c -lSDL2 -lSDL2_image -framework OpenGL