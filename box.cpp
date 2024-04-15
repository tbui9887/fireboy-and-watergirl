#include "box.h"

Box::Box(int x, int y)
{
    x_box = x;
    y_box = y;
    w_box = 0;
    h_box = 0;
}

Box::~Box()
{
    x_box = 0; y_box = 0; w_box = 0; h_box = 0;
    free();
}

bool Box::loadImg(string path, SDL_Renderer* screen)
{
    bool ret = LTexture::loadFromFile(path, screen);
    if (ret){
        w_box = BLOCK_SIZE;
        h_box = BLOCK_SIZE;
    }
    return ret;
}

void Box::Show(SDL_Renderer* screen)
{
    LTexture::render(x_box, y_box, NULL, screen);
}
