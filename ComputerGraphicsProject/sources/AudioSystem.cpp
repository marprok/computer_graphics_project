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

#ifdef __APPLE__
    // apple
    Mix_Chunk *chunk = NULL;
    chunk = Mix_LoadWAV(concatString);
    Mix_PlayChannel(-1, chunk, 0);
#elif __linux__
    // linux
    Mix_Chunk *chunk = NULL;
    chunk = Mix_LoadWAV(concatString);
    Mix_PlayChannel(-1, chunk, 0);

#endif
    delete[] concatString;
}

void Audio::PlayMusic(const char *filename)
{
    const char *folder = "Audio/";

    int bufferSize = strlen(folder) + strlen(filename) + 1;

    char* concatString = new char[ bufferSize ];

    strcpy( concatString, folder );
    strcat( concatString, filename);


#ifdef __APPLE__
    // apple
    Mix_Music *music = NULL;
    music = Mix_LoadMUS(concatString);
    Mix_PlayMusic(music, -1);
#elif __linux__
    // linux
    Mix_Music *music = NULL;
    music = Mix_LoadMUS(concatString);
    Mix_PlayMusic(music, -1);
#endif
    delete[] concatString;



}
