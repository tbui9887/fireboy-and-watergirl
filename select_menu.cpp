#include "select_menu.h"

Mix_Music *menuMusic;

int ChooseGamePlayMode()
{
    int SelectNum;
    cin >> SelectNum;
    return SelectNum;
}

int ChooseLevel()
{
    int level;
    cin >> level;
    return level;
}

int Randomlevel()
{
    srand(time(NULL));
    int level = rand() % MAX_LEVEL;
    return level;
}

string LevelMap (MainObject &player_1, MainObject &player_2, vector<Object> &obj, vector<Enemy> &enemies_list, SDL_Renderer* screen, const int& level)
{
    string map_path;

    switch(level)
    {
    case LEVEL1:
        {
            //load background differently (not done)
           map_path = "Data/map/MapLevel1.txt";
           player_1.setXpos(64);
           player_1.setYpos(608);

           player_2.setXpos(64);
           player_2.setYpos(703);

           enemies_list.push_back(Enemy(266, 273));
           enemies_list.push_back(Enemy(507, 114));
           enemies_list.push_back(Enemy(130, 532));
           enemies_list.push_back(Enemy(670, 402));

           break;
        }
    case LEVEL2:
        {
            map_path = "Data/map/MapLevel2.txt";
            player_1.setXpos(130);
            player_1.setYpos(672);

            player_2.setXpos(63);
            player_2.setYpos(672);

            enemies_list.push_back(Enemy(631, 675));
            enemies_list.push_back(Enemy(571, 112));
            enemies_list.push_back(Enemy(312, 336));

            Object obj1, obj2;
            obj1.setXbut(864); obj1.setYbut(753);
            obj1.setXbar(546); obj1.setYbar(320);
            obj.push_back(obj1);

            obj2.setXbut(495); obj2.setYbut(145);
            obj2.setXbar(224); obj2.setYbar(32);
            obj.push_back(obj2);

            break;

        }
    case LEVEL3:
        {
            map_path = "Data/map/MapLevel3.txt";
            //set position for water and fire in start game
            player_1.setXpos(250);
            player_1.setYpos(93);

            player_2.setXpos(141);
            player_2.setYpos(360);

            //create enemies and set position for enemies
            enemies_list.push_back(Enemy(152, 93));
            enemies_list.push_back(Enemy(488, 397));

            //set position for obj
            Object obj1;
            obj1.setXbut(141); obj1.setYbut(500);
            obj1.setXbar(461); obj1.setYbar(702);
            obj.push_back(obj1);

        }
    }
                //load enemy, set position, set clips
                for (int i = 0; i < int(enemies_list.size()); i++){
                    enemies_list[i].setTypeMove(MOVING_IN_SPACE);
                    enemies_list[i].setMovingpos( enemies_list[i].get_x_pos() - MAX_MOVING_ENEMY, enemies_list[i].get_x_pos() + MAX_MOVING_ENEMY);
                    enemies_list[i].loadImg("Data/photo/character/red_slime_left.png", screen);
                    enemies_list[i].set_clips();
                }

                //load obj
                for (int i = 0; i < int(obj.size()); i++){
                    obj[i].loadImg(screen);
                }
    return map_path;
}

