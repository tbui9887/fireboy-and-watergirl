
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <stdio.h>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

//Pointer SDL
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

//Transparent Color
const int DelR = 255;
const int DelG = 0;
const int DelB = 255;

#endif // COMMON_FUNCTION_H_
