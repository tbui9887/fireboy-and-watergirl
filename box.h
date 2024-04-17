
#ifndef BOX_H_
#define BOX_H_

#include "header.h"
#include "texture.h"
#include "game_map.h"

class Box : public LTexture
{
private:
    float x_pos, y_pos;
    int box_width, box_height;
    float x_val, y_val;

    bool on_ground_ = false;
public:
    Box(int x, int y);
    ~Box();

    bool loadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);

    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);
};


#endif // BOX_H_
