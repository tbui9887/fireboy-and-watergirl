
#ifndef ENEMY_H_
#define ENEMY_H_

#include "header.h"
#include "texture.h"
#include "game_map.h"
#include "character.h"

#define ENEMY_GRAVITY_SPEED 0.8
#define ENEMY_MOVING_SPEED 2

enum TypeMove
{
    STANDING_ENEMY,
    MOVING_IN_SPACE
};

class Enemy : public LTexture
{
public:
    Enemy();
    Enemy(int x, int y);
    ~Enemy();
    void DeleteEnemy();

    void set_x_val(const float& xVal) { x_val_ = xVal; }
    void set_y_val(const float& yVal) { y_val_ = yVal; }
    void set_x_pos(const float& xp) { x_pos_ = xp; }
    void set_y_pos(const float& yp) { y_pos_ = yp; }

    float get_x_pos() const { return x_pos_; }
    float get_y_pos() const { return y_pos_; }

    void set_clips();
    virtual bool loadImg(string path, SDL_Renderer* screen);
    virtual void Show (SDL_Renderer* screen);
    int get_width_frame() const { return width_frame_; }
    int get_height_frame() const { return height_frame_; }

    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);

    void setTypeMove(const int& typeMove) { type_move_ = typeMove; }
    void setMovingpos(const int& pos_start, const int& pos_end) { start_move = pos_start; end_move = pos_end; }
    void controlMoving(SDL_Renderer* screen,  string left_animation_Enemy, string right_animation_Enemy);

    SDL_Rect get_current_pos() { current_pos = {int(x_pos_), int(y_pos_), width_frame_, height_frame_} ; return current_pos; }

private:
    int frame_;
    int width_frame_;
    int height_frame_;
    SDL_Rect frame_clip_[8]; //4 la so frame
    bool on_ground_;
    float x_pos_;
    float y_pos_;
    float x_val_;
    float y_val_;

    int type_move_;
    int start_move;
    int end_move;

    Input input_type_;
    SDL_Rect current_pos;
};

bool check_collision(SDL_Rect charRect, SDL_Rect button);


#endif // Enemy_H_
