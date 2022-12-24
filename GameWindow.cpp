#include "GameWindow.h"
bool draw = false;

const char *title = "An_Introduction_of_Game_and_Anime";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;

int Game_establish()
{
    int msg = 0;

    game_init();
    game_begin();

    while ( msg != GAME_TERMINATE )
    {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }

    game_destroy();
    return 0;
}

void game_init()
{
    printf( "Game Initializing...\n" );
    al_init();
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/icon.jpg");
    al_set_display_icon(display, icon);
}

void game_begin()
{

    // Load sound
    song = al_load_sample("./sound/hello.wav");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 1) ;
    al_play_sample_instance(sample_instance);
    al_start_timer(fps);
    // initialize the menu before entering the loop
    menu_init();

}

void game_update()
{
    if( judge_next_window )
    {
        if( window == 1 || window == 5 ||window == 6)
        {

            // not back menu anymore, therefore destroy it
            // initialize next scene
            game_scene_init();
            judge_next_window = false;
            if(key_state[ALLEGRO_KEY_1])//start
            {
                window = 2;
                key_state[ALLEGRO_KEY_1] = false;
            }
            else if(key_state[ALLEGRO_KEY_2])//Opt
            {
                window = 3;
                key_state[ALLEGRO_KEY_2] = false;
            }
            else if(key_state[ALLEGRO_KEY_3])//Info
            {
                window = 4;
                key_state[ALLEGRO_KEY_3] = false;
            }
            else if(key_state[ALLEGRO_KEY_4])//Exit
            {
                menu_destroy();
                key_state[ALLEGRO_KEY_4] = false;
            }
        }
    }


        if( window == 2 )
        {
            charater_update();
        }
        if(window == 3)
        {
            // not back option anymore, therefore destroy it
            // initialize next scene
            option_init();
            if(key_state[ALLEGRO_KEY_ESCAPE])//return to menu
            {
                window = 1;
                key_state[ALLEGRO_KEY_ESCAPE] = false;
            }
            else if(key_state[ALLEGRO_KEY_A])//Opt
            {
                window=1;
                key_state[ALLEGRO_KEY_A] = false;
            }
            else if(key_state[ALLEGRO_KEY_B])//Info
            {
                window=5;
               key_state[ALLEGRO_KEY_B] = false;
            }
            else if(key_state[ALLEGRO_KEY_C])//Info
            {
                window=6;
                key_state[ALLEGRO_KEY_C] = false;
            }
        }
        if(window == 4)
        {
            // not back menu anymore, therefore destroy it
            // initialize next scene
            Info_init();
            if(key_state[ALLEGRO_KEY_ESCAPE])//return to menu
            {
                window = 1;
                key_state[ALLEGRO_KEY_ESCAPE] = false;
            }
        }
}

int process_event()
{
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    // process the event of other component

    if( window == 1 ||   window == 5 ||window == 6)
    {
        menu_process(event);
    }
    else if( window == 2 )
    {
        charater_process(event);
    }
    else if( window ==3 )
    {
        option_process(event);
    }
    else if(window == 4)
    {
        Info_process(event);
    }


    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            draw = true;
    if(draw)
    {
        game_update();
    }
    return 0;
}




void game_draw()
{
    if( window == 1  )
    {
        menu_draw();
    }
    else if( window == 2 )
    {

        game_scene_draw();
    }
    else if( window == 3 )
    {
         option_draw();
    }
    else if(window == 4)
    {
        Info_draw();
    }
    else if(window == 5)
    {
        word1_draw();
    }
    else if(window == 6)
    {
        word2_draw();
    }

    al_flip_display();
}



int game_run()
{
    int error = 0;
    if( draw )
    {
        game_draw();
        draw = false;
    }

    if ( !al_is_event_queue_empty(event_queue) )
    {
        error = process_event();
    }
    return error;
}

void game_destroy()
{
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    game_scene_destroy();
}
