
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "common_func.h"
#include "BaseObject.h"

#define MAX_TILE 10

struct Map{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_X][MAX_MAP_Y];
    char* file_name_;
};

class TileMap : public BaseObject
{
public:

    TileMap(){}
    ~TileMap(){}
};

class GameMap
{
public:
    GameMap() {}
    ~GameMap() {}

    void LoadMap(const char* name);
    void LoadTiles(SDL_Renderer* screen);
    void Drawmap(SDL_Renderer* screen);
    Map getMap() {return game_map_;}


private:
    Map game_map_;
    TileMap tile_map [MAX_TILE];
};


#endif // GAME_MAP_H_
