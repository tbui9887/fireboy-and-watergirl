
#ifndef OBJECT_BUTTON_H
#define OBJECT_BUTTON_H

#include "header.h"
#include "texture.h"
#include "character.h"

#define MAX_MOVE 64

class Object : public LTexture
{
private:
    LTexture button;
    LTexture barrier;

    int x_but, y_but;
    int x_bar;
    int y_bar;
    int barrier_move;

    bool on_button;

public:
    int y_barrier = 0;

    Object();
    Object(int, int, int);
    ~Object() { }
    void loadImg (SDL_Renderer* screen);
    void render (SDL_Renderer* screen);

    SDL_Rect getButRect();
    SDL_Rect getBarRect();

    int getXbar() { return x_bar; }
    int getYbar() { return y_bar; }
    int getXbut() { return x_but; }
    int getYbut() { return y_but; }

    void setXbar(int x) { x_bar = x; }
    void setYbar(int y) { y_bar = y; }
    void setXbut(int x) { x_but = x; }
    void setYbut(int y) { y_but = y; }


    void setButDimension(int, int);
    void setBarDimension(int, int);

    void activity(MainObject &character);

    void setOnButton(bool b) { on_button = b; }

};

bool check_collision(SDL_Rect charRect, SDL_Rect button);

class Elevator : public Object
{
public:
    Elevator();
    ~Elevator();
};

#endif // OBJECT_BUTTON_H
