#include "snake.h"

// Private

bool snake_onItSelf(snake_t s);
bool snake_offScreen(snake_t s);


// Public

void snake_create(snake_t *snake)
{
    snakeTile_t *tile1;
    snakeTile_t *tile2;
    snakeTile_t *tile3;

    snake->head = malloc(sizeof(snakeTile_t));

    tile1 = malloc(sizeof(snakeTile_t));
    tile2 = malloc(sizeof(snakeTile_t));
    tile3 = malloc(sizeof(snakeTile_t));

    snake->head->next = NULL;
    snake->head->previous = tile1;
    snake->head->x = 27;
    snake->head->y = 15;

    tile1->next = snake->head;
    tile1->previous = tile2;
    tile1->x = 26;
    tile1->y = 15;

    tile2->next = tile1;
    tile2->previous = tile3;
    tile2->x = 25;
    tile2->y = 15;

    tile3->next = tile2;
    tile3->previous = NULL;
    tile3->x = 24;
    tile3->y = 15;

    snake->direction = RIGHT;
    snake->dead = false;
    snake->snake = list_create();

    list_pushBack(snake->snake, tile1);
    list_pushBack(snake->snake, tile2);
    list_pushBack(snake->snake, tile3);
}

void snake_delete(snake_t *snake)
{
    while(!list_empty(snake->snake))
    {
        snakeTile_t *t = list_back(snake->snake);
        list_popBack(snake->snake);
        free(t);
    }

    free(snake->head);

    list_delite(&(snake->snake));
}

void snake_move(snake_t *snake)
{
    snakeTile_t *tile;
    snakeTile_t *next = list_at(snake->snake, list_size(snake->snake) - 2);

    for(int i = list_size(snake->snake) - 1; i >= 0; i--)
    {
        tile = list_at(snake->snake, i);
        tile->x = next->x;
        tile->y = next->y;

        next = next->next;
    }

    switch(snake->direction)
    {
    case UP:
        (snake->head->y)--;
        break;
    case DOWN:
        (snake->head->y)++;
        break;
    case LEFT:
        (snake->head->x)--;
        break;
    case RIGHT:
        (snake->head->x)++;
        break;
    }
}

bool snake_onFood(snake_t s, food_t f)
{
    return s.head->x == f.x && s.head->y == f.y;
}

bool snake_onItSelf(snake_t s)
{
    for(snakeTile_t *t = s.head->previous; t != NULL; t = t->previous)
    {
        if(s.head->x == t->x && s.head->y == t->y)
            return true;
    }

    return false;
}

bool snake_offScreen(snake_t s)
{
    return (s.head->x < 0 || s.head->x >= SCREEN_W / TILE_W ||
            s.head->y < 0 || s.head->y >= SCREEN_H / TILE_H);
}

void snake_dies(snake_t *s)
{
    if(snake_onItSelf(*s) || snake_offScreen(*s))
        s->dead = true;
}

void snake_grow(snake_t *snake)
{
    snakeTile_t *new = malloc(sizeof(snakeTile_t));
    snakeTile_t *last = list_at(snake->snake, list_size(snake->snake) - 1);

    new->x = last->x;
    new->y = last->y;
    new->next = last;
    new->previous = NULL;

    last->previous = new;

    list_pushBack(snake->snake, new);
}

void snake_draw(const snake_t snake)
{
    al_draw_filled_rectangle(snake.head->x * TILE_W +  1, snake.head->y * TILE_H +  1,
                             snake.head->x * TILE_W + 19, snake.head->y * TILE_H + 19,
                             al_map_rgb(0, 200, 0));
    
    list_dump(snake.snake, snake_drawTile);
}

void snake_drawTile(void *data)
{
    snakeTile_t *tile = data;

    al_draw_filled_rectangle(tile->x * TILE_W +  1, tile->y * TILE_H +  1,
                             tile->x * TILE_W + 19, tile->y * TILE_H + 19,
                             al_map_rgb(0, 150, 0));
}

void food_setPosition(food_t *food)
{
    food->x = rand() % (SCREEN_W / TILE_W);
    food->y = rand() % (SCREEN_H / TILE_H);
}

void food_draw(food_t food)
{
    al_draw_filled_rectangle(food.x * TILE_W +  1, food.y * TILE_H +  1,
                             food.x * TILE_W + 19, food.y * TILE_H + 19,
                             al_map_rgb(200, 0, 0));
}
