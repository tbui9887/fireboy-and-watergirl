
#ifndef MAIN_CHARACT_H_
#define MAIN_CHARACT_H_

#include "header.h"
#include "texture.h"
#include "game_map.h"

const int max_below_liquid = 10;

struct Input
{
    int left_;
    int right_;
    int up_;
    int jump_;
    int stand_;
};

enum WalkType //trạng thái đi của nhân vật
    {
        FIRE_WALK_RIGHT,
        FIRE_WALK_LEFT,
        WATER_WALK_RIGHT,
        WATER_WALK_LEFT,
        FIRE_STAND,
        WATER_STAND,
        FIRE_JUMP,
        WATER_JUMP
    };

class MainObject : public LTexture
{
public:
    MainObject();
    ~MainObject();

    bool loadFromFile(std::string path, SDL_Renderer* screen); //tải ảnh nhân vật lên (kế thừa từ Texture)
    void set_clips(); //cắt ảnh từ cái ảnh dài của nhân vật
    void Show(SDL_Renderer* screen); //để render ra màn hình
    void HandleInputAction(SDL_Event event, SDL_Renderer* screen, CHARACTER character); //2 con khác nhau nên dùng CHARACTER để phân biệt 2 con

    void DoPlayer(Map& map_data); //check kiểm tra va chạm
    void check_to_map(Map& map_data); //check vào map
    //bool check_collision_horizontal (SDL_Rect bRect); //bRect: barrier
    SDL_Rect getRectChar();
    void setRectchar(int, int);

    int getXval() { return x_val_; }
    int getYval() { return y_val_; }
    int getXpos() { return x_pos_; }
    int getYpos() { return y_pos_; }

    void setXpos(int x) { x_pos_ = x; }
    void setYpos(int y) { y_pos_ = y; }
    void setXval(int x) { x_val_ = x; }
    void setYval(int y) { y_val_ = y; }

    void setLose(bool boo) { lose = boo; }
    bool getLose() { return lose; }
    void setWin(bool boo) { win = boo; }
    bool getWin() { return win; }

    void coin_increase() { coin++; }
    int get_coin() { return coin; }
    void set_coin(int x) { coin = x; }
    bool check_liquid(int val_1, int val_2, CHARACTER char_main);

    void setCharacter(CHARACTER charact) { character = charact; }
    CHARACTER getCharacter() { return character; }
    void loadChunk();

private:
    float x_val_; //vận tốc theo chiều ngang
    float y_val_; //vận tốc theo chiều dọc

    float x_pos_; //vị trí của nhân vật (góc trái trên)
    float y_pos_;

    int width_frame_; //chiều rộng của frame
    int height_frame_; //chiều cao của frame

    SDL_Rect clip_walk[frame_main_character_walk]; //sau khi dùng hàm set_clip xong thì lưu hình chữ nhật vào đây (đi)
    SDL_Rect clip_stand[frame_main_character_stand]; //đứng

    Input input_type_; //trạng thái input
    int frame_; //lưu frame hiện tại
    int status_; //lưu trạng thái
    CHARACTER character; //nhân vật (lửa hay nước)

    bool on_ground = false;
    bool on_fan = false;
    bool on_button = false;
    int barrier_move = 0;

    int coin;
    int below_liquid = 0;

    bool lose = false, win = false;
};

#endif // MAIN_CHARACT_H_
