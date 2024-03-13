#include "common_func.h"
#include "game_map.h"

void GameMap::LoadMap(const char* name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if (fb == NULL){
        return;
    }
    for (int i = 0; i < MAX_MAP_Y; i++){
        for (int j = 0; j < MAX_MAP_X; j++){
            fscanf_s(fp, "%d", &game_map_.tile[i][j]);
        }
    }
}

void GameMap::LoadTiles(SDL_Renderer* gRenderer)
{
    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;

    for (int i = 0; i < MAX_MAP_Y; i++){
        for (int j = 0; j < MAX_MAP_X; j++){
            bool success = tile_map[i][j].loadImg(map[i][j].block_name, gRenderer);
            if (success = false){
                printf("Get_Error: %s\n",SDL_GetError());
                return;
            }
            else{
                tile_map[i][j].Render(gRenderer, NULL);
                int val = game_map_.tile[i][j];
                if (val > 0){
                    if (j > game_map_.max_y_) game_map_.max_x_ = j; //game_max_.max_y_ để tìm giá trị của x lớn nhất
                    if (i > game_map_.max_x) game_map_.max_y_ = i;
                }
            }
        }
    }

    game_map_.max_x = (game_map_.max_x_+1)*block_width; //hiện tại biến đó chỉ là chỉ số của i và j => giá trị tối đa của bản đồ
    game_map_.max_y = (game_map_.max_y_+1)*block_height;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = name //nếu có lỗi thì có thể load lại
    fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* gRenderer)
{
    char file_img[10]; //chỉ số cho ảnh
    FILE* fp = NULL;

    for (int i = 0; i < MAX_TILES; i++){
        sprintf_s(file_img, "map/%d.png", i);
        fopen_s(&fp, file_img, "rb");
        if (fp == NULL){
            continue;
        }
        fclose(fp);
        tile_map[i].loadImg(file_img,gRenderer);
    }

}

void GameMap::DrawMap(SDL_Renderer* gRenderer)
{
    int x1 = 0;
    int x2 = SCREEN_WIDTH;

    int y1 = 0;
    int y2 = SCREEN_HEIGHT;

    map_x = game_map_.start_x_/block_width;
    map_y = game_map_.start_y/block_height; //chỉ số của nó, bên trên nhân vào, bên này lấy ra
    int map_x = 0;
    int map_y = 0;

    for (int i = y1; i < y2; i+= block_height){
        map_x = game_map_.start_x_/block_width;
        for (int j = x1; j < x2; j+=block_width){
            int val = game_map_.tile[map_y][map_x];
            if (val>0){
                tile_map[val].setRect(j,i);
                tile_map[val].Render(gRenderer,NULL);
            }
            map_x++;
        }
        map_y++;
    }

}

