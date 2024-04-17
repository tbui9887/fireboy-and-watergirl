#include "box.h"

Box::Box(int x, int y)
{
    x_pos = x;
    y_pos = y;

    box_width = BLOCK_SIZE;
    box_height = BLOCK_SIZE;

    x_val = 0;
    y_val = 0;
}

Box::~Box()
{
    free();
}

bool Box::loadImg(string path, SDL_Renderer* screen)
{
    bool ret = LTexture::loadFromFile(path, screen);
    if (ret){
        box_width = BLOCK_SIZE;
        box_height = BLOCK_SIZE;
    }
    return ret;
}

void Box::Show(SDL_Renderer* screen)
{
    LTexture::render(x_pos, y_pos, NULL, screen);
}

void Box::DoPlayer(Map &gMap)
{
    x_val = 0.0;
    y_val += 0.8;

    CheckToMap(gMap);
}

void Box::CheckToMap(Map &map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // Check horizontally
    int height_min = box_height < BLOCK_SIZE ? box_height : BLOCK_SIZE;

    x1 = (x_pos + x_val) / BLOCK_SIZE; //vi tri cua character tuong ung voi block tren ban do (phan ben trai)
    x2 = (x_pos + x_val + box_width) / BLOCK_SIZE; //tuong tu nhung phan ben phai

    y1 = y_pos / BLOCK_SIZE;
    y2 = (y_pos + height_min) / BLOCK_SIZE;


    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if (x_val > 0)
        {
            int value_1 = map_data.tile[y1][x2], value_2 = map_data.tile[y2][x2];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ||
                  value_1 == YELLOW_COIN || value_2 == BLUE_COIN) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID ||
                  value_2 == YELLOW_COIN || value_2 == BLUE_COIN) )
                {
                    x_pos = x2 * BLOCK_SIZE;
                    x_pos -= box_width + 1;
                    x_val = 0;
                }
        }
        else if (x_val < 0)
        {
            int value_1 = map_data.tile[y1][x1], value_2 = map_data.tile[y2][x1];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ||
                  value_1 == YELLOW_COIN || value_2 == BLUE_COIN) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID ||
                  value_2 == YELLOW_COIN || value_2 == BLUE_COIN) )
                {
                    x_pos = (x1 + 1) * BLOCK_SIZE;
                    x_val = 0;
                }
        }
    }

    // Check vertically
    int width_min = box_width < BLOCK_SIZE ? box_width : BLOCK_SIZE;
    x1 = (x_pos) / BLOCK_SIZE;
    x2 = (x_pos + width_min) / BLOCK_SIZE;

    y1 = (y_pos + y_val) / BLOCK_SIZE;
    y2 = (y_pos + y_val + box_height - 1) / BLOCK_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val > 0)
        {
            int value_1 = map_data.tile[y2][x1], value_2 = map_data.tile[y2][x2];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ||
                  value_1 == YELLOW_COIN || value_2 == BLUE_COIN) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID ||
                  value_2 == YELLOW_COIN || value_2 == BLUE_COIN) )
                {
                    y_pos = y2 * BLOCK_SIZE;
                    y_pos -= (box_height+1);
                    y_val = 0;
                    on_ground_ = true;
                }
        }
        else if (y_val < 0)
        {
            int value_1 = map_data.tile[y1][x1], value_2 = map_data.tile[y1][x2];
            if (!(value_1 == BLANK_TILE || value_1 == FLOWER_TILE || value_1 == SMALL_ROCK || value_1 == BIG_ROCK || value_1 == BUSH || value_1 == YELLOW_COIN || value_1 == BLUE_COIN ||
                  value_1 == WATER_FRONT_LIQUID || value_1 == FIRE_FRONT_LIQUID || value_1 == TOXIC_FRONT_LIQUID || value_1 == WATER_MIDDLE_LIQUID || value_1 == FIRE_MIDDLE_LIQUID ||
                  value_1 == TOXIC_MIDDLE_LIQUID || value_1 == FIRE_END_LIQUID || value_1 == WATER_END_LIQUID || value_1 == TOXIC_END_LIQUID ||
                  value_1 == YELLOW_COIN || value_2 == BLUE_COIN) ||
                !(value_2 == BLANK_TILE || value_2 == FLOWER_TILE || value_2 == SMALL_ROCK || value_2 == BIG_ROCK || value_2 == BUSH || value_2 == YELLOW_COIN || value_2 == BLUE_COIN ||
                  value_2 == WATER_FRONT_LIQUID || value_2 == FIRE_FRONT_LIQUID || value_2 == TOXIC_FRONT_LIQUID || value_2 == WATER_MIDDLE_LIQUID || value_2 == FIRE_MIDDLE_LIQUID ||
                  value_2 == TOXIC_MIDDLE_LIQUID || value_2 == FIRE_END_LIQUID || value_2 == WATER_END_LIQUID || value_2 == TOXIC_END_LIQUID ||
                  value_2 == YELLOW_COIN || value_2 == BLUE_COIN) )
            {
                    y_pos = (y1 + 1) * BLOCK_SIZE;
                    y_val = 0;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + box_width > SCREEN_WIDTH)
    {
        x_pos = SCREEN_WIDTH - box_width + 1;
    }

}
