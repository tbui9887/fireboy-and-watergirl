
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using std::cout;
using std::cin;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

//Transparent Color
const int DelR = 255;
const int DelG = 0;
const int DelB = 255;

//Struct for map

#define MAX_MAP_X 20
#define MAX_MAP_Y 20

#define BLOCK 32

#endif // COMMON_FUNCTION_H_
