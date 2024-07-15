#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <chrono>
#include <unordered_map>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cstdio>

#define REMOVE_IMGUI 0

#if REMOVE_IMGUI == 0
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imguiThemes.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif
#undef min
#undef max


typedef unsigned int uint;