#ifndef SELECT_MENU_H
#define SELECT_MENU_H

#include "header.h"
#include "character.h"
#include "object_button.h"
#include "enermy.h"

enum GAME_PLAY_MODE
{
    RANDOM_MAP = 0,
    CHOOSE_LEVEL = 1,
};

enum LEVEL_GAME
{
    LEVEL1,
    LEVEL2,
    LEVEL3,
};

int ChooseGamePlayMode();
int RandomLevel();
int ChooseLevel();

string LevelMap (MainObject &player_1, MainObject &player_2, vector<Object> &obj, vector<Enermy> &enmy);


#endif // SELECT_MENU_H
