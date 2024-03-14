

#include "common_func.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
    ORect.x = 0;
    ORect.y = 0;
    ORect.w = 0;
    ORect.h = 0;
    OTexture = NULL;
}

BaseObject::~BaseObject()
{
    free();
}

bool BaseObject::loadImg (std::string path, SDL_Renderer* gRenderer)
{
    free();
    bool success = true;
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL){
        printf("Can't load surface. IMG_Error: %s\n", IMG_GetError());
        success = false;
    }
    else{
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,DelR,DelG,DelB));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL){
            printf("Can't create texture from surface. SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else{
            ORect.w = loadedSurface->w;
            ORect.h = loadedSurface->h;
            SDL_FreeSurface(loadedSurface);
        }
    }
    OTexture = newTexture;
    return success;
    ;
}

void BaseObject::Render(SDL_Renderer* gRenderer, SDL_Rect* clip){
    SDL_Rect renderQuad = { ORect.x, ORect.y , ORect.w, ORect.h};
    SDL_RenderCopy(gRenderer, OTexture, clip, &renderQuad);
}

void BaseObject::free(){
    if (OTexture != NULL){
        SDL_DestroyTexture(OTexture);
        OTexture = NULL;
        ORect.x = 0;
        ORect.y = 0;
    }
}
