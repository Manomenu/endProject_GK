#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>



namespace internals
{
	void GLAPIENTRY glDebugOutput(GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char* message,
		const void* userParam);

	void enable_gl_error_handling();
}
