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

    snake_create(&snake, 0);
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
                    snake_grow(&snake, 0);
                    printf("Plop\n");
                }

                if(snake_dies(snake)) snake.dead = true;

                if(snake.dead)
                    printf("dead\n");

                event.type = 0;
            }


            // Drawing
            if(event.timer.source == timer_draw)
            {

                al_clear_to_color(al_map_rgb(15, 15, 15));

                snake_draw(snake);
                food_draw(food);


                al_flip_display();

                event.type = 0;
            }
        }
    }

    snake_delete(&snake);

    al_destroy_timer(timer_draw);
    al_destroy_timer(timer_snakeMove);
}




void play_multiPlayer(ALLEGRO_EVENT_QUEUE *eventQueue)
{
    ALLEGRO_DISPLAY *display = al_get_current_display();
    ALLEGRO_TIMER *timer_snakeMove;
    ALLEGRO_TIMER *timer_draw;
    
    int finish = 0;

    snake_t snake1;
    snake_t snake2;
    food_t food;

    bool canMove1 = true;
    bool canMove2 = true;

    snake_create(&snake1, 0);
    snake_create(&snake2, 1);
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

        if(snake1.dead && snake2.dead)
            finish = 1;

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            // Snake 1
            if(canMove1)
            {
                switch(event.keyboard.keycode)
                {

                case ALLEGRO_KEY_Z:
                    if(snake1.direction != DOWN)
                        snake1.direction = UP;
                    break;

                case ALLEGRO_KEY_S:
                    if(snake1.direction != UP)
                        snake1.direction = DOWN;
                    break;

                case ALLEGRO_KEY_Q:
                    if(snake1.direction != RIGHT)
                        snake1.direction = LEFT;
                    break;

                case ALLEGRO_KEY_D:
                    if(snake1.direction != LEFT)
                        snake1.direction = RIGHT;
                    break;
                }

                canMove1 = false;
            }

            // Snake 2
            if(canMove2)
            {
                switch(event.keyboard.keycode)
                {
                case ALLEGRO_KEY_UP:
                    if(snake2.direction != DOWN)
                        snake2.direction = UP;
                    break;

                case ALLEGRO_KEY_DOWN:
                    if(snake2.direction != UP)
                        snake2.direction = DOWN;
                    break;

                case ALLEGRO_KEY_LEFT:
                    if(snake2.direction != RIGHT)
                        snake2.direction = LEFT;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    if(snake2.direction != LEFT)
                        snake2.direction = RIGHT;
                    break;
                }

                canMove2 = false;
            }

            if(event.keyboard.keycode == ALLEGRO_KEY_P)
                al_save_bitmap("screen2.jpg", al_get_backbuffer(display));
        }


        // Timer events
        // Sanke move and drawing

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            //Snake move
            if(event.timer.source == timer_snakeMove)
            {
                snake_move(&snake1);
                snake_move(&snake2);
                canMove1 = true;
                canMove2 = true;

                if(snake_onFood(snake1, food))
                {
                    food_setPosition(&food);
                    snake_grow(&snake1, 0);
                    printf("Plop 1\n");
                }

                if(snake_onFood(snake2, food))
                {
                    food_setPosition(&food);
                    snake_grow(&snake2, 1);
                    printf("Plop 2\n");
                }

                if(snake_dies(snake1)) snake1.dead = true;
                if(snake_dies(snake2)) snake2.dead = true;

                if(snake_onOtherSnake(snake1, snake2))
                    snake1.dead = true;
                if(snake_onOtherSnake(snake2, snake1))
                    snake2.dead = true;

                if(snake1.dead)
                    printf("dead 1\n");
                if(snake2.dead)
                    printf("dead 2\n");

                event.type = 0;
            }


            // Drawing
            if(event.timer.source == timer_draw)
            {

                al_clear_to_color(al_map_rgb(15, 15, 15));

                snake_draw(snake1);
                snake_draw(snake2);
                food_draw(food);


                al_flip_display();

                event.type = 0;
            }
        }
    }

    snake_delete(&snake1);
    snake_delete(&snake2);

    al_destroy_timer(timer_draw);
    al_destroy_timer(timer_snakeMove);

}