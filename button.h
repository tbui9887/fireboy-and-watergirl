

#ifndef BUTTON_H_
#define BUTTON_H_

#include "header.h"

class LButton
{
private:
    //top left position
    SDL_Point mPosition;

public:
    LButton();
    ~LButton();

    void setPosition(int, int);
    void handleEvent( SDL_Event* e);

};

#endif // BUTTON_H_
