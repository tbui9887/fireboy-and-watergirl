
#include "bomb.h"

Bomb::Bomb()
{
    x_bomb = 0;
    y_bomb = 0;
    bomb_width = 34;
    bomb_height = 30;
    y_val_bomb = 0;

    x_explode = 0;
    y_explode = 0;
    explode_width = 128;
    explode_height = 65;

}

void Bomb::DeleteBomb()
{
    x_bomb = 0;
    y_bomb = 0;

    x_explode = 0;
    y_explode = 0;
}

void Bomb::loadImg(SDL_Renderer *screen)
{
    if (! bomb_obj.loadFromFile("Data/photo/block/bomb.png", screen)){
        cout << "can't load bomb image\n";
    }
    if (! explode_obj.loadFromFile("Data/photo/block/explode.png", screen)){
        cout << "can't load explode image\n";
    }
}

void Bomb::ShowBomb(SDL_Renderer *screen)
{
    bomb_obj.render(x_bomb, y_bomb, NULL, screen);
}

void Bomb::ShowExplode (SDL_Renderer *screen)
{
    explode_obj.render(x_explode, y_explode, NULL, screen);
}

void Bomb::HandleInputAction (SDL_Event event, SDL_Renderer *screen, MainObject &Player)
{
    if (Player.getCharacter() == FIREBOY){
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym)
            {
            case SDLK_l:
                x_bomb = Player.getXpos();
                y_bomb = Player.getYpos();
                TimePutBomb = SDL_GetTicks();
                isPutBomb = true;
                break;
            }
        }
    }
    else{
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                x_bomb = Player.getXpos();
                y_bomb = Player.getYpos();
                TimePutBomb = SDL_GetTicks();
                isPutBomb = true;
                break;
            }
        }
    }
}

void Bomb::FallDown(const Map &map_data)
{
    y_val_bomb += GRAVITY;
    cout << "y_val is: " << y_val_bomb << endl;
    check_to_map(map_data);
}

void Bomb::check_to_map(const Map &map_data){
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // Check vertically
    int width_min = bomb_width < BLOCK_SIZE ? bomb_width : BLOCK_SIZE;
    x1 = (x_bomb) / BLOCK_SIZE;
    x2 = (x_bomb + width_min) / BLOCK_SIZE;

    y1 = (y_bomb + y_val_bomb) / BLOCK_SIZE;
    y2 = (y_bomb + y_val_bomb + bomb_height - 1) / BLOCK_SIZE;


    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_bomb > 0)
        {
            int value_1 = map_data.tile[y2][x1], value_2 = map_data.tile[y2][x2];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ||
                  value_1 == YELLOW_COIN || value_2 == BLUE_COIN) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID ||
                  value_2 == YELLOW_COIN || value_2 == BLUE_COIN) )
                {
                    y_bomb = y2 * BLOCK_SIZE;
                    y_bomb -= (bomb_height+1);
                    y_val_bomb = 0;
                }
        }
    }
    y_bomb += y_val_bomb;
    x_explode = x_bomb - 64; y_explode = y_bomb - 35; //update explode in the same time
}

void Bomb::ExplosionAfterPutBomb(SDL_Renderer *screen, MainObject &FirePlay, MainObject &WaterPlay, vector<Enemy> &enemies_list)
{
    int time_distance = SDL_GetTicks() - TimePutBomb;

    if (time_distance <= 2000){
        ShowBomb(screen);
    }
    else if (time_distance <= 4000){
        ShowExplode(screen);
        InteractWithCharAndEnemy(FirePlay, WaterPlay, enemies_list);
    }
    else{
        isPutBomb = false;
        DeleteBomb();
    }
}

void Bomb::InteractWithCharAndEnemy(MainObject &FirePlay, MainObject &WaterPlay, vector<Enemy> &enemies_list)
{
    setExplosionRect();
    //check with main character
    SDL_Rect mainRect [2];

    mainRect[FIREBOY] = FirePlay.getRectChar();
    mainRect[WATERGIRL] = WaterPlay.getRectChar();

    for (int i = 0; i < 2; i++){
        if ( check_collision(mainRect[i], ExplosionRect) ){
            cout << mainRect[i].x << " " << mainRect[i].y << " " << mainRect[i].w << " " << mainRect[i].h << " "
                 << ExplosionRect.x << " " << ExplosionRect.y << " " << ExplosionRect.w << " " << ExplosionRect.h << endl;
            FirePlay.setLose(true); WaterPlay.setLose(true);
        }
    }

    //check with enemy
    for (int i = 0; i < (int) enemies_list.size(); i++){
        if ( check_collision(enemies_list[i].get_current_pos(), ExplosionRect) ){
            enemies_list[i].DeleteEnemy();
        }
    }
}