int ShowMenuStartOrNot(MainObject &Player1, MainObject &Player2, vector<Object> &obj, vector<Enemy> &enemies_list, SDL_Renderer* screen, SDL_Event event, string &path_map, bool &quit) //tí nữa code phần khi bấm vào từng phần lựa chọn thì show ra một cửa sổ mới
{
    menuMusic = Mix_LoadMUS("Data/sound/Menu Music.wav");
    if (menuMusic == NULL) cout << "can't open menuMusic\n";

    enemies_list.clear(); obj.clear();
    LTexture StartMenu;
    if ( ! StartMenu.loadFromFile("Data/photo/background/brick_background.png", screen) ){
        cout << "can't upload brick background\n";
        return -1;
    }

    const int option_type = 3;

    LTexture select_button [option_type];
    if ( ! ( select_button[0].loadFromFile("Data/photo/background/choose_level.png", screen)
            && select_button[2].loadFromFile("Data/photo/background/exit_game.png", screen)
            && select_button[1].loadFromFile("Data/photo/background/random_level.png", screen) ) ){
        cout << "can't upload image of button!\n";
    }

    for (int i = 0; i < option_type; i++){
        select_button[i].SetWidth(MENU_BUTTON_WIDTH);
        select_button[i].SetHeight(MENU_BUTTON_HEIGHT);
        select_button[i].SetRect((SCREEN_WIDTH - MENU_BUTTON_WIDTH)/2, 50+i*MENU_BUTTON_WIDTH);
        select_button[i].ChangeColorTexture(255, 14, 201);
    }

    //bool selected[option_type] = {0,0};
    int x_mouse, y_mouse;
    if (Mix_PlayMusic(menuMusic, -1) == -1){
        cout << "can't play music! \n";
    }
    while (true){
        StartMenu.render(0, 0, NULL, screen);
        for (int i = 0; i < option_type; i++){
            select_button[i].render(select_button[i].getRect().x, select_button[i].getRect().y, NULL, screen);
        while(SDL_PollEvent(&event) != 0){
            switch (event.type)
            {
            case SDL_QUIT:
                    quit = 1;
                    return 0;
            case SDL_MOUSEMOTION:
                x_mouse = event.motion.x;
                y_mouse = event.motion.y;
                for (int i = 0; i < option_type; i++){
                    if (CheckFocusWithRect(x_mouse, y_mouse, select_button[i].getRect())){
                        select_button[i].ChangeColorTexture(160, 160, 0);
                    }
                    else{
                        select_button[i].ChangeColorTexture(255, 14, 201);
                    }

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x_mouse = event.motion.x;
                y_mouse = event.motion.y;

                if (CheckFocusWithRect(x_mouse, y_mouse,select_button[0].getRect())){
                    int if_choose = ShowSelectLevel(screen, event, path_map, Player1, Player2, obj, enemies_list, quit);
                    return if_choose;
                }
                else if (CheckFocusWithRect(x_mouse, y_mouse, select_button[1].getRect())){
                    int level = Randomlevel();
                    path_map = LevelMap(Player1, Player2, obj, enemies_list, screen, level);
                    return 0;
                }
                else if (CheckFocusWithRect(x_mouse, y_mouse, select_button[2].getRect())){
                    quit = true;
                    return 0;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    quit = 1;
                    return 0;
                }
                break;
            default:
                break;
            }
            }
        }
        SDL_RenderPresent(screen); //in order to show to screen
    }
    return 1;
}

int ShowSelectLevel(SDL_Renderer* screen, SDL_Event event, string &path_map, MainObject &Player1, MainObject &Player2, vector<Object> &obj, vector<Enemy> &enemies_list, bool &quit)
{
    //if (ShowMenuStartOrNot(Player1, Player2, obj, enemies_list, screen, event, path_map) == 1) return 1;
    //free luon texture kia luon
    LTexture menu_background;
    if ( ! menu_background.loadFromFile("Data/photo/background/brick_background.png", screen) ){
        cout << "can't upload menu background in ShowSelectLevel function\n";
    }
    const int level_num = 3;
    LTexture level_button [level_num];

    if ( ! (level_button[0].loadFromFile("Data/photo/background/level_1.png", screen)
            && level_button[1].loadFromFile("Data/photo/background/level_2.png", screen)
            && level_button[2].loadFromFile("Data/photo/background/level_3.png", screen)) )
    {
        cout << "can't upload menu button in ShowSelectLevel function\n";
    }

    for (int i = 0; i < level_num; i++){
        level_button[i].SetWidth(MENU_BUTTON_WIDTH);
        level_button[i].SetHeight(MENU_BUTTON_HEIGHT);
        level_button[i].SetRect((SCREEN_WIDTH - MENU_BUTTON_WIDTH)/2, 50+MENU_BUTTON_WIDTH*i);
        level_button[i].ChangeColorTexture(255, 14, 201);
    }

    int x_mouse, y_mouse; //tọa độ của chuột

    while (true){ //để duy trì việc in ra màn hình, khi có tác động (event thì return ra giá trị thôi)
        menu_background.render(0, 0, NULL, screen);
        for (int i = 0; i < level_num; i++){
            level_button[i].render(level_button[i].getRect().x, level_button[i].getRect().y, NULL, screen);
        }
        while(SDL_PollEvent(&event) != 0){
            switch (event.type)
            {
            case SDL_QUIT:
                    quit = 1;
                    return 0; //1 là quit ra ngoài

            case SDL_MOUSEMOTION:
                x_mouse = event.motion.x;
                y_mouse = event.motion.y;
                for (int i = 0; i < level_num; i++){
                    if (CheckFocusWithRect(x_mouse, y_mouse, level_button[i].getRect())){
                        level_button[i].ChangeColorTexture(160, 160, 0);
                    }
                    else{
                        level_button[i].ChangeColorTexture(255, 14, 201);
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                x_mouse = event.motion.x;
                y_mouse = event.motion.y;

                for (int i = 0; i < level_num; i++){
                    if (CheckFocusWithRect(x_mouse, y_mouse, level_button[i].getRect()) ){
                        path_map = LevelMap(Player1, Player2, obj, enemies_list, screen, i); //lay path roi return ve 0 luon (thoat khoi vong lap
                        return 0; //0 là không quit
                    }
                }
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    quit = 1;
                    return 0; //1 là quit ra ngoài
                }
                break;

            //default:
                //break;
            }
        }
        SDL_RenderPresent(screen);
    }
    return 1;
}

bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h){
            return true;
    }
    return false;
}

