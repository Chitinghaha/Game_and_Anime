#include "scene.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_FONT *fInfo = NULL;
ALLEGRO_FONT *fop = NULL;
ALLEGRO_FONT *fword = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *menu_open = NULL;



// function of menu
void menu_init()
{
    //menu_scene_init();
    char temp2[50];
    sprintf( temp2, "./image/main.png");
    menu_open = al_load_bitmap(temp2);
    font = al_load_ttf_font("./font/pirulen.ttf",25,0);
}

void menu_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )

        if( event.keyboard.keycode == ALLEGRO_KEY_1 )
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_1] = true;
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_2)
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_2] = true;
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_3)
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_3] = true;
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_4)
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_4] = true;
        }

}
void menu_draw()
{
    al_draw_bitmap(menu_open, 0, 0, 0);
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-200, HEIGHT/2+150, ALLEGRO_ALIGN_LEFT, "1. Start");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-200, HEIGHT/2+180, ALLEGRO_ALIGN_LEFT, "2. Option");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-200, HEIGHT/2+210, ALLEGRO_ALIGN_LEFT, "3. Info");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-200, HEIGHT/2+240, ALLEGRO_ALIGN_LEFT, "4. Leave");
}
void word1_draw()
{
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_bitmap(menu_open,0, 0, 0);
    al_draw_text(font, al_map_rgb(255,400,255), WIDTH/2-200, HEIGHT/2+150, ALLEGRO_ALIGN_LEFT, "1. Start");
    al_draw_text(font, al_map_rgb(255,400,255), WIDTH/2-200, HEIGHT/2+180, ALLEGRO_ALIGN_LEFT, "2. Option");
    al_draw_text(font, al_map_rgb(255,400,255), WIDTH/2-200, HEIGHT/2+210, ALLEGRO_ALIGN_LEFT, "3. Info");
    al_draw_text(font, al_map_rgb(255,400,255), WIDTH/2-200, HEIGHT/2+240, ALLEGRO_ALIGN_LEFT, "4. Leave");
}
void word2_draw()
{
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_bitmap(menu_open, 0, 0, 0);
    al_draw_text(font, al_map_rgb(255, 0, 0 ), WIDTH/2-200, HEIGHT/2+150, ALLEGRO_ALIGN_LEFT, "1. Start");
    al_draw_text(font, al_map_rgb(255, 255, 0), WIDTH/2-200, HEIGHT/2+180, ALLEGRO_ALIGN_LEFT, "2. Option");
    al_draw_text(font, al_map_rgb(0, 127, 255), WIDTH/2-200, HEIGHT/2+210, ALLEGRO_ALIGN_LEFT, "3. Info");
    al_draw_text(font, al_map_rgb(139, 0, 255 ), WIDTH/2-200, HEIGHT/2+240, ALLEGRO_ALIGN_LEFT, "4. Leave");
}
void menu_destroy()
{
    al_destroy_font(font);
}




void option_init()
{
    fop = al_load_ttf_font("./font/pirulen.ttf",30,0);
}
void option_process(ALLEGRO_EVENT event)
{

    if( event.type == ALLEGRO_EVENT_KEY_UP )

        if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_ESCAPE] = true;
        }
        else if( event.keyboard.keycode == ALLEGRO_KEY_A)
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_A] = true;
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_B)
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_B] = true;
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_C)
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_C] = true;
        }

}
void option_draw()
{
    al_draw_bitmap(menu_open, 0, 0, 0);
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-200, HEIGHT/2+150, ALLEGRO_ALIGN_LEFT, "color of word ");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-200, HEIGHT/2+180, ALLEGRO_ALIGN_LEFT, "a.white");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-200, HEIGHT/2+210, ALLEGRO_ALIGN_LEFT, "b.pink");
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-200, HEIGHT/2+240, ALLEGRO_ALIGN_LEFT, "c.rainbow");
}
void option_destroy()
{
    al_destroy_font(fop);
}



void Info_init()
{
    fInfo = al_load_ttf_font("./font/pirulen.ttf",50,0);
}
void Info_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
        {
            judge_next_window = true;
            key_state[ALLEGRO_KEY_ESCAPE] = true;
        }
}
void Info_draw()
{
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_text(fInfo, al_map_rgb(334,600,255), WIDTH/2-50, 100, ALLEGRO_ALIGN_CENTER, "Created by Jim.");
}
void Info_destroy()
{
    al_destroy_font(fInfo);
}


// function of game_scene
void game_scene_init()
{
    buildwall();
    character_init();
    backpack_intit();
    form_intit();
    shop_init();
    battle_init();
    monster_init();
    background = al_load_bitmap("./image/village.png");
}
void game_scene_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    character_draw();
    backpack_draw();
    form_draw();
    shop_draw();
    battle_draw();
    al_flip_display();
}
void game_scene_destroy()
{
    al_destroy_bitmap(background);
    character_destory();
    backpack_destroy();
    form_destroy();
    battle_destroy();
    shop_destory();
}
