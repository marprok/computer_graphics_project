#include <string>
#include "GLEW\glew.h"

#ifndef TOOLS_H
#define TOOLS_H

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