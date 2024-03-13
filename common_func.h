
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//Screen dimensions
const int SCREEN_WIDTH = 544;
const int SCREEN_HEIGHT = 400;

//Pointer SDL
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

//Transparent Color
const int DelR = 255;
const int DelG = 0;
const int DelB = 255;

//Struct for map
#define TILE_SIZE 34*25

#define MAX_MAP_X 34
#define MAX_MAP_Y 25

#define block_width 25
#define block_height 16

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_X][MAX_MAP_Y];
    char* file_name_;
}

#endif // COMMON_FUNCTION_H_
