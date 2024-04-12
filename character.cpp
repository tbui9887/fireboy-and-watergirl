
#include "character.h"

MainObject::MainObject()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
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

    LTexture::SetRect(x_pos_, y_pos_);

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
    y_val_ += GRAVITY; //nếu không ở trên quạt thì có trọng lực

    if (y_val_ > MAX_GRAVITY){
        y_val_ = MAX_GRAVITY;
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
        if ( (value_1 == YELLOW_COIN || value_2 == YELLOW_COIN ) && character == FIREBOY){
            map_data.tile[y1][x2] = BLANK_TILE;
            map_data.tile[y2][x2] = BLANK_TILE;
            coin_increase();
        }

        if ( (value_1 == BLUE_COIN || value_2 == BLUE_COIN) && character == WATERGIRL) {
            map_data.tile[y1][x2] = BLANK_TILE;
            map_data.tile[y2][x2] = BLANK_TILE;
            coin_increase();
        }

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
        if (check_liquid (value_1, value_2, character)){
            cout << "LOSE !\n";
        }
        }
        else if (x_val_ < 0)
        {
        int value_1 = map_data.tile[y1][x1], value_2 = map_data.tile[y2][x1];

        if ( (value_1 == YELLOW_COIN || value_2 == YELLOW_COIN ) && character == FIREBOY){
            map_data.tile[y1][x1] = BLANK_TILE;
            map_data.tile[y2][x1] = BLANK_TILE;
            coin_increase();
        }

        if ( (value_1 == BLUE_COIN || value_2 == BLUE_COIN) && character == WATERGIRL) {
            map_data.tile[y1][x1] = BLANK_TILE;
            map_data.tile[y2][x1] = BLANK_TILE;
            coin_increase();
        }
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
            if (check_liquid (value_1, value_2, character)){
                cout << "LOSE !\n";
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

        if ( (value_1 == YELLOW_COIN || value_2 == YELLOW_COIN ) && character == FIREBOY){
            map_data.tile[y2][x1] = BLANK_TILE;
            map_data.tile[y2][x2] = BLANK_TILE;
            coin_increase();
        }

        if ( (value_1 == BLUE_COIN || value_2 == BLUE_COIN) && character == WATERGIRL) {
            map_data.tile[y2][x1] = BLANK_TILE;
            map_data.tile[y2][x2] = BLANK_TILE;
            coin_increase();
        }

        if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
              value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
              value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ) ||
            !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
              value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
              value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID) )
            {
                y_pos_ = y2 * BLOCK_SIZE - height_frame_;
                y_val_ = 0;
                on_ground = true;
            }

            if (check_liquid (value_1, value_2, character)){
                cout << "LOSE !\n";
            }
        }
        else if (y_val_ < 0)
        {
            int value_1 = map_data.tile[y1][x1], value_2 = map_data.tile[y1][x2];

        if ( (value_1 == YELLOW_COIN || value_2 == YELLOW_COIN ) && character == FIREBOY){
            map_data.tile[y1][x1] = BLANK_TILE;
            map_data.tile[y1][x2] = BLANK_TILE;
            coin_increase();
        }

        if ( (value_1 == BLUE_COIN || value_2 == BLUE_COIN) && character == WATERGIRL) {
            map_data.tile[y1][x1] = BLANK_TILE;
            map_data.tile[y1][x2] = BLANK_TILE;
            coin_increase();
        }

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
        if (check_liquid (value_1, value_2, character)){
            cout << "LOSE !\n";
        }
    }

    //check fan
    int block_below_1 = map_data.tile[y2][x1];
    int block_below_2 = map_data.tile[y2][x2];

    if (block_below_1 == 5|| block_below_2 == 5){ //nếu chỉ có cái này, nó chỉ check ở dưới chân của nó có block kia khôgn thì mới giảm thôi (thích hợp để làm cái nhún)
        y_val_ -= BLOCK_SIZE/3;
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
} }

void MainObject::setRectchar(int x, int y)
{
    x_pos_ = x;
    y_pos_ = y;
}

SDL_Rect MainObject::getRectChar()
{
    SDL_Rect character;
    character.x = x_pos_;
    character.y = y_pos_;
    character.w = width_frame_;
    character.h = height_frame_;
    return character;
}

bool MainObject::check_liquid(int val_1, int val_2, CHARACTER char_main)
{
    bool lose = false;

    if ( (val_1 == WATER_FRONT_LIQUID || val_2 == WATER_FRONT_LIQUID ||
          val_1 == WATER_MIDDLE_LIQUID || val_2 == WATER_MIDDLE_LIQUID ||
          val_1 == WATER_END_LIQUID || val_2 == WATER_END_LIQUID)
        && char_main == FIREBOY ){
        cout << "lose from fireboy when stand in water\n";
        lose = true;
    }
    if ( (val_1 == FIRE_FRONT_LIQUID || val_2 == FIRE_FRONT_LIQUID ||
          val_1 == FIRE_MIDDLE_LIQUID || val_2 == FIRE_MIDDLE_LIQUID ||
          val_1 == FIRE_END_LIQUID || val_2 == FIRE_END_LIQUID)
        && char_main == WATERGIRL ){
        cout << "lose from watergirl when stand in fire\n";
        lose = true;
    }
    if ( (val_1 == TOXIC_FRONT_LIQUID || val_2 == TOXIC_FRONT_LIQUID ||
          val_1 == TOXIC_MIDDLE_LIQUID || val_2 == TOXIC_MIDDLE_LIQUID ||
          val_1 == TOXIC_END_LIQUID || val_2 == TOXIC_END_LIQUID) )
    {
        cout << "lose when fall on toxic\n";
        lose = true;
    }

    return lose;
}

