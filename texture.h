
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "header.h"

class LTexture
{
public:
    LTexture();
    ~LTexture();

    //Tải ảnh lên từ địa chỉ path
    virtual bool loadFromFile (std::string path, SDL_Renderer* screen);

    void free();

    virtual void render (int x, int y, SDL_Rect* clip, SDL_Renderer* screen);
    void inrect (int x, int y);
    void inwidth (int);
    void inheight (int);

    int getWidth();
    int getHeight();

    SDL_Rect getRect() {return mRect; }
    SDL_Texture* getTexture() {return mTexture; }

private:
    SDL_Texture* mTexture;
    SDL_Rect mRect;

    int mWidth;
    int mHeight;
};

#endif // TEXTURE_H_
