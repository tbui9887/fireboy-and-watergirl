
#ifndef BOMB_H
#define BOM_H

#include "header.h"
#include "texture.h"
#include "game_map.h"
#include "character.h"

class Bomb : LTexture
{
private:
    LTexture bomb_obj;
    LTexture explode_obj;

    float x_bomb, y_bomb, y_val_bomb;
    int bomb_width, bomb_height;

    int x_explode, y_explode;
    int explode_width, explode_height;

    int TimePutBomb;
    bool isPutBomb = false;

public:
    Bomb();
    ~Bomb();
    void loadImg(SDL_Renderer *screen);
    void ShowBomb(SDL_Renderer *screen);
    void ShowExplode (SDL_Renderer *screen);
    void setXposBomb(int x) { x_bomb = x; }
    void setYposBomb(int y) { y_bomb = y; }
    void HandleInputAction (SDL_Event event, SDL_Renderer *screen, MainObject &WaterPlayer, MainObject &FirePlayer);
    void ExplosionAfterPutBomb();
    void FallDown(const Map &map_data);
    void check_to_map(const Map &map_data);
    bool getIsPutBomb() { return isPutBomb; }
};


#endif // BOMB_H
