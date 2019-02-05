#include "../headers/AudioSystem.h"



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
    delete[] concatString;
    Mix_PlayChannel(-1, chunk, 0);

}
