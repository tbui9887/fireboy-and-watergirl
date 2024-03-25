#include "texture.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;

    mRect = {0, 0, mWidth, mHeight};
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* screen)
{
    free();

    bool success = true;
    SDL_Texture* new_texture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL){
        cout << SDL_GetError();
        success = false;
    }
    else{
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, TRANSPARENT_RED, TRANSPARENT_GREEN, TRANSPARENT_BLUE));
        new_texture = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (new_texture == nullptr){
            cout << SDL_GetError();
            success = false;
        }
        else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
            mTexture = new_texture;
        }
    }
    SDL_FreeSurface(loadedSurface);

    return success;
}

void LTexture::free()
{
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;

    mWidth = 0;
    mHeight = 0;
}

int LTexture::getHeight() { return mHeight; }

int LTexture::getWidth() { return mWidth; }

void LTexture::render (int x, int y, SDL_Rect* clip, SDL_Renderer* screen)
{
    SDL_Rect renderQuad = {x, y, this->mWidth, this->mHeight};
    if (clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(screen, mTexture, clip, &renderQuad);
}

void LTexture::inrect(int x, int y)
{
    mRect.x = x;
    mRect.y = y;
    mRect.w = mWidth;
    mRect.h = mHeight;
}

void LTexture::inwidth(int x)
{
    mWidth = x;
}

void LTexture::inheight(int x)
{
    mHeight = x;
}
