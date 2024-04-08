
#ifndef MENU_H_
#define MENU_H_

#include "header.h"
#include "texture.h"

void menu(SDL_Renderer* screen);

class Letter: public LTexture
{
public:
    LTexture(int, int);
    void HandleMouseButton(SDL_Event e);
private:
    int x, int y;
};

#endif // MENU_H_
