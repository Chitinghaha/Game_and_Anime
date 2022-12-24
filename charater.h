#include "global.h"

void buildwall();

void character_init();
void charater_process(ALLEGRO_EVENT event);
void charater_update();
void character_draw();
void character_destory();

void shop_init();
void shop_draw();
void shop_destory();

void backpack_intit();
void backpack_draw();
void backpack_destroy();

void form_intit();
void form_draw();
void form_destroy();

void battle_init();
void battle_draw();
void battle_destroy();

void monster_init();
void monster_update();

void boss_update();

int check(int x,int y);
int checkmon(int xx,int yy);
int checkwall(int nowx,int nowy);
