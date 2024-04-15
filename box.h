
#ifndef BOX_H_
#define BOX_H_

#include "header.h"
#include "enemy.h"

class Box : public Enemy
{
private:
    int x_box, y_box, w_box, h_box;
    bool on_ground_ = false;
public:
    Box(int x, int y);
    ~Box();

    bool loadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
};


#endif // BOX_H_
