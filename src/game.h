#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include "constants.h"
#include "snake.h"

void play_singlePlayer(ALLEGRO_EVENT_QUEUE *eventQueue);
void play_multiPlayer(ALLEGRO_EVENT_QUEUE *eventQueue);

#endif