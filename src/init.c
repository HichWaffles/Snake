#include "init.h"

void initialize_board(char** matrix, Vector* board_map, int* board_map_index) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      matrix[i][j] = EMPTY_CHAR;
      int index = i * WIDTH + j;
      board_map[index].y = i;
      board_map[index].x = j;
      board_map_index[index] = index;
    }
  }
}

void initialize_snake(char** matrix,
                      Vector* snake,
                      int* first_snake_index,
                      int* last_snake_index,
                      int* board_map_index,
                      Vector* board_map) {
  *first_snake_index = *last_snake_index = 0;

  snake[WIDTH * HEIGHT - 1] =
      create_vector(WIDTH / 2 - INIT_SNAKE_SIZE / 2, HEIGHT / 2);

  for (int i = 0; i < INIT_SNAKE_SIZE; i++) {
    Vector new_head =
        project_head(snake, *first_snake_index, *last_snake_index, 0);

    if (!i)
      push_head(snake, *first_snake_index, last_snake_index, new_head,
                board_map_index, board_map, matrix);
    else
      push_head_and_update(snake, *first_snake_index, last_snake_index,
                           new_head, board_map_index, board_map, matrix);
  }
}