#include "header.h"
#include "character.h"
#include "game_map.h"
#include "button.h"
#include "texture.h"
#include "timer.h"
#include "object_button.h"
#include "enermy.h"
#include "text.h"

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

LTexture gBackground;
GameMap gMap;
MainObject Water(0,0);
MainObject Fire(0,64);
LTimer fps_timer;
Object obj_data;
Enermy enmy(100,64); //enermy
Enermy moving_enmy(200,64);

Text time_count;

bool on_button = false;
bool on_ebutton = false;

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        gWindow = SDL_CreateWindow("fireboy and watergirl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1")) printf("Wanrning: SDL_GetError: %s\n", SDL_GetError());
        if (gWindow == NULL){
            printf("SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else{
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) printf("SDL_Error: %s\n", SDL_GetError());
            else{
                SDL_SetRenderDrawColor(gRenderer,255,255,255,0.8);
            }
            int FlagImg = IMG_INIT_JPG;
            if (!(FlagImg & IMG_Init(FlagImg))){
                printf("IMG_Error: %s\n", IMG_GetError());
                success = false;
            }
            if (TTF_Init() == -1){
                cout << "can't init ttf\n";
                success = false;
            }
        }
    }

    //set font_renderer
    gFont = TTF_OpenFont("Data/font/Mario-Party-Hudson-Font.ttf", 30);
    if (gFont == NULL){
        success = false;
        cout << "can't open font\n";
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    //load background
    gBackground.loadFromFile("Data/photo/background/background.png",gRenderer);

    //load map
    gMap.LoadMap("Data/map/update_map_easy.txt");
    gMap.LoadTiles(gRenderer);

    //load watergirl character
    Water.loadFromFile("Data/photo/character/water_girl_stand.png", gRenderer);
    Water.set_clips();

    //load fireboy character
    Fire.loadFromFile("Data/photo/character/fire_boy_stand.png", gRenderer);
    Fire.set_clips();

    //load object barrier and button
    obj_data.loadImg(gRenderer, "Data/photo/block/button.png", "Data/photo/block/barrier.png");
    obj_data.setYbar(Y_BARRIER);

    //load enemy just standing
    if ( ! enmy.loadImg("Data/photo/character/water_girl_stand.png", gRenderer) ) cout << "can't load enermy photo !\n";
    enmy.set_clips();

    //load enemy can move
    if (! moving_enmy.loadImg("Data/photo/character/fire_boy_walk_left.png", gRenderer) ) cout << "can't load moving enemy photo !\n";
    moving_enmy.set_clips();
    moving_enmy.setTypeMove(MOVING_IN_SPACE);
    moving_enmy.setMovingpos(200 - MAX_MOVING_ENERMY, 200);

    return success;
}
void close()
{
    gBackground.~LTexture();
    Fire.~LTexture();
    Water.~LTexture();


    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gRenderer = NULL;
    gWindow = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}
int main(int argc, char* args[])
{
    if (!init()) return -1;
    else{

        if (!loadMedia()) return -1;
        else{
            bool quit = false;
            SDL_Event event;

            int startTime = 0;

            std::stringstream timeText;

            while (!quit){
                fps_timer.start();
                while (SDL_PollEvent(&event) != 0){ //event click quit and key related to main character
                    if (event.type == SDL_QUIT) quit = true;
                    Fire.HandleInputAction(event, gRenderer, FIREBOY);
                    Water.HandleInputAction(event, gRenderer, WATERGIRL);

                }
                //time counting
                timeText.str("");
                timeText << "TIME: " << set_standard_time( SDL_GetTicks() - startTime );
                time_count.setText(timeText.str());
                //set color for time_count
                time_count.setTextColor(WHITE_TEXT);

                //Update screen
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0.8);
                SDL_RenderClear(gRenderer);

                //render background
                gBackground.render(0, 0, NULL, gRenderer);

                //render map
                gMap.DrawMap(gRenderer);
                Map map_data = gMap.getMap();

                //render barrier and button
                obj_data.render(gRenderer);

                //main character
                Fire.DoPlayer(map_data);
                SDL_Rect FireRect = Fire.getRectChar();
                Fire.Show(gRenderer);

                Water.DoPlayer(map_data);
                SDL_Rect WaterRect = Water.getRectChar();
                Water.Show(gRenderer);

                //enemy and check collision of it
                enmy.DoPlayer(map_data);
                enmy.Show(gRenderer);

                moving_enmy.DoPlayer(map_data);
                moving_enmy.controlMoving(gRenderer, "Data/photo/character/fire_boy_walk_left.png", "Data/photo/character/fire_boy_walk_right.png");
                moving_enmy.Show(gRenderer);

                SDL_Rect enmy_rect = moving_enmy.get_current_pos();

                if ( check_collision(FireRect, enmy_rect) || check_collision(WaterRect, enmy_rect) ) cout << "lose \n"; //check xem neu cham vao co lose khong


                //check collision of button
                SDL_Rect button = obj_data.getButRect();

                if (check_collision(FireRect,button) || check_collision(WaterRect,button)){
                    on_button = true;
                }
                else{
                    on_button = false;
                }

                //activity related to button, barrier and character
                obj_data.activity(Fire,on_button);
                obj_data.activity(Water,on_button);

                //render time_count
                if ( ! time_count.CreateGameText(gFont, gRenderer, ( SCREEN_WIDTH - time_count.getWidth() ) / 2, 0 ) ) {
                    cout << "can't create time count !\n";
                }

                SDL_RenderPresent(gRenderer); //show to screen

                //set fps
                int frameTicks = fps_timer.get_ticks();
                if (frameTicks < SCREEN_TICKS_PER_FRAME){
                    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);

                }
            }
        }
    }
    close();
    return 0;
}
