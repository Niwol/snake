#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "list.h"
#include "snake.h"
#include "game.h"
#include "constants.h"


void erreur(const char *txt)
{
    ALLEGRO_DISPLAY *d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "Error message", "ERREUR", txt, NULL, 0);
    exit(1);
}

void allegroInit(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **eventQueue);


int main()
{
    srand(time(NULL));

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_FONT *menuFont;
    
    int finish = 0;
    int selectedOption = 0;

    if(!al_init())
        erreur("al_init()");

    allegroInit(&display, &eventQueue);


    menuFont = al_load_font("Ubuntu-M.ttf", 80, 0);
    if(!menuFont)
        erreur("al_load_font(\"Ubuntu-M.ttf\", 80, 0)");

    while(!finish)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event_timed(eventQueue, &event, 1/60.0);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            finish = 1;

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN: selectedOption = (selectedOption + 1) % 3; break;
                case ALLEGRO_KEY_UP: selectedOption = selectedOption == 0 ? 2 : selectedOption - 1; break;

                case ALLEGRO_KEY_ENTER:
                    switch(selectedOption)
                    {
                        case 0: play_singlePlayer(eventQueue); break;
                        case 1: play_multiPlayer(eventQueue); break;
                        case 2: finish = 1; break;
                    }
                    event.keyboard.keycode = 0;
                    break;
            }
        }

        // Drawing
        al_clear_to_color(al_map_rgb(15, 15, 15));

        switch(selectedOption)
        {
            case 0: al_draw_filled_rectangle(260, 150, 765, 250, al_map_rgb(0, 50, 0)); break;
            case 1: al_draw_filled_rectangle(260, 270, 765, 370, al_map_rgb(0, 50, 0)); break;
            case 2: al_draw_filled_rectangle(260, 390, 765, 490, al_map_rgb(0, 50, 0)); break;
        }

        al_draw_text(menuFont, al_map_rgb(0, 150, 0), 270, 150, 0, "Single player");
        al_draw_text(menuFont, al_map_rgb(0, 150, 0), 280, 270, 0, "Multi player");
        al_draw_text(menuFont, al_map_rgb(0, 150, 0), 410, 390, 0, "Quit");

        al_flip_display();
    }


    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);

    return 0;
}


void allegroInit(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **eventQueue)
{
    if(!al_init())
        erreur("al_init()");

    *display = al_create_display(SCREEN_W, SCREEN_H);
    if(!*display)
        erreur("al_create_display(800, 600)");

    *eventQueue = al_create_event_queue();
    if(!*eventQueue)
        erreur("al_create_event_queue()");

    if(!al_install_keyboard())
        erreur("al_install_keyboard()");
    
    if(!al_init_primitives_addon())
        erreur("al_init_primities_addon()");

    if(!al_init_image_addon())
        erreur("al_init_image_addon()");

    al_init_font_addon();

    if(!al_init_ttf_addon())
        erreur("al_init_ttf_addon()");
    

    al_register_event_source(*eventQueue, al_get_display_event_source(*display));
    al_register_event_source(*eventQueue, al_get_keyboard_event_source());
}
