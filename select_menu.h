#ifndef SELECT_MENU_H
#define SELECT_MENU_H

#include "header.h"
#include "character.h"
#include "object_button.h"
#include "enemy.h"
#include "texture.h"
#include "text.h"
#include "timer.h"


enum GAME_PLAY_MODE
{
    RANDOM_MAP = 0,
    CHOOSE_LEVEL = 1,
};

enum LEVEL_GAME
{
    LEVEL1 = 0,
    LEVEL2 = 1,
    LEVEL3 = 2,
};

int ChooseGamePlayMode();
int RandomLevel();
int ChooseLevel();

string LevelMap (MainObject &player_1, MainObject &player_2, vector<Object> &obj, vector<Enemy> &enemies_list, SDL_Renderer* screen, int &StartTime);
int ShowMenuStartOrNot(MainObject &Player1, MainObject &Player2, vector<Object> &obj, vector<Enemy> &enemies_list, SDL_Renderer* screen, SDL_Event event, string &path_map, bool &quit, int &StartTime);
int ShowSelectLevel(SDL_Renderer* screen, SDL_Event event, string &path_map, MainObject &Player1, MainObject &Player2, vector<Object> &obj, vector<Enemy> &enemies_list, bool &quit, int &StartTime);
bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
int menu_playing(SDL_Renderer *screen, SDL_Event event, bool quit, vector<Object> &obj, vector<Enemy> &enemies_list, MainObject &Player1, MainObject &Player2, string &path_map, int &StartTime);
int MenuResult(SDL_Renderer *screen, SDL_Event event, bool &quit, vector<Object> &obj, vector<Enemy> &enemies_list, MainObject &Player1, MainObject &Player2, string path_map, bool win, const int &time_num, int &StartTime);

#endif // SELECT_MENU_H