//menu in game
//restart + back to home (we just need to call show menu start or not and after that, before that we set lose) + pause <resume>

int menu_playing(SDL_Renderer *screen, SDL_Event event, bool quit, vector<Object> &obj, vector<Enemy> &enemies_list, MainObject &Player1, MainObject &Player2, string path_map)
{
    const int num_button = 3;
    LTexture playing_button [num_button];

    if (! (playing_button[0].loadFromFile("Data/photo/background/restart.png", screen)
           && playing_button[1].loadFromFile("Data/photo/background/resume.png", screen)
           && playing_button[2].loadFromFile("Data/photo/background/backmenu.png", screen))){
            cout << "Can't load the file of playing button!\n";
           }
    for (int i = 0; i < num_button; i++){
        playing_button[i].SetWidth(MENU_BUTTON_WIDTH);
        playing_button[i].SetHeight(MENU_BUTTON_HEIGHT);
        playing_button[i].SetRect((SCREEN_WIDTH - MENU_BUTTON_WIDTH)/2, 50+i*MENU_BUTTON_WIDTH);
        playing_button[i].ChangeColorTexture(255, 14, 201);
    }

    int x_mouse, y_mouse;
    while(true){

        for (int i = 0; i < num_button; i++){
            playing_button[i].render(playing_button[i].getRect().x, playing_button[i].getRect().y, NULL, screen);
        }

        while (SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                return 0;
            case SDL_MOUSEMOTION:
                x_mouse = event.motion.x;
                x_mouse = event.motion.y;

                for (int i = 0; i < num_button; i++){
                    if (CheckFocusWithRect(x_mouse, y_mouse, playing_button[i].getRect())){
                        playing_button[i].ChangeColorTexture(160, 160, 0);
                    }
                    else{
                        playing_button[i].ChangeColorTexture(255, 14, 201);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x_mouse = event.motion.x;
                y_mouse = event.motion.y;

                if (CheckFocusWithRect(x_mouse, y_mouse, playing_button[0].getRect())){
                        obj.clear();
                        enemies_list.clear();

                        int level;
                        if (path_map == "Data/map/MapLevel1.txt") level = 0;
                        else if (path_map == "Data/map/MapLevel2.txt") level = 1;
                        else level = 3;

                        path_map = LevelMap(Player1, Player2, obj, enemies_list, screen, level);
                        return 0;
                }
                else if (CheckFocusWithRect(x_mouse, y_mouse, playing_button[1].getRect())){
                        return 0;
                }
                else if (CheckFocusWithRect(x_mouse, y_mouse, playing_button[2].getRect())){
                        obj.clear();
                        enemies_list.clear();

                        /*for (int i = 0; i < obj.size(); i++){
                            cout << obj[i].getXbar();
                        }

                        for (int i = 0; i < enemies_list.size(); i++){
                            cout << enemies_list[i].get_x_pos();
                        }

                        ShowMenuStartOrNot(Player1, Player2, obj, enemies_list, screen, event, path_map, quit);
                        */return 1;
                }
                break;
            default:
                break;
            }
        }
        SDL_RenderPresent(screen);
    }

}


