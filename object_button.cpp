#include "object_button.h"
#include "header.h"

void Object::loadImg(SDL_Renderer* screen)
{
    if (! button.loadFromFile("Data/photo/block/button.png", screen) ){
        cout << "can't upload button photo\n";
    }
    if (! barrier.loadFromFile("Data/photo/block/barrier.png", screen) ){
        cout << "can't upload barrier photo\n";
    }

}

Object::Object()
{
    x_but = X_BUTTON;
    y_but = Y_BUTTON;
    x_bar = X_BARRIER;
    y_bar = Y_BARRIER;
}

void Object::render(SDL_Renderer* screen)
{
    button.render(x_but, y_but, NULL, screen);
    barrier.render(x_bar, y_bar, NULL, screen);
}

SDL_Rect Object::getButRect()
{
    button.SetRect(x_but, y_but);
    SDL_Rect but = button.getRect();
    return but;
}

SDL_Rect Object::getBarRect()
{
    barrier.SetRect(x_bar, y_bar);
    SDL_Rect bar = barrier.getRect();
    return bar;
}

void Object::setButDimension(int w, int h)
{
    button.SetWidth(w);
    button.SetHeight(h);
}

void Object::setBarDimension(int w, int h)
{
    barrier.SetWidth(w);
    barrier.SetHeight(h);
}

void Object::activity(MainObject &character, bool on_button)
{
    SDL_Rect charRect = character.getRectChar();

    SDL_Rect butRect = getButRect();
    butRect.w = BARRIER_WIDTH;
    butRect.h = BARRIER_HEIGHT;

    // Kiểm tra va chạm
    if (check_collision(charRect, butRect) || on_button) {
        if (barrier_move < MAX_MOVE) {
            y_bar -= 10;
            barrier_move += 10;
        }
    } else {
        if (barrier_move > 0) {
            y_bar += 10;
            barrier_move -= 10;
        }
    }

    SDL_Rect barRect = getBarRect();
    int x_val = character.getXval();
    int y_val = character.getYval();
    int x_pos = character.getXpos();
    int y_pos = character.getYpos();

    if (x_val != 0 && check_collision(charRect, barRect)){
        character.setXpos(x_pos - x_val);
    }

    if (y_val != 0 && check_collision(charRect, barRect)){
        character.setYpos(y_pos - y_val);
    }
}




