#include "common_func.h"
#include "MainCharact.h"

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
    //defaut
}

MainObject::~MainObject()
{

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
       /*if (status_ == FIRE_STAND || status_ == WATER_STAND || status_ == -1){
            for (int i = 0; i < frame_main_character_stand; i++){
                clip_stand[i].x = width_frame_*i;
                clip_stand[i].y = 0;
                clip_stand[i].w = width_frame_;
                clip_stand[i].h = height_frame_;
            }
        }
        else{*/
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

    if (input_type_.left_ == 1 || input_type_.right_ == 1){
        if (frame_ > frame_main_character_walk*35) frame_ = 0;
        //SDL_Rect* current_clip = &clip_walk[frame_];
        frame_++;
    }
    else if (input_type_.stand == 1){
        if (frame_ > frame_main_character_stand) frame_ = 0;
        //current_clip = &clip_stand[frame_];
        frame_++;
    }
    else{
        frame_ = 0;
    }

    ORect.x = x_pos_;
    ORect.y = y_pos_;
    SDL_Rect* current_clip = &clip_walk[frame_/35];
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
                break;
            case SDLK_LEFT:
                status_ = FIRE_WALK_LEFT;
                input_type_.left_ = 1;
                input_type_.right_ = 0; // Chắc chắn rằng khi đi sang trái thì không di chuyển sang phải
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        input_type_.stand = 1;
        input_type_.left_ = 0; input_type_.right_ = 0;
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
                break;
            case SDLK_d:
                status_ = WATER_WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0; // Chắc chắn rằng khi đi sang phải thì không di chuyển sang trái
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        input_type_.stand = 1;
        input_type_.left_ = 0; input_type_.right_ = 0;
        status_ = WATER_STAND;
    }
}
}
