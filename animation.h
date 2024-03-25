
#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "header.h"
#include "texture.h"

class Animate : public LTexture
{
public:
    bool loadFromFile(string path, SDL_Renderer* screen);
    void set_clips();
    virtual void Show(SDL_Renderer* screen);
    Animate();
    ~Animate();
private:
    int frame;
    int num_clips;
    int x_pos, y_pos;
    int width_frame, height_frame;
    SDL_Rect clip[MAX_CLIPS];
};
#endif // ANIMATION_H_
