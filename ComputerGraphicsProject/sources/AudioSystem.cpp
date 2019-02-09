#include "../headers/AudioSystem.h"
#include <iostream>

Audio::Audio()
{

}


Audio::~Audio()
{
}

void Audio::PlayAudio(const char *filename)
{

    const char *folder = "Audio/";

    int bufferSize = strlen(folder) + strlen(filename) + 1;

    char* concatString = new char[ bufferSize ];

    strcpy( concatString, folder );
    strcat( concatString, filename);

	Mix_Chunk *chunk = NULL;
	chunk = Mix_LoadWAV(concatString);
	if (chunk == NULL)
	{
        //std::cout << "Null" << std::endl;
	}
	Mix_PlayChannel(-1, chunk, 0);

    delete[] concatString;
}

void Audio::PlayMusic(const char *filename)
{

	const char *folder = "Audio/";

    int bufferSize = strlen(folder) + strlen(filename) + 1;

    char* concatString = new char[ bufferSize ];

    strcpy( concatString, folder );
    strcat( concatString, filename);

	Mix_Music *music = NULL;
	music = Mix_LoadMUS(concatString);
	Mix_PlayMusic(music, -1);

    delete[] concatString;

}
