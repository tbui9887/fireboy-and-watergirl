#include "select_menu.h"
#include "enermy.h"

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

string LevelMap (MainObject &player_1, MainObject &player_2)
{
    string map_path;

    int mode = ChooseGamePlayMode();
    int level;
    if (mode == CHOOSE_LEVEL){
        level = ChooseLevel();
    }
    else{
        level = Randomlevel();
    }

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

           break;
        }
    case LEVEL2:
        {
            map_path = "Data/map/MapLevel2.txt";
            player_1.setXpos(130);
            player_1.setYpos(672);

            player_2.setXpos(63);
            player_2.setYpos(672);

            break;

        }
    case LEVEL3:
        {
            map_path = "Data/map/MapLevel3.txt";
            player_1.setXpos(250);
            player_1.setYpos(93);

            player_2.setXpos(141);
            player_2.setYpos(360);
        }
    }
    return map_path;
}
