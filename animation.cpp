

#include "animation.h"

Animate::Animate()
{
    num_clips = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    frame = 0;
}

Animate::~Animate()
{

}

bool Animate::loadFromFile(string path, SDL_Renderer* screen)
{
    bool upload = LTexture::loadFromFile(path, screen);
    if (upload == true){
        width_frame = CHARACTER_WIDTH;
        height_frame = CHARACTER_HEIGHT;
        int total_width = LTexture::getWidth();
        num_clips = total_width / width_frame;
    }
    return upload;
}

void Animate::set_clips()
{
    if (width_frame > 0 && height_frame > 0){
            for (int i = 0; i < num_clips; i++){
                clip[i].x = width_frame*i;
                clip[i].y = 0;
                clip[i].w = width_frame;
                clip[i].h = height_frame;
            }
    }
}

void Animate::Show(SDL_Renderer* screen)
{
    SDL_Rect* currentClip =  &clip[frame];
    LTexture::render(x_pos, y_pos, currentClip, screen);

    frame++;
    if (frame > num_clips){
        frame = 0;
    }
}
