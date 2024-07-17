#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
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
typedef unsigned short ushort;
typedef unsigned char uchar;

#define PROJECT_ERROR(message)																						  \
    {																									      \
        std::cerr << "Error at line " << __LINE__ << " in file " << __FILE__ << ": " << message << std::endl; \
		exit(1);																							  \
    }