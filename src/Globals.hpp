#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#ifndef Globals_hpp
#define Globals_hpp

SDL_Window* gWindow{nullptr};
SDL_Surface* gScreenSurface{nullptr};
SDL_Renderer* gRenderer{nullptr};

#endif
