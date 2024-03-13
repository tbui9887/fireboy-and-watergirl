#include "common_func.h"
#include "game_map.h"

void GameMap::LoadMap(const char* name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if (fp == NULL){
        return;
    }
    for (int i = 0; i < MAX_MAP_Y; i++){
        for (int j = 0; j < MAX_MAP_X; j++){
            fscanf(fp, "%d", &game_map_.tile[i][j]);
            int val = game_map_.tile[i][j];
                if (val > 0){
                    if (j > game_map_.max_y_) game_map_.max_x_ = j; //game_max_.max_y_ để tìm giá trị của x lớn nhất
                    if (i > game_map_.max_x_) game_map_.max_y_ = i;
                }
            }
    }

    game_map_.max_x_= (game_map_.max_x_+1)*BLOCK; //hiện tại biến đó chỉ là chỉ số của i và j => giá trị tối đa của bản đồ
    game_map_.max_y_ = (game_map_.max_y_+1)*BLOCK;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = const_cast<char*>(name); //nếu có lỗi thì có thể load lại
    fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    char file_img[100]; // ten cua anh dang char[]
    FILE* fp = NULL;

    for (int i = 0; i < MAX_TILE; i++){
        sprintf_s(file_img, "Data/photo/%d.png", i);
        fopen_s(&fp, file_img, "rb");
        if (fp == NULL){
            continue;
        }
        tile_map[i].loadImg(file_img,screen);
        fclose(fp);
    }
}

void GameMap::Drawmap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = SCREEN_WIDTH;

    int y1 = 0;
    int y2 = SCREEN_HEIGHT;

    int map_x = 0;
    int map_y = 0; //chỉ số của nó, bên trên nhân vào, bên này lấy ra

    for (int i = y1; i < y2; i+= BLOCK){
        map_x = 0;
        for (int j = x1; j < x2; j+=BLOCK){
            int val = game_map_.tile[map_y][map_x];
            if (val>0){
                tile_map[val].setRect(j,i);
                tile_map[val].Render(screen,NULL);
            }
            map_x++;
        }
        map_y++;
    }
    return;
}

