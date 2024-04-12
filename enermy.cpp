
#include "enermy.h"

Enermy::Enermy(int x, int y)
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_pos_ = x;
    y_pos_ = y;
    x_val_ = 0;
    y_val_ = 0;
    frame_ = 0;
    on_ground_ = 0;

    start_move = 0;
    end_move = 0;
    input_type_.left_ = 1;
    type_move_ = STANDING_ENERMY;
}

Enermy::~Enermy()
{

}

bool Enermy::loadImg(string path, SDL_Renderer* screen)
{
    bool ret = LTexture::loadFromFile(path, screen);
    if (ret){
        width_frame_ = ENEMY_WIDTH;
        height_frame_ = ENEMY_HEIGHT;
    }
    return ret;
}

void Enermy::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0){
            for (int i = 0; i < ENEMY_CLIPS; i++){
                frame_clip_[i].x = width_frame_*i;
                frame_clip_[i].y = 0;
                frame_clip_[i].w = width_frame_;
                frame_clip_[i].h = height_frame_;
            }
    }
}

void Enermy::Show(SDL_Renderer* screen)
{
    LTexture::SetRect(x_pos_, y_pos_);

    frame_++;
    if (frame_ >= ENEMY_CLIPS*10){
        frame_ = 0;
    }

    SDL_Rect* current_clip = &frame_clip_[frame_ / 10];

    SDL_Rect rRect = LTexture::getRect();
    rRect.w /= ENEMY_CLIPS;
    SDL_Texture* rTexture = LTexture::getTexture();

    SDL_Rect renderQuad = {rRect.x, rRect.y, rRect.w, rRect.h};
    SDL_RenderCopy(screen, rTexture, current_clip, &renderQuad);
}

void Enermy::DoPlayer(Map& gMap)
{
    x_val_ = 0;
    y_val_ += ENERMY_GRAVITY_SPEED;

    if (input_type_.left_ == 1 && type_move_ == MOVING_IN_SPACE){
        x_val_ -= ENERMY_MOVING_SPEED;
    }
    else if (input_type_.right_ == 1 && type_move_ == MOVING_IN_SPACE){
        x_val_ += ENERMY_MOVING_SPEED;
    }

    CheckToMap(gMap);
}

void Enermy::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // Check horizontally
    int height_min = height_frame_ < BLOCK_SIZE ? height_frame_ : BLOCK_SIZE;

    x1 = (x_pos_ + x_val_) / BLOCK_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_) / BLOCK_SIZE;

    y1 = y_pos_ / BLOCK_SIZE;
    y2 = (y_pos_ + height_min) / BLOCK_SIZE;


    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if (x_val_ > 0)
        {
            int value_1 = map_data.tile[y1][x2], value_2 = map_data.tile[y2][x2];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID) )
                {
                    x_pos_ = x1 * BLOCK_SIZE;
                    x_val_ = 0;
                }
        }
        else if (x_val_ < 0)
        {
            int value_1 = map_data.tile[y1][x1], value_2 = map_data.tile[y2][x1];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID) )
                {
                    x_pos_ = (x1 + 1) * BLOCK_SIZE;
                    x_val_ = 0;
                }
        }
    }

    // Check vertically
    int width_min = width_frame_ < BLOCK_SIZE ? width_frame_ : BLOCK_SIZE;
    x1 = (x_pos_ + diff_walk) / BLOCK_SIZE;
    x2 = (x_pos_ + width_min - diff_walk) / BLOCK_SIZE;

    y1 = (y_pos_ + y_val_) / BLOCK_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_) / BLOCK_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            int value_1 = map_data.tile[y2][x1], value_2 = map_data.tile[y2][x2];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID) )
                {
                    y_pos_ = y2 * BLOCK_SIZE - height_frame_;
                    y_val_ = 0;
                    on_ground_ = true;
                }
        }
        else if (y_val_ < 0)
        {
            int value_1 = map_data.tile[y1][x1], value_2 = map_data.tile[y1][x2];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID) )
            {
                    y_pos_ = (y1 + 1) * BLOCK_SIZE;
                    y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > SCREEN_WIDTH)
    {
        x_pos_ = SCREEN_WIDTH - width_frame_ + 1;
    }

}

void Enermy::controlMoving(SDL_Renderer* screen, string left_animation_enermy, string right_animation_enermy)
{
    if (type_move_ == STANDING_ENERMY){
        ;
    }
    else{
        if (on_ground_ == true){
            if (x_pos_ > end_move){
                input_type_.left_ = 1;
                input_type_.right_ = 0;
            }
            else if (x_pos_ < start_move){
                input_type_.left_ = 0;
                input_type_.right_ = 1;
            }
        }
    }

    if ( input_type_.left_ == 1 ){
        loadImg(left_animation_enermy, screen);//tai anh quay ve ben trai len
    }
    else if ( input_type_.right_ == 1 ){
        loadImg(right_animation_enermy, screen); //tai anh quay ben phai
    }

}

bool check_collision(SDL_Rect charRect, SDL_Rect button)
{
    // Kiểm tra va chạm theo cả hai trục x và y
    bool collision = (charRect.x < button.x + button.w &&
                      charRect.x + charRect.w > button.x &&
                      charRect.y < button.y + button.h &&
                      charRect.y + charRect.h > button.y);
    return collision;
}
