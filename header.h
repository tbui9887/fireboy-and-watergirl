
#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using std::cout;
using std::cin;
using std::string;
using std::vector;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 800;

const int TRANSPARENT_RED = 255;
const int TRANSPARENT_GREEN = 0;
const int TRANSPARENT_BLUE = 255;

const int DEFAULT_RED = 255;
const int DEFAULT_GREEN = 255;
const int DEFAULT_BLUE = 255;

#define MAX_TILE 100

#define MAX_MAP_X 30
#define MAX_MAP_Y 25
#define BLOCK_SIZE 32

#define BLANK_TILE 0
#define FLOWER_TILE 46
#define SMALL_ROCK 47
#define BIG_ROCK 48
#define BUSH 49
#define YELLOW_COIN 55
#define BLUE_COIN 62
#define WATER_FRONT_LIQUID 78
#define FIRE_FRONT_LIQUID 81
#define TOXIC_FRONT_LIQUID 85
#define WATER_MIDDLE_LIQUID 79
#define FIRE_MIDDLE_LIQUID 82
#define TOXIC_MIDDLE_LIQUID 86
#define WATER_END_LIQUID 80
#define FIRE_END_LIQUID 83
#define TOXIC_END_LIQUID 87

#define MAX_CLIPS 10

const int CHARACTER_WIDTH = 32;
const int CHARACTER_HEIGHT = 52;

enum CHARACTER{ //có thể sẽ phát triển animation của cái khác nữa, hoặc tương tác với cái khác
    FIREBOY = 0,
    WATERGIRL = 1,
};

#define frame_main_character_walk 9
#define frame_main_character_stand 7

#define GRAVITY 0.5
#define MAX_GRAVITY 6
#define PLAYER_SPEED 2
#define JUMP_SPEED 10
#define diff_walk 7

#define FPS 40
#define SCREEN_TICKS_PER_FRAME 1000/FPS

#define X_BUTTON 64
#define Y_BUTTON 120

#define X_BARRIER 96
#define Y_BARRIER 288

#define BUTTON_WIDTH 20
#define BUTTON_HEIGHT 10

#define BARRIER_WIDTH 7
#define BARRIER_HEIGHT 64

#define X_EBUTTON 358
#define Y_EBUTTON 113

#define X_ELEVATOR 293
#define Y_ELEVATOR 558

#define EBUT_WIDTH 20
#define EBUT_HEIGHT 10

#define ELEVATOR_WIDTH 60
#define ELEVATOR_HEIGHT 7

#define MAX_MOVE 70

static int barrier_move = 0;

//static int YellowCoin = 0;
//static int BlueCoin = 0;

#define MAX_MOVING_ENERMY 20
#define enermy_jet 1

#define MAX_LEVEL 3

#define ENEMY_WIDTH 39
#define ENEMY_HEIGHT 32

#define ENEMY_CLIPS 7

#endif // HEADER_H_
