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
        if (frame_ > frame_main_character_walk*60) frame_ = 0;
        //SDL_Rect* current_clip = &clip_walk[frame_];
        frame_++;
    }
    else if (input_type_.stand_ == 1){
        if (frame_ > frame_main_character_stand*60) frame_ = 0;
        //current_clip = &clip_stand[frame_];
        frame_++;
    }
    else{
        frame_ = 0;
    }

    ORect.x = x_pos_;
    ORect.y = y_pos_;
    SDL_Rect* current_clip = &clip_walk[frame_/60];
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
        input_type_.stand_ = 1;
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
        input_type_.stand_ = 1;
        input_type_.left_ = 0; input_type_.right_ = 0;
        status_ = WATER_STAND;
    }
}
}

void MainObject::DoPlayer(Map& map_data)
{
    x_val_  = 0;
    y_val_ = GRAVATY; //trong luc - toc do roi,

    /*if (y_val_ >= MAX_GRAVATY){
        y_val_ = MAX_GRAVATY;
    }*/

    if (input_type_.left_ == 1){
        x_val_ -= PLAYER_SPEED;
    }
    else if (input_type_.right_ == 1){
        x_val_ += PLAYER_SPEED;
    }
    check_to_map(map_data);
}

void MainObject::check_to_map(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;
    //kiem tra theo chieu ngang

    int y1 = 0;
    int y2 = 0;

    //kiem tra chieu ngang
    int height_min = height_frame_ < BLOCK ? height_frame_ : BLOCK;
    x1 = (x_pos_ + x_val_)/BLOCK; //xem dang o o thu bao nhieu
    x2 = (x_pos_ + x_val_ + width_frame_ -1)/BLOCK; //tranh truong howp x1 == x2 => tao sai so de check va cham (co khi int chuyen ve dang nguyen)

    y1 = (y_pos_)/BLOCK;
    y2 = (y_pos_ + height_min -1)/BLOCK;

    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y){ //dieu kien khong vuot qua ban do
        if (x_val_ > 0 ) //di chuyen sang phai
        {
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2]){
                  x_pos_ = x1*BLOCK;
                  x_val_ = 0;
            }
        else if (x_val_ < 0){
                x_pos_ = x1*BLOCK;
                x_val_ = 0;
            }
        }
    }
    //check vertical
    int width_min = width_frame_ < BLOCK ? width_min : BLOCK;
    x1 = (x_pos_)/BLOCK;
    x2 = (x_pos_ + width_min)/BLOCK;

    y1 = (y_pos_ + y_val_)/BLOCK;
    y2 = (y_pos_ + y_val_ + height_frame_)/BLOCK;

    if (x1>=0 && x2 < MAX_MAP_X && y1 >= 0 && y2< MAX_MAP_Y){
        if (y_val_ > 0){
            if (y_val_ > 0){
                if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE){ //check 2 truong hop neu no o giua hai o
                    y_pos_ = y2 * BLOCK - height_frame_; // Dùng phép gán đúng ở đây
                    y_val_ = 0;
                    on_ground = true;
                }
            }
        }
        else if (y_val_ < 0){
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE){
                y_pos_ = (y1+1)*BLOCK;
                y_val_ = 0;
            }
        }
    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0){
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_){
        x_pos_ = map_data.max_x_ + width_frame_ -1;
        }
    }
}
