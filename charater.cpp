#include "charater.h"

// the state of character
ALLEGRO_BITMAP *backpack_open = NULL;
ALLEGRO_BITMAP *background1 = NULL;
ALLEGRO_BITMAP *background2 = NULL;
ALLEGRO_BITMAP *form_open = NULL;

ALLEGRO_FONT *fgame = NULL;
ALLEGRO_FONT *fbackpack = NULL;
ALLEGRO_FONT *fbattle = NULL;
ALLEGRO_FONT *ftext = NULL;
ALLEGRO_FONT *fform = NULL;

int rtime;
int wall[4150][980];
int flag = 0;
int nowstate = 0;
int HP[2];

int firsttime = 0;
int charadamage;
int enemydamage;

enum {STOP = 0, MOVE, ATK, VILLAGE, MAP, SHOP, BACKPACK, FORM, BATTLE, BOSSROOM, LOSE, WIN, COMPLETE};

typedef struct character{
    int HP, MP;
    int attack;
    int def;
    int speed;
    int atkuse;
    int defuse;
    int money;
    int weapon;
    int killedmon;
    int x, y; // the position of image
    int width, height; // the width and height of image
    int backpack[6];
    bool dir; // left: false, right: true
    int state; // the state of character
    int position;
    ALLEGRO_BITMAP *img_move[3];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    bool openbackpack;
}Character;

typedef struct{
    int x, y;
    int position;
    int menu;
    int buy;
    bool dir;
    bool state;
    bool confirm;
    bool rich;
    ALLEGRO_BITMAP *img_close[1];
    ALLEGRO_BITMAP *img_menu1[3];
    ALLEGRO_BITMAP *img_menu2[3];
}NPC;

typedef struct{
    int menu;
    int position;
    int use;
    bool confirm;
    bool mana;

    ALLEGRO_BITMAP *origin;
    ALLEGRO_BITMAP *fight;
    ALLEGRO_BITMAP *item;

    ALLEGRO_BITMAP *bossorigin;
    ALLEGRO_BITMAP *bossfight;
    ALLEGRO_BITMAP *bossitem;

    ALLEGRO_BITMAP *weapon[7][2];

    ALLEGRO_BITMAP *bossimage;
    ALLEGRO_BITMAP *monster[2];

    ALLEGRO_BITMAP *win;
    ALLEGRO_BITMAP *lose;
    ALLEGRO_BITMAP *complete;

}FIGHT;

typedef struct{
    int HP;
    int attack;
    int def;
    int speed;
}monster_info;

typedef struct{
    int which;
    monster_info number[2];
}MONSTER;




Character chara;
NPC shop;
FIGHT battle;
MONSTER monster;
monster_info BOSS;

ALLEGRO_SAMPLE *sample = NULL;

