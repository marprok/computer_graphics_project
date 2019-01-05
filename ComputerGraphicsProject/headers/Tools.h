#ifndef TOOLS_H
#define TOOLS_H

#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
		//define something for Windows (64-bit only)
		#include <string>
		#include "GLEW\glew.h"
	#endif
#elif __APPLE__
	// apple
	#include "TargetConditionals.h"
	#include <string>
	#include "../GLEW/glew.h"
#elif __linux__
	// linux
	#include <string>
	#include "../GLEW/glew.h"
#endif

namespace Tools
{
	char* LoadWholeStringFile(const char* filename);

	std::string GetFolderPath(const char* filename);

	std::string tolowerCase(std::string str);

	bool compareStringIgnoreCase(std::string str1, std::string str2);

	GLenum CheckGLError();

	GLenum CheckFramebufferStatus(GLuint framebuffer_object);
};

#endif