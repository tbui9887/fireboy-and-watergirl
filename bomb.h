
#ifndef BOMB_H
#define BOM_H

#include "header.h"
#include "texture.h"
#include "game_map.h"
#include "character.h"
#include "enemy.h"
#include "text.h"

class Bomb : LTexture
{
private:
    LTexture bomb_obj;
    LTexture explode_obj;

    float x_bomb, y_bomb, y_val_bomb;
    int bomb_width, bomb_height;

    int x_explode, y_explode;
    int explode_width, explode_height;
    SDL_Rect ExplosionRect;

    int TimePutBomb;
    int ReadyBomb = 0;
    bool isPutBomb = false;

public:
    Bomb();
    void DeleteBomb();

    void loadImg(SDL_Renderer *screen);
    void loadChunk();
    void ShowBomb(SDL_Renderer *screen);
    void ShowExplode (SDL_Renderer *screen);
    void setXposBomb(int x) { x_bomb = x; }
    void setYposBomb(int y) { y_bomb = y; }
    void HandleInputAction (SDL_Event event, SDL_Renderer *screen, MainObject &Player);
    void ExplosionAfterPutBomb(SDL_Renderer *screen, MainObject &FirePlay, MainObject &WaterPlay, vector<Enemy> &enemies_list);
    void FallDown(const Map &map_data);
    void check_to_map(const Map &map_data);
    bool getIsPutBomb() { return isPutBomb; }
    void setExplosionRect() { ExplosionRect = {x_explode, y_explode, explode_width, explode_height}; }
    void InteractWithCharAndEnemy(MainObject &FirePlay, MainObject &WaterPlay, vector<Enemy> &enemies_list);
};


#endif // BOMB_H