void buildwall(){

    int i,j;
    for( i=1900; i<=2000; i++)
    {
        for(j=845; j<=855; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=0; i<=145; i++)
    {
        for(j=845; j<=855; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=250; i<=575; i++)
    {
        for(j=845; j<=855; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=785; i<=1000; i++)
    {
        for(j=845; j<=855; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1110; i<=1435; i++)
    {
        for(j=845; j<=855; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1540; i<=1755; i++)
    {
        for(j=845; j<=855; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=40; i<=250; i++)
    {
        for(j=735; j<=745; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=575; i<=895; i++)
    {
        for(j=735; j<=745; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1225; i<=1325; i++)
    {
        for(j=735; j<=745; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1435; i<=1650; i++)
    {
        for(j=735; j<=745; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=1900; i<=2000; i++)
    {
        for(j=620; j<=630; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=0; i<=145; i++)
    {
        for(j=620; j<=630; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=465; i<=680; i++)
    {
        for(j=620; j<=630; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=785; i<=895; i++)
    {
        for(j=620; j<=630; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1000; i<=1325; i++)
    {
        for(j=620; j<=630; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1435; i<=1755; i++)
    {
        for(j=620; j<=630; j++)
        {
            wall[i][j]=1;
        }
    }

//
    for( i=360; i<=680; i++)
    {
        for(j=520; j<=530; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=785; i<=1000; i++)
    {
        for(j=520; j<=530; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1110; i<=1225; i++)
    {
        for(j=520; j<=530; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1540; i<=1650; i++)
    {
        for(j=520; j<=530; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=40; i<=250; i++)
    {
        for(j=405; j<=415; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=360; i<=575; i++)
    {
        for(j=405; j<=415; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=680; i<=895; i++)
    {
        for(j=405; j<=415; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1000; i<=1110; i++)
    {
        for(j=405; j<=415; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=1225; i<=1325; i++)
    {
        for(j=405; j<=415; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=1540; i<=1650; i++)
    {
        for(j=405; j<=415; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=140; i<=465; i++)
    {
        for(j=300; j<=310; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=575; i<=680; i++)
    {
        for(j=300; j<=310; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=895; i<=1225; i++)
    {
        for(j=300; j<=310; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1325; i<=1435; i++)
    {
        for(j=300; j<=310; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1650; i<=1755; i++)
    {
        for(j=320; j<=330; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=145; i<=360; i++)
    {
        for(j=190; j<=200; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=575; i<=785; i++)
    {
        for(j=190; j<=200; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=895; i<=1325; i++)
    {
        for(j=190; j<=200; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1435; i<=1650; i++)
    {
        for(j=190; j<=200; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=40; i<=250; i++)
    {
        for(j=90; j<=100; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=360; i<=465; i++)
    {
        for(j=90; j<=100; j++)
        {
            wall[i][j]=1;
        }
    }


    for( i=680; i<=895; i++)
    {
        for(j=90; j<=100; j++)
        {
            wall[i][j]=1;
        }
    }


    for( i=1325; i<=1435; i++)
    {
        for(j=90; j<=100; j++)
        {
            wall[i][j]=1;
        }
    }


//y繞b
    for( i=30; i<=40; i++)
    {
        for(j=0; j<=90; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=30; i<=40; i++)
    {
        for(j=190; j<=305; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=30; i<=40; i++)
    {
        for(j=410; j<=520; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=135; i<=145; i++)
    {
        for(j=520; j<=625; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=240; i<=255; i++)
    {
        for(j=410; j<=850; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=355; i<=365; i++)
    {
        for(j=0; j<=190; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=355; i<=365; i++)
    {
        for(j=305; j<=740; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=460; i<=465; i++)
    {
        for(j=190; j<=305; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=460; i<=465; i++)
    {
        for(j=625; j<=850; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=570; i<=580; i++)
    {
        for(j=0; j<=190; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=570; i<=580; i++)
    {
        for(j=305; j<=410; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=675; i<=685; i++)
    {
        for(j=410; j<=520; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=675; i<=685; i++)
    {
        for(j=740; j<=955; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=780; i<=790; i++)
    {
        for(j=190; j<=410; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=890; i<=900; i++)
    {
        for(j=90; j<=190; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=890; i<=900; i++)
    {
        for(j=305; j<=410; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=890; i<=900; i++)
    {
        for(j=625; j<=740; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=995; i<=1005; i++)
    {
        for(j=0; j<=90; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=995; i<=1005; i++)
    {
        for(j=410; j<=520; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=995; i<=1005; i++)
    {
        for(j=625; j<=850; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=1105; i<=1115; i++)
    {
        for(j=90; j<=190; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1105; i<=1115; i++)
    {
        for(j=740; j<=850; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=1220; i<=1230; i++)
    {
        for(j=0; j<=90; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1220; i<=1230; i++)
    {
        for(j=305; j<=625; j++)
        {
            wall[i][j]=1;
        }
    }
//

    for( i=1320; i<=1330; i++)
    {
        for(j=190; j<=305; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=1320; i<=1330; i++)
    {
        for(j=410; j<=520; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=1320; i<=1330; i++)
    {
        for(j=625; j<=740; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=1430; i<=1440; i++)
    {
        for(j=0; j<=190; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=1430; i<=1440; i++)
    {
        for(j=305; j<=410; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=1430; i<=1440; i++)
    {
        for(j=740; j<=850; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=1535; i<=1545; i++)
    {
        for(j=0; j<=90; j++)
        {
            wall[i][j]=1;
        }
    }
    for( i=1535; i<=1545; i++)
    {
        for(j=190; j<=520; j++)
        {
            wall[i][j]=1;
        }
    }

    for( i=1535; i<=1545; i++)
    {
        for(j=625; j<=740; j++)
        {
            wall[i][j]=1;
        }
    }
//
    for( i=1645; i<=1655; i++)
    {
        for(j=0; j<=190; j++)
        {
            wall[i][j]=1;
        }
    }

//糧?竄獺穠繙wall
    for( i=1755; i<=1800; i++)
    {
        for(j=0; j<=900; j++)
        {
            wall[i][j]=1;
        }
    }

}

void character_init(){
    // load character images
    rtime = rand()%4;

    char temp[50];
    for(int i = 1 ; i <= 3 ; i++){
        sprintf( temp, "./image/char_move%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        sprintf( temp, "./image/char_atk%d.png", i );
        chara.img_atk[i-1] = al_load_bitmap(temp);
    }

    sprintf( temp, "./image/map.png");
    background1 = al_load_bitmap(temp);

    // load effective sound
    sample = al_load_sample("./sound/atk_sound.wav");
    chara.atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    /*for(int i = 0; i < 6; i++)
    {
        chara.backpack[i] = 10;
    }*/

    chara.HP = 1000;
    chara.MP = 1000;
    chara.attack = 120;
    chara.def = 0;
    chara.speed = 50;
    chara.money = 5000;
    chara.weapon = 0;
    chara.atkuse = 0;
    chara.defuse = 0;
    chara.killedmon = 0;

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = 50;
    chara.y = 500;
    chara.dir = true;
    chara.openbackpack = false;

    // initial the animation component
    chara.state = STOP;
    chara.position = VILLAGE;
    chara.anime = 0;
    chara.anime_time = 30;
    background2= al_load_bitmap("./image/black.png");
}
void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void charater_update(){
    if(chara.position == VILLAGE)
    {
        if( key_state[ALLEGRO_KEY_W] )
        {
            if(chara.y > 0)
            {
                chara.y -= 10;
                chara.state = MOVE;
            }
            else
            {
                chara.state = STOP;
            }
        }
        else if( key_state[ALLEGRO_KEY_A] )
        {
            chara.dir = false;
            if(chara.x > -100)
            {
                chara.x -= 10;
                chara.state = MOVE;
            }
            else
            {
                chara.state = STOP;
            }
        }
        else if( key_state[ALLEGRO_KEY_S] )
        {
            if(chara.y < 900)
            {
                chara.y += 10;
                chara.state = MOVE;
            }
            else
            {
                chara.state = STOP;
            }
        }
        else if( key_state[ALLEGRO_KEY_D] )
        {
            chara.dir = true;
            if(chara.x < 1800)
            {
                chara.x += 10;
                chara.state = MOVE;
            }
            else
            {
                chara.state = STOP;
            }
        }
        else if( key_state[ALLEGRO_KEY_B])
        {
            chara.openbackpack = true;
            chara.position = BACKPACK;
        }
        else if( key_state[ALLEGRO_KEY_C])
        {
            chara.position = FORM;
        }
        else if( key_state[ALLEGRO_KEY_ENTER] && nowstate == 0)
        {
            if(check(chara.x,chara.y) == 1)
            {

                if(chara.x - shop.x < 0)
                {
                    chara.dir = true;

                }
                else
                {
                    chara.dir = false;
                }
                chara.position = SHOP;
                shop.position = 1;
                shop.menu = 1;
                shop.buy = 0;
                shop.confirm = false;
                shop.state = true;
            }
        }//enter
        else if(check(chara.x,chara.y) == 2)
        {
            chara.x = 1;
            chara.y = 905;
            flag = 1;
            nowstate = 1;
            chara.position = MAP;
        }
        else if( chara.anime == chara.anime_time - 1 )
        {
            chara.anime = 0;
            chara.state = STOP;
        }
        else if ( chara.anime == 0 )
        {
            chara.state = STOP;
        }
    }//map end
    else if(chara.position == MAP)
    {
        if(checkmon(chara.x,chara.y) == 1 && nowstate == 1 && HP[0] == 1)
        {
            monster.which = 0;
            firsttime = 0;
            battle.menu = 1;
            battle.confirm = false;
            chara.position = BATTLE;
        }
        else if(checkmon(chara.x,chara.y) == 2 && nowstate == 1 && HP[1] == 1)
        {
            monster.which = 1;
            firsttime = 0;
            battle.menu = 1;
            battle.confirm = false;
            chara.position = BATTLE;
        }
        else if( key_state[ALLEGRO_KEY_W] )
        {
            if(chara.y > 0 && checkwall(chara.x,chara.y))
            {
                chara.y -= 3;
                chara.state = MOVE;
            }
            else
            {
                chara.state = STOP;
            }
        }
        else if( key_state[ALLEGRO_KEY_A] )
        {
            chara.dir = false;
            if(chara.x > -100 && checkwall(chara.x,chara.y))
            {
                chara.x -= 3;
                chara.state = MOVE;
            }
            else
            {
                chara.state = STOP;
            }
        }
        else if( key_state[ALLEGRO_KEY_S] )
        {
            if(chara.y < 900&&checkwall(chara.x,chara.y))
            {
                chara.y += 3;
                chara.state = MOVE;
            }
            else
            {
                chara.state = STOP;
            }
        }
        else if( key_state[ALLEGRO_KEY_D] )
        {
            chara.dir = true;
            if(chara.x < 1800 && checkwall(chara.x,chara.y))
            {
                chara.x += 3;
                chara.state = MOVE;
            }
            else
            {
                chara.state = STOP;
            }
        }
        else if( key_state[ALLEGRO_KEY_SPACE] )
        {
            chara.state = ATK;
        }
        else if( !checkwall(chara.x, chara.y) )
        {
             chara.x = 1;
             chara.y = 905;

        }
        else if( key_state[ALLEGRO_KEY_B])
        {
            chara.openbackpack = true;
            chara.position = BACKPACK;
        }
        else if( key_state[ALLEGRO_KEY_C])
        {
            chara.position = FORM;
        }
        else if(check(chara.x, chara.y) == 3)
        {
            chara.position = BOSSROOM;
        }
        else if( chara.anime == chara.anime_time - 1 )
        {
            chara.anime = 0;
            chara.state = STOP;
        }
        else if ( chara.anime == 0 )
        {
            chara.state = STOP;
        }
    }//map end
    else if(chara.position == SHOP)
    {
        if(shop.menu == 1)
        {
            if(chara.weapon == 0)
            {
                if(key_state[ALLEGRO_KEY_ESCAPE] )
                {
                    chara.position = VILLAGE;
                    shop.state = false;
                }
                else if(key_state[ALLEGRO_KEY_F1])
                {
                    shop.position = 1;
                    shop.menu = 2;
                }
                else if(key_state[ALLEGRO_KEY_F2])
                {
                    shop.position = 2;
                    shop.menu = 2;

                }
                else if(key_state[ALLEGRO_KEY_F3])
                {
                    shop.position = 3;
                    shop.menu = 2;
                }
            }
            else if(chara.weapon >= 0)
            {
                if(shop.confirm)
                {
                    if(key_state[ALLEGRO_KEY_ENTER])
                    {
                        shop.menu = 2;
                        shop.position = 2;
                        chara.attack = 0;
                        shop.confirm = false;
                    }
                    else if(key_state[ALLEGRO_KEY_ESCAPE])
                    {
                        shop.menu = 1;
                        shop.confirm = false;
                    }
                }
                else if(!shop.confirm)
                {
                     if(key_state[ALLEGRO_KEY_ESCAPE] )
                    {
                        chara.position = VILLAGE;
                        shop.state = false;
                    }
                    else if(key_state[ALLEGRO_KEY_F1])
                    {
                        shop.position = 1;
                        shop.menu = 2;
                    }
                    else if(key_state[ALLEGRO_KEY_F2])
                    {
                        shop.menu = 1;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_F3])
                    {
                        shop.position = 3;
                        shop.menu = 2;
                    }
                }

            }
        }
        else if(shop.menu == 2)
        {
            if(shop.confirm == false)
            {
                if(key_state[ALLEGRO_KEY_W])
                {
                    shop.menu = 1;
                    shop.position = 1;
                }
                else if(shop.position == 1)
                {
                    if(key_state[ALLEGRO_KEY_1])
                    {
                        shop.buy = 1;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_2])
                    {
                        shop.buy = 2;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_3])
                    {
                        shop.buy = 3;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_4])
                    {
                        shop.buy = 4;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_5])
                    {
                        shop.buy = 5;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_6])
                    {
                        shop.buy = 6;
                        shop.confirm = true;
                    }
                }
                else if(shop.position == 2)
                {
                    if(key_state[ALLEGRO_KEY_1])
                    {
                        shop.buy = 1;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_2])
                    {
                        shop.buy = 2;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_3])
                    {
                        shop.buy = 3;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_4])
                    {
                        shop.buy = 4;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_5])
                    {
                        shop.buy = 5;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_6])
                    {
                        shop.buy = 6;
                        shop.confirm = true;
                    }
                }
                else if(shop.position == 3)
                {
                    if(key_state[ALLEGRO_KEY_1])
                    {
                        shop.buy = 1;
                        shop.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_2])
                    {
                        shop.buy = 2;
                        shop.confirm = true;
                    }
                }
            }
            else if(shop.confirm == true)
            {
                if(shop.position == 1)
                {
                    if(shop.buy == 1)
                    {
                        if(chara.money >= 10)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER] && chara.backpack[shop.buy - 1] <= 99)
                            {
                                shop.menu = 2;
                                chara.backpack[shop.buy - 1]++;
                                shop.buy = 0;
                                chara.money -= 10;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }

                    }
                    else if(shop.buy == 2)
                    {
                        if(chara.money >= 15)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER] && chara.backpack[shop.buy - 1] <= 99)
                            {
                                shop.menu = 2;
                                chara.backpack[shop.buy - 1]++;
                                shop.buy = 0;
                                chara.money -= 15;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }
                    }
                    else if(shop.buy == 3)
                    {
                        if(chara.money >= 50)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER] && chara.backpack[shop.buy - 1] <= 99)
                            {
                                shop.menu = 2;
                                chara.backpack[shop.buy - 1]++;
                                shop.buy = 0;
                                chara.money -= 50;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }
                    }
                    else if(shop.buy == 4)
                    {
                        if(chara.money >= 50)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER] && chara.backpack[shop.buy - 1] <= 99)
                            {
                                shop.menu = 2;
                                chara.backpack[shop.buy - 1]++;
                                shop.buy = 0;
                                chara.money -= 50;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }
                    }
                    else if(shop.buy == 5)
                    {
                        if(chara.money >= 25)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER] && chara.backpack[shop.buy - 1] <= 99)
                            {
                                shop.menu = 2;
                                chara.backpack[shop.buy - 1]++;
                                shop.buy = 0;
                                chara.money -= 25;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }
                    }
                    else if(shop.buy == 6)
                    {
                        if(chara.money >= 100)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER] && chara.backpack[shop.buy - 1] <= 99)
                            {
                                shop.menu = 2;
                                chara.backpack[shop.buy - 1]++;
                                shop.buy = 0;
                                chara.money -= 100;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }
                    }
                }//buy 1st area item end
                else if(shop.position == 2)
                {
                    if(shop.buy == 1)
                    {
                        if(chara.money >= 1000)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 1;
                                shop.position = 1;
                                chara.weapon = shop.buy;
                                shop.buy = 0;
                                chara.money -= 1000;
                                chara.attack = 100;
                                chara.speed = 10;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }

                    }
                    else if(shop.buy == 2)
                    {
                        if(chara.money >= 1000)
                        {
                            if( key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 1;
                                shop.position = 1;
                                chara.weapon = shop.buy;
                                shop.buy = 0;
                                chara.money -= 1000;
                                chara.attack = 40;
                                chara.def = 20;
                                chara.speed = 20;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }

                    }
                    else if(shop.buy == 3)
                    {
                        if(chara.money >= 2000)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 1;
                                shop.position = 1;
                                chara.weapon = shop.buy;
                                shop.buy = 0;
                                chara.money -= 2000;
                                chara.attack = 200;
                                chara.speed = 50;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }

                    }
                    else if(shop.buy == 4)
                    {
                        if(chara.money >= 2500)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 1;
                                shop.position = 1;
                                chara.weapon = shop.buy;
                                shop.buy = 0;
                                chara.money -= 2500;
                                chara.attack = 1000;
                                chara.speed = 10;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }

                        }
                    }
                    else if(shop.buy == 5)
                    {
                        if(chara.money >= 2300)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 1;
                                shop.position = 1;
                                chara.weapon = shop.buy;
                                shop.buy = 0;
                                chara.money -= 2300;
                                chara.attack = 50;
                                chara.speed = 200;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }

                    }
                    else if(shop.buy == 6)
                    {
                        if(chara.money >= 2700)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 1;
                                shop.position = 1;
                                chara.weapon = shop.buy;
                                shop.buy = 0;
                                chara.money -= 2700;
                                chara.attack = 500;
                                chara.speed = 20;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }

                    }
                }//buy 2nd area item end
                else if(shop.position == 3)
                {
                    if(shop.buy == 1)
                    {
                        if(chara.money >= 500)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER] && chara.backpack[shop.buy - 1] <= 99)
                            {
                                shop.menu = 2;
                                chara.HP = 1000;
                                chara.MP = 1000;
                                shop.buy = 0;
                                chara.money -= 500;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }

                    }
                    else if(shop.buy == 2)
                    {
                        if(chara.money >= 700)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER] && chara.backpack[shop.buy - 1] <= 99)
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                chara.money -= 700;
                                shop.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                            }
                        }
                        else
                        {
                            shop.rich = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                shop.menu = 2;
                                shop.buy = 0;
                                shop.confirm = false;
                                shop.rich = true;
                            }
                        }
                    }
                }//buy 3rd area item end

            }//really want to buy end
        }//shop menu 2 ned
    }//shop end;
    else if(chara.position == BACKPACK)
    {
        if(key_state[ALLEGRO_KEY_ESCAPE])
        {
            if(nowstate == 0)
            {
                chara.position = VILLAGE;
            }
            else
            {
                chara.position = MAP;
            }
            chara.openbackpack = false;
        }
    }//backpack end
    else if(chara.position == FORM)
    {
        if(key_state[ALLEGRO_KEY_ESCAPE])
        {
            if(nowstate == 0)
            {
                chara.position = VILLAGE;
            }
            else
            {
                chara.position = MAP;
            }
        }
    }
    else if(chara.position == BATTLE)
    {
        if(battle.menu == 1)
        {
            if(key_state[ALLEGRO_KEY_F1])
            {
                battle.menu = 2;
                battle.position = 1;
            }
            else if(key_state[ALLEGRO_KEY_F2])
            {
                battle.menu = 2;
                battle.position = 2;
            }
        }
        else if(battle.menu == 2)
        {
            if(battle.confirm == false)
            {
                if(key_state[ALLEGRO_KEY_W])
                {
                    battle.menu = 1;
                }
                else if(battle.position == 1)
                {
                    if(key_state[ALLEGRO_KEY_1])
                    {
                        battle.use = 1;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_2])
                    {
                        battle.use = 2;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_3])
                    {
                        battle.use = 3;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_4])
                    {
                        battle.use = 4;
                        battle.confirm = true;
                    }
                }
                else if(battle.position == 2)
                {
                    if(key_state[ALLEGRO_KEY_1])
                    {
                        battle.use = 1;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_2])
                    {
                        battle.use = 2;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_3])
                    {
                        battle.use = 3;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_4])
                    {
                        battle.use = 4;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_5])
                    {
                        battle.use = 5;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_6])
                    {
                        battle.use = 6;
                        battle.confirm = true;
                    }
                }
            }
            else if(battle.confirm == true)
            {
                if(battle.position == 1)
                {
                    if(battle.use == 1)
                    {
                        if(chara.MP >= 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                battle.use = 0;
                                charadamage = chara.attack * (chara.speed / monster.number[monster.which].speed) + rand() % 50;
                                monster.number[monster.which].HP -= charadamage;
                                if(monster.number[monster.which].HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    HP[monster.which] = 0;
                                    chara.killedmon++;
                                    chara.money += 2000 + rand() % 500;
                                    chara.position = WIN;
                                }
                                else
                                {
                                    monster_update();
                                    battle.confirm = false;
                                }
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                    }
                    else if(battle.use == 2)
                    {
                        if(chara.MP >= 100)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                battle.use = 0;
                                chara.MP -= 100;
                                charadamage = chara.attack * (chara.speed / monster.number[monster.which].speed) + 50 + rand() %100;
                                monster.number[monster.which].HP -= charadamage;
                                if(monster.number[monster.which].HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    HP[monster.which] = 0;
                                    chara.killedmon++;
                                    chara.money += 2000 + rand() % 500;
                                    chara.position = WIN;
                                }
                                else
                                {
                                    monster_update();
                                    battle.confirm = false;
                                }
                                monster_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 3)
                    {
                        if(chara.MP >= 200)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                battle.use = 0;
                                chara.MP -= 200;
                                charadamage = chara.attack * (chara.speed / monster.number[monster.which].speed) * 2;
                                monster.number[monster.which].HP -= charadamage;
                                if(monster.number[monster.which].HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    HP[monster.which] = 0;
                                    chara.killedmon++;
                                    chara.money += 2000 + rand() % 500;
                                    chara.position = WIN;
                                }
                                else
                                {
                                    monster_update();
                                    battle.confirm = false;
                                }
                                monster_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 4)
                    {
                        if(chara.MP >= 500)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                battle.use = 0;
                                chara.MP -= 500;
                                charadamage = chara.attack * (chara.speed / monster.number[monster.which].speed) + rand() %1000;
                                monster.number[monster.which].HP -= charadamage;
                                if(monster.number[monster.which].HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    HP[monster.which] = 0;
                                    chara.killedmon++;
                                    chara.money += 2000 + rand() % 500;
                                    chara.position = WIN;
                                }
                                else
                                {
                                    monster_update();
                                    battle.confirm = false;
                                }
                                monster_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                }//kick monster end
                else if(battle.position == 2)
                {
                    if(battle.use == 1)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                if(chara.HP <= 900)
                                {
                                    chara.HP += 100;
                                }
                                else
                                {
                                    chara.HP = 1000;
                                }
                                battle.use = 0;
                                monster_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 2)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                if(chara.MP <= 700)
                                {
                                    chara.MP += 300;
                                }
                                else
                                {
                                    chara.MP = 1000;
                                }
                                battle.use = 0;
                                monster_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 3)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                if(chara.atkuse == 0)
                                {
                                    chara.attack += 100;
                                }
                                chara.atkuse += 5;
                                battle.use = 0;
                                monster_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 4)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                if(chara.defuse == 0)
                                {
                                    chara.def += 20;
                                }
                                chara.defuse += 5;
                                battle.use = 0;
                                monster_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 5)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                if(chara.HP <= 910)
                                {
                                    chara.HP += 90;
                                }
                                else
                                {
                                    chara.HP = 1000;
                                }
                                if(chara.MP<= 730)
                                {
                                    chara.MP += 270;
                                }
                                else
                                {
                                    chara.MP = 1000;
                                }
                                battle.use = 0;
                                monster_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 6)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                charadamage = rand() % 1000;
                                monster.number[monster.which].HP -= charadamage;
                                battle.use = 0;
                                if(monster.number[monster.which].HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    HP[monster.which] = 0;
                                    chara.killedmon++;
                                    chara.money += 2000 + rand() % 500;
                                    chara.position = WIN;
                                }
                                else
                                {
                                    monster_update();
                                    battle.confirm = false;
                                }
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                }//use item end
            }//really want to use skill/item end
        }//battle menu 2 ned
    }//battle end
    else if(chara.position == BOSSROOM)
    {
        if(battle.menu == 1)
        {
            if(key_state[ALLEGRO_KEY_F1])
            {
                battle.menu = 2;
                battle.position = 1;
            }
            else if(key_state[ALLEGRO_KEY_F2])
            {
                battle.menu = 2;
                battle.position = 2;
            }
        }
        else if(battle.menu == 2)
        {
            if(battle.confirm == false)
            {
                if(key_state[ALLEGRO_KEY_W])
                {
                    battle.menu = 1;
                }
                else if(battle.position == 1)
                {
                    if(key_state[ALLEGRO_KEY_1])
                    {
                        battle.use = 1;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_2])
                    {
                        battle.use = 2;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_3])
                    {
                        battle.use = 3;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_4])
                    {
                        battle.use = 4;
                        battle.confirm = true;
                    }
                }
                else if(battle.position == 2)
                {
                    if(key_state[ALLEGRO_KEY_1])
                    {
                        battle.use = 1;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_2])
                    {
                        battle.use = 2;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_3])
                    {
                        battle.use = 3;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_4])
                    {
                        battle.use = 4;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_5])
                    {
                        battle.use = 5;
                        battle.confirm = true;
                    }
                    else if(key_state[ALLEGRO_KEY_6])
                    {
                        battle.use = 6;
                        battle.confirm = true;
                    }
                }
            }
            else if(battle.confirm == true)
            {
                if(battle.position == 1)
                {
                    if(battle.use == 1)
                    {
                        if(chara.MP >= 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                battle.use = 0;
                                charadamage = chara.attack * (chara.speed / BOSS.speed) + rand() %50;
                                BOSS.HP -= charadamage;
                                if(BOSS.HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    chara.position = WIN;
                                }
                                else
                                {
                                    boss_update();
                                    battle.confirm = false;
                                }
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                    }
                    else if(battle.use == 2)
                    {
                        if(chara.MP >= 100)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                battle.use = 0;
                                chara.MP -= 100;
                                charadamage = chara.attack * (chara.speed / BOSS.speed) + 50 + rand() %100;
                                BOSS.HP -= charadamage;
                                if(BOSS.HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    chara.position = WIN;
                                }
                                else
                                {
                                    boss_update();
                                    battle.confirm = false;
                                }
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 3)
                    {
                        if(chara.MP >= 200)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                battle.use = 0;
                                chara.MP -= 200;
                                charadamage = chara.attack * (chara.speed / BOSS.speed) + rand() %500;
                                BOSS.HP -= charadamage;
                                if(BOSS.HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    chara.position = WIN;
                                }
                                else
                                {
                                    boss_update();
                                    battle.confirm = false;
                                }
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 4)
                    {
                        if(chara.MP >= 500)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                battle.use = 0;
                                chara.MP -= 500;
                                charadamage = chara.attack * (chara.speed / BOSS.speed) + rand() %1000;
                                BOSS.HP -= charadamage;
                                if(BOSS.HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    chara.position = COMPLETE;
                                }
                                else
                                {
                                    boss_update();
                                    battle.confirm = false;
                                }
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                }//kick monster end
                else if(battle.position == 2)
                {
                    if(battle.use == 1)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                charadamage = 0;
                                if(chara.HP <= 900)
                                {
                                    chara.HP += 100;
                                }
                                else
                                {
                                    chara.HP = 1000;
                                }
                                battle.use = 0;
                                boss_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 2)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                charadamage = 0;
                                if(chara.MP <= 700)
                                {
                                    chara.MP += 300;
                                }
                                else
                                {
                                    chara.MP = 1000;
                                }
                                battle.use = 0;
                                boss_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 3)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                charadamage = 0;
                                if(chara.atkuse == 0)
                                {
                                    chara.attack += 100;
                                }
                                chara.atkuse += 5;
                                battle.use = 0;
                                boss_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 4)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                charadamage = 0;
                                if(chara.defuse == 0)
                                {
                                    chara.def += 20;
                                }
                                chara.defuse += 5;
                                battle.use = 0;
                                boss_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 5)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                charadamage = 0;
                                if(chara.HP <= 910)
                                {
                                    chara.HP += 90;
                                }
                                else
                                {
                                    chara.HP = 1000;
                                }
                                if(chara.MP<= 730)
                                {
                                    chara.MP += 270;
                                }
                                else
                                {
                                    chara.MP = 1000;
                                }
                                battle.use = 0;
                                boss_update();
                                battle.confirm = false;
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                    else if(battle.use == 6)
                    {
                        if(chara.backpack[battle.use - 1] > 0)
                        {
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 1;
                                chara.backpack[battle.use - 1]--;
                                charadamage = rand()%3000;
                                BOSS.HP -= charadamage;
                                battle.use = 0;
                                if(BOSS.HP <= 0)
                                {
                                    chara.HP = 1000;
                                    chara.MP = 1000;
                                    chara.position = COMPLETE;
                                }
                                else
                                {
                                    boss_update();
                                    battle.confirm = false;
                                }
                            }
                            else if(key_state[ALLEGRO_KEY_ESCAPE])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                            }
                        }
                        else
                        {
                            battle.mana = false;
                            if(key_state[ALLEGRO_KEY_ENTER])
                            {
                                battle.menu = 2;
                                battle.use = 0;
                                battle.confirm = false;
                                battle.mana = true;
                            }
                        }
                    }
                }//use item end
            }//really want to use skill/item end
        }//boss menu 2 ned
    }//boss end
    else if(chara.position == WIN)
    {
        if(key_state[ALLEGRO_KEY_ESCAPE])
        {
            chara.position = MAP;
        }
    }
    else if(chara.position == LOSE)
    {
        if(key_state[ALLEGRO_KEY_ESCAPE])
        {
            nowstate =0;
            flag=0;
            window = 1;
        }
    }
    else if(chara.position == COMPLETE)
    {
        if(key_state[ALLEGRO_KEY_ESCAPE])
        {
            window = 1;
        }
    }
}
void character_draw(){
    // with the state, draw corresponding image



    if(nowstate == 1)
    {
        al_draw_bitmap(background1, 0, 0, 0);
    }
    if(flag == 1)
    {
       al_draw_bitmap(background2, chara.x-1980,chara.y-1150, 0);
    }

    //al_draw_textf(fgame, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "%d, %d", chara.x, chara.y);

    if( chara.state == STOP ){
        if( chara.dir )
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
    }else if( chara.state == MOVE ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/3 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else if( chara.anime < chara.anime_time*2/3 ){
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[2], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara.anime < chara.anime_time/3 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else if( chara.anime < chara.anime_time*2/3 ){
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[2], chara.x, chara.y, 0);
            }
        }
    }else if( chara.state == ATK ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, 0);
                al_play_sample_instance(chara.atk_Sound);
            }
        }
    }
}
void character_destory(){
    al_destroy_bitmap(chara.img_atk[0]);
    al_destroy_bitmap(chara.img_atk[1]);
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_sample_instance(chara.atk_Sound);
}

void shop_init(){
    char temp[50];
    sprintf( temp, "./image/shop.jpg");
    shop.img_close[0] = al_load_bitmap(temp);
    for(int i = 1 ; i <= 3 ; i++)
    {
        char temp[50];
        sprintf( temp, "./image/menu1_%d.png", i );
        shop.img_menu1[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 3 ; i++)
    {
        char temp[50];
        sprintf( temp, "./image/menu2_%d.png", i );
        shop.img_menu2[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    //sample = al_load_sample("./sound/atk_sound.wav");  //don't know if we need.
    //chara.atk_Sound  = al_create_sample_instance(sample);  change to other voice
    //al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    //al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    shop.position = 1;
    shop.menu = 1;
    shop.x = 100;
    shop.y = 100;
    shop.buy = 0;
    shop.dir = false;
    shop.state = false;
    shop.confirm = false;
    shop.rich = true;
    fgame = al_load_ttf_font("./font/pirulen.ttf",50,0);
}
void shop_draw(){
    if(nowstate == 0)
    {
        if(shop.state == true)
        {
            if(shop.menu == 1)
            {
                if(shop.position == 1)
                {
                    //al_clear_to_color(al_map_rgb(100, 100, 100));
                    al_draw_bitmap(shop.img_menu1[0], shop.x / 2, shop.y / 2, 0);
                    al_draw_textf(fgame, al_map_rgb(0, 0, 0), 350, 950, ALLEGRO_ALIGN_CENTER, "%d", chara.money);
                    al_flip_display();
                }
                else if(shop.position == 2)
                {
                    //al_clear_to_color(al_map_rgb(100, 100, 100));
                    al_draw_bitmap(shop.img_menu1[1], shop.x / 2, shop.y / 2, 0);
                    al_draw_textf(fgame, al_map_rgb(0, 0, 0), 350, 950, ALLEGRO_ALIGN_CENTER, "%d", chara.money);
                    al_flip_display();
                }
                else if(shop.position == 3)
                {
                    //al_clear_to_color(al_map_rgb(100, 100, 100));
                    al_draw_bitmap(shop.img_menu1[2], shop.x / 2, shop.y / 2, 0);
                    al_draw_textf(fgame, al_map_rgb(0, 0, 0), 350, 950, ALLEGRO_ALIGN_CENTER, "%d", chara.money);
                    al_flip_display();
                }

                if(shop.confirm)
                {
                    al_draw_text(fgame, al_map_rgb(255, 0, 0), 900, 800, ALLEGRO_ALIGN_CENTER, "Do you want to change weapon?(ENTER/ESC)");
                    al_flip_display();
                }
            }
            else if(shop.menu == 2)
            {
                if(shop.position == 1)
                {
                    //al_clear_to_color(al_map_rgb(100, 100, 100));
                    al_draw_bitmap(shop.img_menu2[0], shop.x / 2, shop.y / 2, 0);
                    al_draw_textf(fgame, al_map_rgb(0, 0, 0), 350, 950, ALLEGRO_ALIGN_CENTER, "%d", chara.money);
                    al_flip_display();
                    if(shop.confirm)
                    {
                        if(shop.rich)
                        {
                            al_draw_text(fgame, al_map_rgb(255, 0, 0), 800, 800, ALLEGRO_ALIGN_CENTER, "Are you sure?(ENTER/ESC)");
                        }
                        else
                        {
                            al_draw_text(fgame, al_map_rgb(255, 0, 0), 800, 800, ALLEGRO_ALIGN_CENTER, "You don't have enough gold(ENTER)");
                        }

                        if(shop.buy == 1)
                        {
                            al_draw_rectangle(105, 335, 469, 405, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 2)
                        {
                            al_draw_rectangle(105, 408, 469, 478, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 3)
                        {
                            al_draw_rectangle(105, 480, 469, 550, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 4)
                        {
                            al_draw_rectangle(105, 551, 469, 621, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 5)
                        {
                            al_draw_rectangle(105, 623, 469, 693, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 6)
                        {
                            al_draw_rectangle(105, 694, 469, 763, al_map_rgb(255, 0, 0), 0);
                        }
                    }
                }
                else if(shop.position == 2)
                {
                    //al_clear_to_color(al_map_rgb(100, 100, 100));
                    al_draw_bitmap(shop.img_menu2[1], shop.x / 2, shop.y / 2, 0);
                    al_draw_textf(fgame, al_map_rgb(0, 0, 0), 350, 950, ALLEGRO_ALIGN_CENTER, "%d", chara.money);
                    al_flip_display();
                    if(shop.confirm)
                    {
                        if(shop.rich)
                        {
                            al_draw_text(fgame, al_map_rgb(255, 0, 0), 800, 800, ALLEGRO_ALIGN_CENTER, "Are you sure?(ENTER/ESC)");
                        }
                        else
                        {
                            al_draw_text(fgame, al_map_rgb(255, 0, 0), 800, 800, ALLEGRO_ALIGN_CENTER, "You don't have enough gold(ENTER)");
                        }
                        if(shop.buy == 1)
                        {
                            al_draw_rectangle(570, 335, 1185, 405, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 2)
                        {
                            al_draw_rectangle(570, 408, 1185, 478, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 3)
                        {
                            al_draw_rectangle(570, 480, 1185, 550, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 4)
                        {
                            al_draw_rectangle(570, 551, 1185, 621, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 5)
                        {
                            al_draw_rectangle(570, 623, 1185, 693, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 6)
                        {
                            al_draw_rectangle(570, 695, 1185, 765, al_map_rgb(255, 0, 0), 0);
                        }
                    }
                }
                else if(shop.position == 3)
                {
                    //al_clear_to_color(al_map_rgb(100, 100, 100));
                    al_draw_bitmap(shop.img_menu2[2], shop.x / 2, shop.y / 2, 0);
                    al_draw_textf(fgame, al_map_rgb(0, 0, 0), 350, 950, ALLEGRO_ALIGN_CENTER, "%d", chara.money);
                    al_flip_display();
                    if(shop.confirm)
                    {
                        if(shop.rich)
                        {
                            al_draw_text(fgame, al_map_rgb(255, 0, 0), 800, 800, ALLEGRO_ALIGN_CENTER, "Are you sure?(ENTER/ESC)");
                        }
                        else
                        {
                            al_draw_text(fgame, al_map_rgb(255, 0, 0), 800, 800, ALLEGRO_ALIGN_CENTER, "You don't have enough gold(ENTER)");
                        }
                        if(shop.buy == 1)
                        {
                            al_draw_rectangle(1320, 335, 1740, 405, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 2)
                        {
                            al_draw_rectangle(1320, 408, 1740, 478, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 3)
                        {
                            al_draw_rectangle(1320, 480, 1740, 550, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 4)
                        {
                            al_draw_rectangle(1320, 551, 17405, 621, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 5)
                        {
                            al_draw_rectangle(1320, 623, 1740, 693, al_map_rgb(255, 0, 0), 0);
                        }
                        else if(shop.buy == 6)
                        {
                            al_draw_rectangle(1320, 695, 1740, 765, al_map_rgb(255, 0, 0), 0);
                        }
                    }
                }
            }
        }
    }

}
void shop_destory(){
    al_destroy_bitmap(shop.img_close[0]);
    al_destroy_bitmap(shop.img_menu1[0]);
    al_destroy_bitmap(shop.img_menu1[1]);
    al_destroy_bitmap(shop.img_menu1[2]);
    al_destroy_bitmap(shop.img_menu2[0]);
    al_destroy_bitmap(shop.img_menu2[1]);
    al_destroy_bitmap(shop.img_menu2[2]);
    al_destroy_font(fgame);
}

void backpack_intit(){
    char temp[50];
    sprintf( temp, "./image/backpack.png");
    backpack_open = al_load_bitmap(temp);
    fbackpack = al_load_ttf_font("./font/pirulen.ttf", 40, 0);
}
void backpack_draw(){
    if(chara.position == BACKPACK)
    {
        al_draw_bitmap(backpack_open, 650, 150, 0);
        if(chara.weapon == 0)
        {
            al_draw_text(fbackpack, al_map_rgb(0, 0, 0), 823, 266, ALLEGRO_ALIGN_LEFT, "STICK");
        }
        else if(chara.weapon == 1)
        {
            al_draw_text(fbackpack, al_map_rgb(0, 0, 0), 823, 266, ALLEGRO_ALIGN_LEFT, "SWORD");
        }
        else if(chara.weapon == 2)
        {
            al_draw_text(fbackpack, al_map_rgb(0, 0, 0), 823, 266, ALLEGRO_ALIGN_LEFT, "SHIELD");
        }
        else if(chara.weapon == 3)
        {
            al_draw_text(fbackpack, al_map_rgb(0, 0, 0), 823, 266, ALLEGRO_ALIGN_LEFT, "SPEAR");
        }
        else if(chara.weapon == 4)
        {
            al_draw_text(fbackpack, al_map_rgb(0, 0, 0), 823, 266, ALLEGRO_ALIGN_LEFT, "GREAT SWORD");
        }
        else if(chara.weapon == 5)
        {
            al_draw_text(fbackpack, al_map_rgb(0, 0, 0), 823, 266, ALLEGRO_ALIGN_LEFT, "WAND");
        }
        else if(chara.weapon == 6)
        {
            al_draw_text(fbackpack, al_map_rgb(0, 0, 0), 823, 266, ALLEGRO_ALIGN_LEFT, "BATTLE AXE");
        }
        for(int i = 0; i < 6; i++)
        {
            al_draw_textf(fgame, al_map_rgb(0, 0, 0), 1200, 350 + 55 * i, ALLEGRO_ALIGN_CENTER, "%d", chara.backpack[i]);
        }
        al_draw_textf(fgame, al_map_rgb(0, 0, 0), 775, 873, ALLEGRO_ALIGN_LEFT, "%d", chara.money);
    }
}
void backpack_destroy(){
    al_destroy_bitmap(backpack_open);
    al_destroy_font(fbackpack);
}

void form_intit(){
    char temp1[50];
    sprintf( temp1, "./image/form1.png");
    form_open = al_load_bitmap(temp1);
    fform = al_load_ttf_font("./font/pirulen.ttf", 30, 0);
}
void form_draw(){
    if(chara.position == FORM)
    {
        al_draw_bitmap(form_open, 650, 150, 0);
        al_draw_textf(fform, al_map_rgb(0, 0, 0), 1200, 290, ALLEGRO_ALIGN_RIGHT, "%d / %d", chara.HP,1000);
        al_draw_textf(fform, al_map_rgb(0, 0, 0), 1200, 290 + 60 * 1, ALLEGRO_ALIGN_RIGHT, "%d / %d", chara.MP,1000);
        al_draw_textf(fform, al_map_rgb(0, 0, 0), 1200, 290 + 60 * 2, ALLEGRO_ALIGN_RIGHT, "%d", chara.attack);
        al_draw_textf(fform, al_map_rgb(0, 0, 0), 1200, 290 + 60 * 3, ALLEGRO_ALIGN_RIGHT, "%d", chara.def);
        al_draw_textf(fform, al_map_rgb(0, 0, 0), 1200, 290 + 60 * 4, ALLEGRO_ALIGN_RIGHT, "%d", chara.speed);
        al_draw_textf(fform, al_map_rgb(0, 0, 0), 1200, 290 + 60 * 5, ALLEGRO_ALIGN_RIGHT, "%d", chara.killedmon);
    }
}
void form_destroy(){
    al_destroy_bitmap(form_open);
}

void battle_init(){
    HP[0] = 1, HP[1] = 1;
    battle.menu = 1;
    battle.position = 1;
    battle.use = 0;
    battle.confirm = false;
    battle.mana = true;

    char temp[50];
    sprintf(temp, "./image/battle_origin.png");
    battle.origin = al_load_bitmap(temp);

    sprintf( temp, "./image/battle_fight.png");
    battle.fight = al_load_bitmap(temp);


    sprintf(temp, "./image/battle_item.png");
    battle.item = al_load_bitmap(temp);


    sprintf(temp, "./image/boss_origin.png");
    battle.bossorigin = al_load_bitmap(temp);

    sprintf( temp, "./image/boss_fight.png");
    battle.bossfight = al_load_bitmap(temp);


    sprintf(temp, "./image/boss_item.png");
    battle.bossitem = al_load_bitmap(temp);

    for(int i = 0 ; i <= 6 ; i++)
    {
        for(int j = 0; j <= 1; j++)
        {
            sprintf( temp, "./image/weapon%d_%d.png", i, j + 1);
            battle.weapon[i][j] = al_load_bitmap(temp);
        }
    }

    for(int i = 0; i <= 1; i++)
    {
        sprintf( temp, "./image/monster%d.png", i);
        battle.monster[i] = al_load_bitmap(temp);
    }

    sprintf(temp, "./image/boss.png");
    battle.bossimage = al_load_bitmap(temp);

    sprintf(temp, "./image/win.png");
    battle.win = al_load_bitmap(temp);

    sprintf(temp, "./image/lose.png");
    battle.lose = al_load_bitmap(temp);

    sprintf(temp, "./image/complete.png");
    battle.complete = al_load_bitmap(temp);

    fbattle = al_load_ttf_font("./font/pirulen.ttf", 20, 0);
    ftext = al_load_ttf_font("./font/pirulen.ttf", 25, 0);
}
void battle_draw(){
    if(chara.position == BATTLE)
    {
        if(battle.menu == 1)
        {
            al_draw_bitmap(battle.origin, 0, 0, 0);
            if(firsttime == 1)
            {
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "You deal %d damage.", charadamage);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 550, 640, ALLEGRO_ALIGN_LEFT, "Boss kicked you for %d.", enemydamage);
            }
        }
        else if(battle.menu == 2)
        {
            if(battle.position == 1)
            {
                al_draw_bitmap(battle.fight, 0, 0, 0);
                if(battle.confirm)
                {
                    if(battle.mana)
                    {
                        al_draw_text(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "Are you sure?(ENTER/ESC)");
                    }
                    else
                    {
                        al_draw_text(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "You don't have enough MP(ENTER)");
                    }

                    if(battle.use == 1)
                    {
                        al_draw_rectangle(15, 720, 245, 820, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 2)
                    {
                        al_draw_rectangle(255, 720, 500, 820, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 3)
                    {
                        al_draw_rectangle(15, 835, 245, 935, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 4)
                    {
                        al_draw_rectangle(255, 835, 500, 935, al_map_rgb(255, 0, 0), 0);
                    }
                }
            }
            else if(battle.position == 2)
            {
                al_draw_bitmap(battle.item, 0, 0, 0);
                if(battle.confirm)
                {
                    if(battle.mana)
                    {
                        al_draw_text(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "Are you sure?(ENTER/ESC)");
                    }
                    else
                    {
                        al_draw_text(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "You don't have enough item(ENTER)");
                    }

                    if(battle.use == 1)
                    {
                        al_draw_rectangle(15, 720, 245, 820, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 2)
                    {
                        al_draw_rectangle(255, 720, 500, 820, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 3)
                    {
                        al_draw_rectangle(15, 835, 245, 935, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 4)
                    {
                        al_draw_rectangle(255, 835, 500, 935, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 5)
                    {
                        al_draw_rectangle(15, 940, 245, 1040, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 6)
                    {
                        al_draw_rectangle(255, 940, 500, 1040, al_map_rgb(255, 0, 0), 0);
                    }
                }
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 238, 733, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[0]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 490, 733, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[1]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 238, 847, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[2]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 490, 847, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[3]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 230, 963, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[4]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 490, 963, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[5]);
            }
        }

        al_draw_bitmap(battle.weapon[chara.weapon][0], 10, 300, 0);
        al_draw_bitmap(battle.monster[monster.which], 1200, 50, 0);

        al_draw_textf(fbackpack, al_map_rgb(255, 255, 255), 900, 970, ALLEGRO_ALIGN_RIGHT, "%d/1000", chara.HP);
        al_draw_textf(fbackpack, al_map_rgb(255, 255, 255), 1350, 970, ALLEGRO_ALIGN_RIGHT, "%d/1000", chara.MP);
        al_draw_textf(fbattle, al_map_rgb(255, 0, 0), 50, 10, ALLEGRO_ALIGN_LEFT, "ATK BUFF: %d", chara.atkuse);
        al_draw_textf(fbattle, al_map_rgb(255, 0, 0), 50, 40, ALLEGRO_ALIGN_LEFT, "DEF BUFF: %d", chara.defuse);
        al_draw_textf(fbackpack, al_map_rgb(255, 0, 0), 1500, 70, ALLEGRO_ALIGN_LEFT, "%d", monster.number[monster.which].HP);
    }
    else if(chara.position == BOSSROOM)
    {
        if(battle.menu == 1)
        {
            al_draw_bitmap(battle.bossorigin, 0, 0, 0);
        }
        else if(battle.menu == 2)
        {
            if(battle.position == 1)
            {
                al_draw_bitmap(battle.bossfight, 0, 0, 0);
                if(battle.confirm)
                {
                    if(battle.mana)
                    {
                        al_draw_text(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "Are you sure?(ENTER/ESC)");
                    }
                    else
                    {
                        al_draw_text(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "You don't have enough MP(ENTER)");
                    }

                    if(battle.use == 1)
                    {
                        al_draw_rectangle(15, 720, 245, 820, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 2)
                    {
                        al_draw_rectangle(255, 720, 500, 820, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 3)
                    {
                        al_draw_rectangle(15, 835, 245, 935, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 4)
                    {
                        al_draw_rectangle(255, 835, 500, 935, al_map_rgb(255, 0, 0), 0);
                    }
                }
            }
            else if(battle.position == 2)
            {
                al_draw_bitmap(battle.bossitem, 0, 0, 0);
                if(battle.confirm)
                {
                    if(battle.mana)
                    {
                        al_draw_text(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "Are you sure?(ENTER/ESC)");
                    }
                    else
                    {
                        al_draw_text(ftext, al_map_rgb(0, 0, 0), 550, 595, ALLEGRO_ALIGN_LEFT, "You don't have enough item(ENTER)");
                    }

                    if(battle.use == 1)
                    {
                        al_draw_rectangle(15, 720, 245, 820, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 2)
                    {
                        al_draw_rectangle(255, 720, 500, 820, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 3)
                    {
                        al_draw_rectangle(15, 835, 245, 935, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 4)
                    {
                        al_draw_rectangle(255, 835, 500, 935, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 5)
                    {
                        al_draw_rectangle(15, 940, 245, 1040, al_map_rgb(255, 0, 0), 0);
                    }
                    else if(battle.use == 6)
                    {
                        al_draw_rectangle(255, 940, 500, 1040, al_map_rgb(255, 0, 0), 0);
                    }
                }
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 238, 733, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[0]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 490, 733, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[1]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 238, 847, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[2]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 490, 847, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[3]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 230, 963, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[4]);
                al_draw_textf(ftext, al_map_rgb(0, 0, 0), 490, 963, ALLEGRO_ALIGN_RIGHT, "%d", chara.backpack[5]);
            }
        }

        al_draw_bitmap(battle.weapon[chara.weapon][0], 10, 300, 0);
        al_draw_bitmap(battle.bossimage, 1200, 50, 0);

        al_draw_textf(fbackpack, al_map_rgb(255, 255, 255), 900, 970, ALLEGRO_ALIGN_RIGHT, "%d/1000", chara.HP);
        al_draw_textf(fbackpack, al_map_rgb(255, 255, 255), 1350, 970, ALLEGRO_ALIGN_RIGHT, "%d/1000", chara.MP);
        al_draw_textf(fbattle, al_map_rgb(255, 0, 0), 50, 10, ALLEGRO_ALIGN_LEFT, "ATK BUFF: %d", chara.atkuse);
        al_draw_textf(fbattle, al_map_rgb(255, 0, 0), 50, 40, ALLEGRO_ALIGN_LEFT, "DEF BUFF: %d", chara.defuse);
        al_draw_textf(fbackpack, al_map_rgb(255, 0, 0), 1500, 70, ALLEGRO_ALIGN_LEFT, "%d", BOSS.HP);
    }
    else if(chara.position == WIN)
    {
        al_draw_bitmap(battle.win, 0, 0, 0);
    }
    else if(chara.position == LOSE)
    {
        al_draw_bitmap(battle.lose, 0, 0, 0);
    }
    else if(chara.position == COMPLETE)
    {
        al_draw_bitmap(battle.complete, 0, 0, 0);
    }
}
void battle_destroy(){
    al_destroy_bitmap(battle.origin);
    al_destroy_bitmap(battle.item);
    al_destroy_bitmap(battle.win);
    al_destroy_bitmap(battle.lose);
    al_destroy_bitmap(battle.fight);
    for(int i = 0; i <= 6; i++)
    {
        for(int j = 0; j <= 1; j++)
        {
            al_destroy_bitmap(battle.weapon[i][j]);
        }
    }
    al_destroy_font(fbackpack);
    al_destroy_font(fbattle);
    al_destroy_font(ftext);
}

void monster_init(){
    monster.which = 1;

    monster.number[0].HP = 100;
    monster.number[0].attack = 50;
    monster.number[0].def = 30;
    monster.number[0].speed = 5;

    monster.number[1].HP = 200;
    monster.number[1].attack = 60;
    monster.number[1].def = 0;
    monster.number[1].speed = 10;

    BOSS.HP = 100;
    BOSS.attack = 70;
    BOSS.def = 30;
    BOSS.speed = 10;
}
void monster_update(){
    int x = rand() % 10;
    firsttime = 1;

    if(x >= 0 && x <= 3)
    {
        enemydamage = monster.number[monster.which].attack + rand() % 50;
        chara.HP -= enemydamage;
    }
    else if(x >= 4 && x <= 6)
    {
        enemydamage = monster.number[monster.which].attack + 50 + rand() % 100;
        chara.HP -= enemydamage;
    }
    else if(x >= 6 && x <= 8)
    {
        enemydamage = monster.number[monster.which].attack + rand() % 500;
        chara.HP -= enemydamage;
    }
    else if(x == 9)
    {
        enemydamage = monster.number[monster.which].attack * 2 + rand() % 50;
        chara.HP -= enemydamage;
    }

    if(chara.atkuse != 0)
    {
        chara.atkuse--;
        if(chara.atkuse == 0)
        {
            chara.attack -= 100;
        }
    }//ATKBUFF
    if(chara.defuse != 0)
    {
        chara.defuse--;
        if(chara.defuse == 0)
        {
            chara.def -= 20;
        }
    }//DEFBUFF

    if(chara.HP <= 0)
    {
        chara.position = LOSE;
    }
    else
    {
        if(chara.HP <= 950)
        {
            chara.HP += 50;
        }
        else
        {
            chara.HP = 1000;
        }
        if(chara.MP<= 950)
        {
            chara.MP += 50;
        }
        else
        {
            chara.MP = 1000;
        }
    }
    battle.confirm = false;
}

void boss_update(){
    int x = rand() % 14;
    firsttime = 1;

    if(x >= 0 && x <= 3)
    {
        enemydamage = BOSS.attack + rand() % 50;
        chara.HP -= enemydamage;
    }
    else if(x >= 4 && x <= 6)
    {
        enemydamage = BOSS.attack + 50 + rand() % 100;
        chara.HP -= enemydamage;
    }
    else if(x >= 6 && x <= 8)
    {
        enemydamage = BOSS.attack + rand() % 500;
        chara.HP -= enemydamage;
    }
    else if(x == 9)
    {
        enemydamage = BOSS.attack * 2 + rand() % 50;
        chara.HP -= enemydamage;
    }
    else if(x >= 10 && x <= 11)
    {
        enemydamage = 300;

        if(chara.MP>300)
        chara.MP -= 300;
        else
        chara.MP = 0;

    }
    else if(x >= 12 && x <= 13)
    {
        chara.MP = 0;
    }

    if(chara.HP <= 0)
    {
        chara.position = LOSE;
        battle.confirm = false;
    }
    else
    {
        if(chara.HP <= 950)
        {
            chara.HP += 50;
        }
        else
        {
            chara.HP = 1000;
        }
        if(chara.MP<= 950)
        {
            chara.MP += 50;
        }
        else
        {
            chara.MP = 1000;
        }
    }

    if(chara.atkuse != 0)
    {
        chara.atkuse--;
        if(chara.atkuse == 0)
        {
            chara.attack -= 100;
        }
    }//ATKBUFF
    if(chara.defuse != 0)
    {
        chara.defuse--;
        if(chara.defuse == 0)
        {
            chara.def -= 20;
        }
    }//DEFBUFF
    battle.confirm = false;
}

int check(int x,int y){
    if(420 < x && x < 890 && 160 < y && y < 330)
    {
        return 1;
    }
    else if(1580 < x && x < 1800 && 350 < y && y < 520)
    {
        return 2;
    }
    else if(1780 <= x && x <= 1801 && -1 <= y && y <= 80)
    {
        return 3;
    }
}
int checkmon(int xx,int yy){
    if(rtime == 0 )
    {
        if(700 < xx )//&& xx < 1000)
            return 1;
        else if(100 < xx )//&& xx < 500)
            return 2;
        else
            return 0;
    }
    else if(rtime == 1 )
    {
        if(1200 < xx )//&& xx < 1000)
            return 1;
        else if(700 < xx )//&& xx < 1800)
            return 2;
        else
            return 0;
    }
    else if(rtime == 2 )
    {
        if(1200 < xx )//&& xx < 1800)
            return 1;
        else if(100 < xx )//&& xx < 500)
            return 2;
        else
            return 0;
    }
    else if(rtime == 3 )
    {
         if(1200 < xx )//&& xx < 500)
            return 1;
        else if(100 < xx )//&& xx < 1800)
            return 2;
        else
            return 0;
    }
    else
        return 0;
}
int checkwall(int nowx,int nowy){
    if(nowx>0&&nowy>0)
    {
        if(wall[nowx][nowy+5]==1)
            return 0;
        else
            return 1;
    }
    else
    {

        if(wall[nowx+2000][nowy+5]==1)
            return 0;
        else
            return 1;

    }
}
