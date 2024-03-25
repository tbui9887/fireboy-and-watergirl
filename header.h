
#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using std::cout;
using std::cin;
using std::string;
using std::vector;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

const int TRANSPARENT_RED = 255;
const int TRANSPARENT_GREEN = 0;
const int TRANSPARENT_BLUE = 255;

const int DEFAULT_RED = 255;
const int DEFAULT_GREEN = 255;
const int DEFAULT_BLUE = 255;

#define MAX_TILE 10
#define MAX_MAP_X 20
#define MAX_MAP_Y 20
#define BLOCK_SIZE 32

#define BLANK_TILE 0
#define LAVA_TILE 4

#define MAX_CLIPS 10

const int CHARACTER_WIDTH = 32;
const int CHARACTER_HEIGHT = 52;

enum CHARACTER{ //có thể sẽ phát triển animation của cái khác nữa, hoặc tương tác với cái khác
    FIREBOY,
    WATERGIRL
};

#define frame_main_character_walk 9
#define frame_main_character_stand 7

#define GRAVATY 0.5
#define MAX_GRAVATY 6
#define PLAYER_SPEED 2
#define JUMP_SPEED 10
#define diff_walk 7

#define SCREEN_TICKS_PER_FRAME 40

#define X_BUTTON 64
#define Y_BUTTON 120

#define X_BARRIER 96
#define Y_BARRIER 288

#define BUTTON_WIDTH 20
#define BUTTON_HEIGHT 10

#define BARRIER_WIDTH 7
#define BARRIER_HEIGHT 64

#define MAX_MOVE 64

#endif // HEADER_H_
