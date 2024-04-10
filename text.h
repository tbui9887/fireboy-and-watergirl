
#ifndef TEXT_H_
#define TEXT_H_

#include "header.h"
#include "texture.h"

enum TextColor
{
    RED_TEXT = 0,
    WHITE_TEXT = 1,
    BLACK_TEXT = 2,
};

class Text : public LTexture
{
public:
    Text();
    ~Text();

    void setText(const string& text) { str_val = text; }
    void setTextColor(const int& type);
    bool CreateGameText (TTF_Font* font, SDL_Renderer* screen, int x, int y);

private:
    string str_val;
    SDL_Color text_color;
};

#endif // TEXT_H_
