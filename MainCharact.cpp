#include "common_func.h"
#include "MainCharact.h"

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
    //defaut
}

MainObject::~MainObject()
{

}

bool MainObject::loadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::loadImg(path, screen);

    if (ret == true){
        width_frame_ = ORect.w / frame_main_character; //frame nguoi chuyen dong co 8 pic
        width_frame_ = ORect.h;
    }

}

void MainObject::set_clips()
{
    if (width_frame_ > 0 & height_frame_ > 0){
        frame_clip_[0].
    }
}
