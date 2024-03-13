
#ifndef MAIN_CHARACT_H_
#define MAIN_CHARACT_H_

#include "common_func.h"
#include "BaseObject.h"

#define frame_main_character 9

struct Input
{
    int left_;
    int right_;
    int up_;
    int jump_;
};

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();
    enum WalkType
    {
        WALK_RIGHT,
        WALK_LEFT,
    };

    bool loadImg(std::string path, SDL_Renderer* screen);
    void set_clips();
    void Show(SDL_Renderer* screen);
    void HandleInputAction(SDL_Event event, SDL_Renderer* screen);

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[frame_main_character]; //rect tung anh mot
    Input input_type_; //trạng thái input
    int frame_; //lưu frame hiện tại
    int status_; //lưu trạng thái
};

#endif // MAIN_CHARACT_H_
