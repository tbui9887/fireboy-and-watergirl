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
        string map_name = "Data/photo/block/" + std::to_string(i) + ".png";
        map_tile[i].loadFromFile(map_name, screen);
    }

    obj.loadImg(screen);
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

    obj.render(screen);
}


void Object::loadImg(SDL_Renderer* screen)
{
    if (! button.loadFromFile("Data/photo/block/button.png", screen) ){
        cout << "can't upload button photo\n";
    }
    if (! barrier.loadFromFile("Data/photo/block/barrier.png", screen) ){
        cout << "can't upload barrier photo\n";
    }
}

Object::Object()
{
    x_but = X_BUTTON;
    y_but = Y_BUTTON;
    x_bar = X_BARRIER;

    button.inwidth(BUTTON_WIDTH);
    button.inheight(BUTTON_HEIGHT);

    barrier.inwidth(BARRIER_WIDTH);
    barrier.inheight(BARRIER_HEIGHT);

    button.inrect(x_but, y_but);
    barrier.inrect(x_bar, y_bar);
}

void Object::render(SDL_Renderer* screen)
{
    button.render(x_but, y_but, NULL, screen);
    barrier.render(x_bar, y_bar, NULL, screen);
    cout << "success upload!";
    cout << y_bar << std::endl;
}

SDL_Rect Object::ButRect()
{
    button.inrect(x_but, y_but);
    SDL_Rect but = button.getRect();
    return but;
}

SDL_Rect Object::BarRect()
{
    barrier.inrect(x_bar, y_bar);
    SDL_Rect bar = barrier.getRect();
    return bar;
}

int Object::y_bar = Y_BARRIER;
