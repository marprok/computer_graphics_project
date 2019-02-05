#ifndef CHEST_H
#define CHEST_H

#endif // CHEST_H
#pragma once

#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
    #ifdef _WIN64
    #include <SDL2/SDL_mixer.h>
    #include <string.h>
    #endif
#elif __APPLE__
    // apple
    #include <SDL2/SDL_mixer.h>
    #include <string.h>
#elif __linux__
    // linux
    #include <string.h>
    #include <SDL2/SDL_mixer.h>
#endif

class Audio
{
public:
    const char*                                             folder;
    Audio();
    ~Audio();

    static void PlayAudio(const char *filename);
};
