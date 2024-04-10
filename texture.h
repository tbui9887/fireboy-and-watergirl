
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
    bool loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* screen);
    void free();

    virtual void render (int x, int y, SDL_Rect* clip, SDL_Renderer* screen);

    void SetRect (int x, int y);
    void SetWidth (int);
    void SetHeight (int);
    void SetTexture(SDL_Texture* temp_texture) { mTexture = temp_texture; }

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
