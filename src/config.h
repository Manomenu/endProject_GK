#define REMOVE_IMGUI 0

#if REMOVE_IMGUI == 0
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imguiThemes.h>
#endif
#include <chrono>
#include <unordered_map>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <cstdio>
#include <assimp/Importer.hpp>	// C++ Importer interface
#include <assimp/scene.h>		// Output data structure
#include <assimp/postprocess.h>	// Post processing flags
#include <cstring>
#include <stb_image/stb_image.h>
#include <assert.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#undef min
#undef max
#include <GLFW/glfw3.h>
#include <glad/glad.h>


typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

#define MODELS_PATH RESOURCES_PATH "models/"

#define PROJECT_ERROR(message)																						  \
    {																									      \
        std::cerr << "Error at line " << __LINE__ << " in file " << MODELS_PATH << __FILE__ << ": " << message << std::endl; \
		assert(0);																					  \
    }