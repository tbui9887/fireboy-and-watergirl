
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "common_func.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void setRect(int x, int y) { ORect.x = x; ORect.y = y; }
    SDL_Rect GetRect() { return ORect; } //chỉ lấy ra mà không thay đổi
    SDL_Texture* GetTexture() { return OTexture; }

    virtual bool loadImg(std::string path, SDL_Renderer* gRenderer);
    void Render(SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);
    void free();

private:
    SDL_Texture* OTexture;
    SDL_Rect ORect;
};
#endif // BASE_OBJECT_H_
