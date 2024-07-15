#pragma once
#include <config.h>



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
