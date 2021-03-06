#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "list.h"
#include "constants.h"

typedef struct food_s
{
    int x;
    int y;
    int type;
} food_t;

typedef struct snakeTile_s
{
    int x;
    int y;
    ALLEGRO_COLOR color;
    struct snakeTile_s *next;
    struct snakeTile_s *previous;
} snakeTile_t;

typedef struct snake_s
{
    List snake;
    snakeTile_t *head;
    int direction;
    ALLEGRO_COLOR color;
    bool dead;
} snake_t;

void snake_create(snake_t *snake, int num);
void snake_delete(snake_t *snake);
void snake_move(snake_t *snake);
bool snake_onFood(snake_t s, food_t f);
bool snake_onOtherSnake(snake_t snake, snake_t other);
bool snake_dies(snake_t s);
void snake_grow(snake_t *snake, int num);
void snake_draw(const snake_t snake);
void snake_drawTile(void *data);

void food_setPosition(food_t *food);
void food_draw(food_t food);

#endif