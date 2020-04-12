#include "game.h"

void play_singlePlayer(ALLEGRO_EVENT_QUEUE *eventQueue)
{
    ALLEGRO_DISPLAY *display = al_get_current_display();
    ALLEGRO_TIMER *timer_snakeMove;
    ALLEGRO_TIMER *timer_draw;
    
    int finish = 0;

    snake_t snake;
    food_t food;

    bool canMove = true;

    snake_create(&snake);
    food_setPosition(&food);

    timer_snakeMove = al_create_timer(0.1);
    al_register_event_source(eventQueue, al_get_timer_event_source(timer_snakeMove));

    timer_draw = al_create_timer(1.0 / 60.0);
    al_register_event_source(eventQueue, al_get_timer_event_source(timer_draw));


    al_start_timer(timer_snakeMove);
    al_start_timer(timer_draw);
    while(!finish)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event_timed(eventQueue, &event, 1/60.0);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(0);

        if(snake.dead)
            finish = 1;

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(canMove)
            {
                switch(event.keyboard.keycode)
                {
                case ALLEGRO_KEY_UP:
                    if(snake.direction != DOWN)
                        snake.direction = UP;
                    break;

                case ALLEGRO_KEY_DOWN:
                    if(snake.direction != UP)
                        snake.direction = DOWN;
                    break;

                case ALLEGRO_KEY_LEFT:
                    if(snake.direction != RIGHT)
                        snake.direction = LEFT;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    if(snake.direction != LEFT)
                        snake.direction = RIGHT;
                    break;
                }

                canMove = false;
            }

            if(event.keyboard.keycode == ALLEGRO_KEY_S)
                al_save_bitmap("screen2.jpg", al_get_backbuffer(display));
        }


        // Timer events
        // Sanke move and drawing

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            //Snake move
            if(event.timer.source == timer_snakeMove)
            {
                snake_move(&snake);
                canMove = true;

                if(snake_onFood(snake, food))
                {
                    food_setPosition(&food);
                    snake_grow(&snake);
                    printf("Plop\n");
                }

                snake_dies(&snake);

                if(snake.dead)
                    printf("dead\n");

                event.type = 0;
            }


            // Drawing
            if(event.timer.source == timer_draw)
            {

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

                snake_draw(snake);
                food_draw(food);


                al_flip_display();

                event.type = 0;
            }
        }
    }

    snake_delete(&snake);
}