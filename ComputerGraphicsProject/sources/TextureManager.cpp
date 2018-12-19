#include "../headers/TextureManager.h"
#include <algorithm>
#include "SDL2/SDL_image.h"

// Texture
TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	// delete textures
	for (int i = 0; i < textures.size(); i++)
		glDeleteTextures(1, &textures[i].textureID);
	textures.clear();
}

void TextureManager::Clear()
{
	std::for_each(textures.begin(), textures.end(), [](TextureContainer container) { glDeleteTextures(1, &container.textureID); });
	textures.clear();
}

int TextureManager::findTexture(const char* filename, bool hasMipmaps)
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i].filename.compare(filename) == 0 && textures[i].hasMipmaps == hasMipmaps)
		{
			return i;
		}
	}
	return -1;
}

GLuint TextureManager::RequestTexture(const char* filename, bool hasMipmaps)
{
	// first check if we can find it in the manager
	int index = findTexture(filename, hasMipmaps);

	if (index != -1)
		return textures[index].textureID;

	// load the texture
	SDL_Surface* surf = IMG_Load(filename);
	if (surf == 0)
	{
		printf("Could not Load texture %s\n", filename);
		printf("SDL load Error %s\n", SDL_GetError());
		return 0; // error
	}
	TextureContainer container;
	container.filename = filename;
	container.hasMipmaps = hasMipmaps;
	GLenum texture_format;
	GLint nOfColors;
	glGenTextures(1, &container.textureID);
	glBindTexture(GL_TEXTURE_2D, container.textureID);
	nOfColors = surf->format->BytesPerPixel;
	switch (surf->format->BytesPerPixel)
	{
	case 4: // contains alpha channel
		if (surf->format->Rmask == 0x000000ff)	 texture_format = GL_RGBA;
		else texture_format = GL_BGRA;
		nOfColors = GL_RGBA;
		break;
	case 3: // no alpha channel
		if (surf->format->Rmask == 0x000000ff) texture_format = GL_RGB;
		else texture_format = GL_BGR;
		nOfColors = GL_RGB;
		break;
	default:
		printf("Error in number of colors at %s\n", filename);
	}

	unsigned char* data = new unsigned char[surf->w * surf->h * surf->format->BytesPerPixel];
	// flip image
	for (int y = 0; y < surf->h; y++)
		memcpy(&data[(surf->h - y - 1) * surf->w * surf->format->BytesPerPixel], &static_cast<unsigned char*>(surf->pixels)[y * surf->w * surf->format->BytesPerPixel], surf->w * surf->format->BytesPerPixel * sizeof(unsigned char));

	SDL_LockSurface(surf);
	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surf->w, surf->h, 0, texture_format, GL_UNSIGNED_BYTE, data);
	SDL_UnlockSurface(surf);
	delete[] data;

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (hasMipmaps)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	if (surf) SDL_FreeSurface(surf);
	glBindTexture(GL_TEXTURE_2D, 0); // unbind the texture

	// save the texture
	textures.push_back(container);
	return container.textureID;
}