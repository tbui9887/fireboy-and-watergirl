

#include "button.h"

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
}

LButton::~LButton()
{

}

void LButton::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{

}
