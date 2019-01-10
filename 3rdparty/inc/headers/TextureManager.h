#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
		//define something for Windows (64-bit only)
		#include "SDL2/SDL.h"
		#include "GLEW\glew.h"
		#include <string>
		#include <vector>
	#endif
#elif __APPLE__
	// apple
	#include "TargetConditionals.h"
	#include "SDL2/SDL.h"
	#include "../GLEW/glew.h"
	#include <string>
	#include <vector>
#elif __linux__
	// linux
	#include "SDL2/SDL.h"
	#include "../GLEW/glew.h"
	#include <string>
	#include <vector>
#endif

// Singleton Class of Texture Manager
class TextureManager
{
protected:
	struct TextureContainer
	{
		GLuint textureID;
		std::string filename;
		bool hasMipmaps;
	};
	std::vector<TextureContainer> textures;

	// find the texture with the fiven filename and mipmaps
	int findTexture(const char* filename, bool hasMipmaps);

public:
	// get the static instance of Texture Manager
	static TextureManager& GetInstance()
	{
		static TextureManager manager;
		return manager;
	}
	~TextureManager();

	// delete all textures
	void Clear();

	// Request a texture handle
	GLuint RequestTexture(const char* filename, bool hasMipmaps = false);

protected:
	TextureManager();	
	void operator=(TextureManager const&);
};

#endif
