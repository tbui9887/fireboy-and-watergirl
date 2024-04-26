
#include "game_map.h"

void GameMap::LoadMap (string name)
{
    std::ifstream file_map (name);
    if (! file_map.is_open()){
        cout << "can't upload file map";
    }
    else{
        for (int i = 0; i < MAX_MAP_Y; i++){
            for (int j = 0; j < MAX_MAP_X; j++){
                file_map >> map_game.tile[i][j];
                cout << map_game.tile[i][j] << " "; //test
            }
            cout << std::endl; //test
        }
    }
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    for (int i = 0; i < MAX_TILE; i++){
        string map_name = "Data/new_tiles/image_part_0" + std::to_string(i) + ".png";
        map_tile[i].loadFromFile(map_name, screen);
    }

}

void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x_of_file, y_of_file = 0;
    for (int i = 0; i < SCREEN_WIDTH; i += BLOCK_SIZE){
        x_of_file = 0;
        for (int j = 0; j < SCREEN_HEIGHT; j += BLOCK_SIZE){
            int val = map_game.tile[x_of_file][y_of_file]; //lấy giá trị của ô đó

            if (val > 0){
                map_tile[val].render(i, j, nullptr, screen); //vẽ ra màn hình
            }
            x_of_file++;
        }
        y_of_file++;
    }

    //obj.render(screen);
}


