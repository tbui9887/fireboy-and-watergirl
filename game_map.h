#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "header.h"
#include "texture.h"


//chứa dữ liệu file map
struct Map
{
    int tile[MAX_MAP_Y][MAX_MAP_X]; //mảng hai chiều chứa dữ liệu map
    string file_name; //lấy tên file chứa dữ liệu map

};

//render ảnh của map ra
class TileMap : public LTexture //kế thừa vì thế nó sẽ lấy các phương thức của LTexture để sử dụng
{
public:
    TileMap() { } //khai báo hàm (không có gì)
    ~TileMap() { } //hủy hàm (không có gì)
};

//kết hợp hai nhiệm vụ tải map lên và render ảnh
class GameMap
{
public:
    GameMap() {}
    ~GameMap() {}

    void LoadMap (string name); //load file map lên
    void LoadTiles (SDL_Renderer* screen); //render ảnh của map ra
    void DrawMap (SDL_Renderer* screen); //vẽ toàn bộ map ra màn hình
    Map getMap() { return map_game; } //lỡ có thay đổi map thì nó sẽ lưu vào

private:
    Map map_game;
    TileMap map_tile [MAX_TILE];
};

#endif // GAME_MAP_H
