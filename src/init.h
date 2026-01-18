#ifndef INIT_H
#define INIT_H

#include "config.h"
#include "snake.h"
#include "vector.h"

void initialize_board(char** matrix, Vector* board_map, int* board_map_index);
void initialize_snake(char** matrix,
                      Vector* snake,
                      int* first_snake_index,
                      int* last_snake_index,
                      int* board_map_index,
                      Vector* board_map);
#endif