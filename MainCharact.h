
#ifndef MAIN_CHARACT_H_
#define MAIN_CHARACT_H_

#include "common_func.h"
#include "BaseObject.h"

#define frame_main_character_walk 9
#define frame_main_character_stand 7

struct Input
{
    int left_;
    int right_;
    int up_;
    int jump_;
    int stand;
};

enum WalkType
    {
        FIRE_WALK_RIGHT,
        FIRE_WALK_LEFT,
        WATER_WALK_RIGHT,
        WATER_WALK_LEFT,
        FIRE_STAND,
        WATER_STAND
    };

class MainObject : public BaseObject
{
public:
    MainObject(float x, float y);
    ~MainObject();

    bool loadImg(std::string path, SDL_Renderer* screen);
    void set_clips();
    void Show(SDL_Renderer* screen);
    void HandleInputAction(SDL_Event event, SDL_Renderer* screen, CHARACTER character); //character vi co 2 con nhan vat khac nhau

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect clip_walk[frame_main_character_walk];
    SDL_Rect clip_stand[frame_main_character_stand];
    Input input_type_; //trạng thái input
    int frame_; //lưu frame hiện tại
    int status_; //lưu trạng thái
    CHARACTER character; //luu nhan vat
};

#endif // MAIN_CHARACT_H_
