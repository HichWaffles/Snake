#include "game.h"

void parse_input(char input, char* direction, char* lost) {
  switch (input) {
    case 'q':
    case 'Q':
      *lost = 1;
      break;

    case 'w':
    case 'W':
    case 72:
      if (*direction != 1)
        *direction = 3;
      break;

    case 'a':
    case 'A':
    case 75:
      if (*direction != 0)
        *direction = 2;
      break;

    case 's':
    case 'S':
    case 80:
      if (*direction != 3)
        *direction = 1;
      break;

    case 'd':
    case 'D':
    case 77:
      if (*direction != 2)
        *direction = 0;
      break;
  }
}

void spawn_food(char** matrix,
                Vector* board_map,
                int* board_map_index,
                int snake_length) {
  int board_map_size = WIDTH * HEIGHT - snake_length;
  if (board_map_size <= 0) {
    return;
  }

  int random_index = rand() % board_map_size;

  Vector food_pos = board_map[random_index];
  update_index(matrix, food_pos, FOOD_CHAR);
}