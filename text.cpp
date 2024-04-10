#include "text.h"

Text::Text()
{
    str_val = "";
}

Text::~Text()
{

}

void Text::setTextColor(const int& type)
{
    if (type == RED_TEXT){
        SDL_Color color = {255, 0, 0};
        text_color = color;
    }
    else if (type == WHITE_TEXT){
        SDL_Color color = {255, 255, 255};
        text_color = color;
    }
    else if (type == BLACK_TEXT){
        SDL_Color color = {0, 0, 0};
        text_color = color;
    }
}

bool Text::CreateGameText (TTF_Font* font, SDL_Renderer* screen, int x, int y)
{
    free();
    bool success = true;

    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    if (text_surface == NULL){
        cout << "can't make surface from ttf\n";
        success = false;
    }
    else{
        SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(screen, text_surface);
        if (temp_texture == NULL){
            cout << "can't create temp_texture\n";
            success = false;
        }
        else{
            SetTexture(temp_texture);
            SetWidth(text_surface->w);
            SetHeight(text_surface->h);
        }
    }
    SDL_FreeSurface(text_surface);

    Text::render(x,y,NULL,screen);
    return success;
}
