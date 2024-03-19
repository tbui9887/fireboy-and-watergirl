#include "common_func.h"
#include "MainCharact.h"
#include "game_map.h"

MainObject::MainObject(float x, float y)
{
    frame_ = 0;
    x_pos_ = x;
    y_pos_ = y;
    x_val_ = 0;
    y_val_ = 0;

    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;

    input_type_.jump_ = 0;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.stand_ = 0;
    input_type_.up_ = 0;
    //defaut
}

MainObject::~MainObject()
{
    free();
}

bool MainObject::loadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::loadImg(path, screen);

    if (ret == true){
        //if (status_ == FIRE_STAND || status_ == WATER_STAND || status_ == -1) width_frame_ = ORect.w / frame_main_character_stand;
        width_frame_ = 32;
        height_frame_ = 52;
    }
    return ret;
}

void MainObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0){
            for (int i = 0; i < frame_main_character_walk; i++){
                clip_walk[i].x = width_frame_*i;
                clip_walk[i].y = 0;
                clip_walk[i].w = width_frame_;
                clip_walk[i].h = height_frame_;
            }
    }
}

void MainObject::Show(SDL_Renderer* screen)
{
    if (status_ == FIRE_WALK_LEFT){
        loadImg("Data/photo/character/fire_boy_walk_left.png", screen);
    }
    if (status_ == FIRE_WALK_RIGHT){
        loadImg("Data/photo/character/fire_boy_walk_right.png", screen);
    }
    if (status_ == WATER_WALK_RIGHT){
        loadImg("Data/photo/character/water_girl_walk_right.png", screen);
    }
    if (status_ == WATER_WALK_LEFT){
        loadImg("Data/photo/character/water_girl_walk_left.png", screen);
    }
    if (status_ == FIRE_STAND){
        loadImg("Data/photo/character/fire_boy_stand.png", screen);
    }
    if (status_ == WATER_STAND){
        loadImg("Data/photo/character/water_girl_stand.png", screen);
    }

    if (input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.jump_ == 1){
        frame_++;
        if (frame_ >= frame_main_character_walk) frame_ = 0;
    }
    else if (input_type_.stand_ == 1){
        frame_++;
        if (frame_ >= frame_main_character_stand*10) frame_ = 0; //20 de tua cham lai
    }
    else{
        frame_ = 0;
    }

    ORect.x = x_pos_;
    ORect.y = y_pos_;
    SDL_Rect* current_clip;
    if (input_type_.stand_ == 1){
        current_clip = &clip_walk[frame_/10]; // 20 de tua cham lai
    }
    else{
        current_clip = &clip_walk[frame_];
    }
    SDL_Rect renderQuad = {ORect.x, ORect.y, width_frame_, height_frame_};
    SDL_RenderCopy(screen, OTexture, current_clip, &renderQuad);
}

void MainObject::HandleInputAction(SDL_Event event, SDL_Renderer* screen, CHARACTER character)
{
if (character == FIRE_BOY){
    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym)
        {
            case SDLK_RIGHT:
                status_ = FIRE_WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0; // Chắc chắn rằng khi đi sang phải thì không di chuyển sang trái
                input_type_.stand_ = 0;
                break;
            case SDLK_LEFT:
                status_ = FIRE_WALK_LEFT;
                input_type_.left_ = 1;
                input_type_.right_ = 0; // Chắc chắn rằng khi đi sang trái thì không di chuyển sang phải.
                input_type_.stand_ = 0;
                break;
            case SDLK_UP:
                if (on_ground){
                    status_ = FIRE_JUMP;
                    input_type_.jump_ = 1;
                    input_type_.stand_ = 0;
                }
                break;
            /*case SDLK_RIGHT && SDLK_UP:
                input_type_.jump_ = 1;
                input_type_.right_ = 1;
                input_type_.left_ = 0; input_type_.stand_ = 0;
                break;*/
        }
    }
    else if (event.type == SDL_KEYUP) {
        input_type_.stand_ = 1;
        input_type_.left_ = 0; input_type_.right_ = 0; input_type_.jump_ = 0;
        status_ = FIRE_STAND;
        }
}
else{
    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym)
        {
            case SDLK_a:
                status_ = WATER_WALK_LEFT;
                input_type_.left_ = 1;
                input_type_.right_ = 0; // Chắc chắn rằng khi đi sang trái thì không di chuyển sang phải
                input_type_.stand_ = 0;
                break;
            case SDLK_d:
                status_ = WATER_WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0; // Chắc chắn rằng khi đi sang phải thì không di chuyển sang trái
                input_type_.stand_ = 0;
                break;
            case SDLK_w:
                if (on_ground){
                    status_ = WATER_JUMP;
                    input_type_.jump_ = 1;
                    input_type_.stand_ = 0;
                }
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        input_type_.stand_ = 1;
        input_type_.left_ = 0; input_type_.right_ = 0; input_type_.jump_ = 0;
        status_ = WATER_STAND;
    }
}
}

void MainObject::DoPlayer(Map& map_data)
{
    x_val_ = 0;
    y_val_ += GRAVATY; //trong luc - toc do roi,

    if (y_val_ > MAX_GRAVATY){
        y_val_ = MAX_GRAVATY;
    }

    if (input_type_.left_ == 1){
        x_val_ -= PLAYER_SPEED;
    }
    else if (input_type_.right_ == 1){
        x_val_ += PLAYER_SPEED;
    }
    else if (input_type_.jump_ == 1 && on_ground){
        y_val_ -= JUMP_SPEED;
        on_ground = false;
    }
    check_to_map(map_data);
}

void MainObject::check_to_map(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // Check horizontally
    int height_min = height_frame_ < BLOCK ? height_frame_ : BLOCK;

    x1 = (x_pos_ + x_val_) / BLOCK;
    x2 = (x_pos_ + x_val_ + width_frame_) / BLOCK;

    y1 = y_pos_ / BLOCK;
    y2 = (y_pos_ + height_min) / BLOCK;

   // cout << x1 << " " <<  x2 << " " <<  y1 << " " << y2 << std::endl;

    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if (x_val_ > 0)
        {
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x1 * BLOCK;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                x_pos_ = (x1 + 1) * BLOCK;
                x_val_ = 0;
            }
        }
    }

    // Check vertically
    int width_min = width_frame_ < BLOCK ? width_frame_ : BLOCK;
    x1 = (x_pos_ + diff_walk) / BLOCK;
    x2 = (x_pos_ + width_min - diff_walk) / BLOCK;

    y1 = (y_pos_ + y_val_) / BLOCK;
    y2 = (y_pos_ + y_val_ + height_frame_) / BLOCK;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2 * BLOCK - height_frame_;
                y_val_ = 0;
                on_ground = true;
            }
        }
        else if (y_val_ < 0)
        {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos_ = (y1 + 1) * BLOCK;
                y_val_ = 0;
            }
        }
    }

    if (map_data.tile[y2][x1] == LAVA_TILE|| map_data.tile[y2][x2] == LAVA_TILE)
        {
          cout << "LOSE\n";
        }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ + 1;
    }
}

