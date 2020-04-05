#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include "list.h"

#define SCREEN_W 1000
#define SCREEN_H 700

void erreur(const char *txt)
{
    ALLEGRO_DISPLAY *d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "Error message", "ERREUR", txt, NULL, 0);
    exit(1);
}

void allegroInit(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **eventQueue);


int main()
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT event;
    int finish = 0;

    if(!al_init())
        erreur("al_init()");

    allegroInit(&display, &eventQueue);


    while(!finish)
    {
        al_wait_for_event_timed(eventQueue, &event, 1/60.0);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            finish = 1;


        // Drawing
        al_clear_to_color(al_map_rgb(15, 15, 15));

        for(int i = 0; i < SCREEN_W / 20; i++)
        {
            for(int j = 0; j < SCREEN_H / 20; j++)
            {
                al_draw_line(i*20, j*20, i*20 + 20, j*20, al_map_rgb(0, 100, 0), 2);
                al_draw_line(i*20, j*20, i*20, j*20 + 20, al_map_rgb(0, 100, 0), 2);
                al_draw_line(i*20 + 20, j*20, i*20 + 20, j*20 + 20, al_map_rgb(0, 100, 0), 2);
                al_draw_line(i*20, j*20 + 20, i*20 + 20, j*20 + 20, al_map_rgb(0, 100, 0), 2);
            }
        }

        al_flip_display();
    }


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

    
    if(!al_init_primitives_addon())
        erreur("al_init_primities_addon()");
    

    al_register_event_source(*eventQueue, al_get_display_event_source(*display));
}
