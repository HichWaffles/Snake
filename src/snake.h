#ifndef SNAKE_H
#define SNAKE_H

#include "config.h"
#include "render.h"
#include "vector.h"

Vector push_head(Vector* snake,
                 int first_snake_index,
                 int* last_snake_index,
                 Vector new_head,
                 int* board_map_index,
                 Vector* board_map,
                 char** matrix);

void push_head_and_update(Vector* snake,
                          int first_snake_index,
                          int* last_snake_index,
                          Vector new_head,
                          int* board_map_index,
                          Vector* board_map,
                          char** matrix);

Vector pop_tail(Vector* snake,
                int* first_snake_index,
                int last_snake_index,
                int* board_map_index,
                Vector* board_map,
                char** matrix);

Vector project_head(Vector* snake,
                    int first_snake_index,
                    int last_snake_index,
                    char direction);

Vector get_head(Vector* snake, int first_snake_index);
#endif
