
#include "character.h"

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

bool MainObject::loadFromFile(std::string path, SDL_Renderer* screen)
{
    bool char_pic = LTexture::loadFromFile(path, screen);

    if (char_pic == true){
        //if (status_ == FIRE_STAND || status_ == WATER_STAND || status_ == -1) width_frame_ = ORect.w / frame_main_character_stand;
        width_frame_ = CHARACTER_WIDTH;
        height_frame_ = CHARACTER_HEIGHT;
    }
    return char_pic;
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
        loadFromFile("Data/photo/character/fire_boy_walk_left.png", screen);
    }
    if (status_ == FIRE_WALK_RIGHT){
        loadFromFile("Data/photo/character/fire_boy_walk_right.png", screen);
    }
    if (status_ == WATER_WALK_RIGHT){
        loadFromFile("Data/photo/character/water_girl_walk_right.png", screen);
    }
    if (status_ == WATER_WALK_LEFT){
        loadFromFile("Data/photo/character/water_girl_walk_left.png", screen);
    }
    if (status_ == FIRE_STAND){
        loadFromFile("Data/photo/character/fire_boy_stand.png", screen);
    }
    if (status_ == WATER_STAND){
        loadFromFile("Data/photo/character/water_girl_stand.png", screen);
    }

    if (input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.jump_ == 1){
        frame_++;
        if (frame_ >= frame_main_character_walk) frame_ = 0;
    }
    else if (input_type_.stand_ == 1){
        frame_++;
        if (frame_ >= frame_main_character_stand*10) frame_ = 0; //10 de tua cham lai
    }
    else{
        frame_ = 0;
    }

    LTexture::inrect(x_pos_, y_pos_);

    SDL_Rect* current_clip;
    if (input_type_.stand_ == 1){
        current_clip = &clip_walk[frame_/10]; // 20 de tua cham lai
    }
    else{
        current_clip = &clip_walk[frame_];
    }

    SDL_Rect rRect = LTexture::getRect();
    SDL_Texture* rTexture = LTexture::getTexture();

    SDL_Rect renderQuad = {rRect.x, rRect.y, width_frame_, height_frame_};
    SDL_RenderCopy(screen, rTexture, current_clip, &renderQuad);
}

bool MainObject::check_collision_horizontal(SDL_Rect bRect)
{
    bool collision = false;
    SDL_Rect charact = {x_pos_, y_pos_, width_frame_,  height_frame_};
    if (charact.x + charact.w - diff_walk >= bRect.x && charact.x + charact.w - diff_walk <= bRect.x + bRect.w){
            cout << "collision\n";
            collision = true;
    }
    else if (charact.x + diff_walk >= bRect.x && charact.x + diff_walk <= bRect.x + bRect.w){
            cout << "collision\n";
            collision = true;
    }
    //nếu chỉ có phần trên thì nó thành cửa tự động luôn :)
    if (! (charact.y + charact.h <= bRect.y + bRect.h && charact.y + charact.h >= bRect.y ) ) collision = false;
    else if (! (charact.y + charact.h <= bRect.y + bRect.h && charact.y + charact.h >= bRect.y ) ) collision = false;
    return collision;
}

void MainObject::HandleInputAction(SDL_Event event, SDL_Renderer* screen, CHARACTER character)
{
if (character == FIREBOY){
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
            /*case                                                                                                     SDLK_RIGHT && SDLK_UP:
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

void MainObject::DoPlayer(Map& map_data, Object& obj)
{
    x_val_ = 0;
    y_val_ += GRAVATY; //nếu không ở trên quạt thì có trọng lực

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


    check_to_map(map_data, obj);
}

void MainObject::check_to_map(Map& map_data, Object& obj)
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

   // cout << x1 << " " <<  x2 << " " <<  y1 << " " << y2 << std::endl;

    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if (x_val_ > 0)
        {
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x1 * BLOCK_SIZE;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
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
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2 * BLOCK_SIZE - height_frame_;
                y_val_ = 0;
                on_ground = true;
            }
        }
        else if (y_val_ < 0)
        {
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos_ = (y1 + 1) * BLOCK_SIZE;
                y_val_ = 0;
            }
        }
    }

    if (map_data.tile[y2][x1] == LAVA_TILE|| map_data.tile[y2][x2] == LAVA_TILE)
        {
          cout << "LOSE\n";
        }
    //check fan

    if (map_data.tile[y2][x1] == 5|| map_data.tile[y2][x2] == 5){ //nếu chỉ có cái này, nó chỉ check ở dưới chân của nó có block kia khôgn thì mới giảm thôi (thích hợp để làm cái nhún)
        y_val_ -= BLOCK_SIZE/3;
    }

    //end

    //button
    SDL_Rect button = obj.ButRect();
    SDL_Rect barrier = obj.BarRect();

    if (check_collision_horizontal(button) && barrier_move < MAX_MOVE){
        int zy = obj.getYbar();
        obj.changeYbar(zy - 10);
        //example is 10
        barrier_move += 10;
        cout << barrier_move << std::endl;
    }
    else if (!check_collision_horizontal(button) && barrier_move > 0){
        int zy = obj.getYbar();
        obj.changeYbar(zy + 10);
        barrier_move -= 10;
    }

    //end
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


