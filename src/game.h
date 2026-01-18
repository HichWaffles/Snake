#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "snake.h"
#include "vector.h"
#include "render.h"

void parse_input(char input, char* direction, char* lost);
void spawn_food(char** matrix,
                Vector* board_map,
                int* board_map_index,
                int snake_length);

#endif