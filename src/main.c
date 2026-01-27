#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "game.h"
#include "init.h"
#include "input.h"
#include "render.h"
#include "score.h"
#include "snake.h"
#include "vector.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
  // These allocations can be optimized later 🤡
  char** matrix = (char**)malloc(HEIGHT * sizeof(char*));
  for (int i = 0; i < HEIGHT; i++) {
    matrix[i] = (char*)malloc(WIDTH * sizeof(char));
  }
  Vector* snake = (Vector*)malloc(WIDTH * HEIGHT * sizeof(Vector));
  Vector* board_map = (Vector*)malloc(WIDTH * HEIGHT * sizeof(Vector));
  int* board_map_index = (int*)malloc(WIDTH * HEIGHT * sizeof(int));

  int should_exit = 0;

  srand(time(NULL));

  while (!should_exit) {
    char lost = 0, direction = 0, won = 0;
    int first_snake_index = 0, last_snake_index = 0;
    initialize_board(matrix, board_map, board_map_index);
    initialize_snake(matrix, snake, &first_snake_index, &last_snake_index,
                     board_map_index, board_map);
    reset_score();
    initial_render(matrix);
    spawn_food(matrix, board_map, board_map_index,
               get_length(first_snake_index, last_snake_index));

    enable_raw_mode();
    hide_cursor();

    while (!lost && !won) {
      clock_t start_time = clock();

      poll_input();

      int key;
      while ((key = get_user_input()) != -1) {
        parse_input(key, &direction, &lost);
      }

      Vector original_head = get_head(snake, last_snake_index);
      Vector new_head =
          project_head(snake, first_snake_index, last_snake_index, direction);

      // Index exceeding bounds can only happen if WRAP_AROUND is disabled
      if (new_head.x < 0 || new_head.x >= WIDTH || new_head.y < 0 ||
          new_head.y >= HEIGHT) {
        lost = 1;
        break;
      }

      CellType removed = get_cell_type(matrix[new_head.y][new_head.x]);

      // This is not efficient or necessary but I really hate the way the snake
      // look when it bites itself.
      if (removed == CELL_BOUNDARY) {
        lost = 1;
        break;
      }

      push_head_and_update(snake, first_snake_index, &last_snake_index,
                           new_head, board_map_index, board_map, matrix);

      switch (removed) {
        case CELL_FOOD:
          update_score(1);
          update_score_display();
          won =
              get_length(first_snake_index, last_snake_index) == HEIGHT * WIDTH;
          if (!won)
            spawn_food(matrix, board_map, board_map_index,
                       get_length(first_snake_index, last_snake_index));
          break;
        case CELL_EMPTY:
          pop_tail(snake, &first_snake_index, last_snake_index, board_map_index,
                   board_map, matrix);
          break;
        default:
          lost = 1;
          break;
      }

      clock_t end_time = clock();
      double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

      double sleep_time = MAX((double)SLEEP_TIME_MS / 1000.0 - elapsed_time, 0);

      struct timespec ts;
      ts.tv_sec = (time_t)sleep_time;
      ts.tv_nsec = (sleep_time - ts.tv_sec) * 1e9;
      nanosleep(&ts, NULL);
    }
    show_cursor();
    disable_raw_mode();

    int new_highscore = check_and_update_highscore();

    clscreen();
    printf(won ? "You won! Now go touch grass..." : "Game Over!");
    printf(" Your score: %d\n", get_score());
    if (new_highscore)
      printf("New Highscore!\n");

    printf("Press 'r' to restart or 'q' to quit.\n");

    int choice = -1;
    while (choice != 'r' && choice != 'q') {
      poll_input();
      choice = get_user_input();
    }
    should_exit = (choice == 'q');
  }

  for (int i = 0; i < HEIGHT; i++) {
    free(matrix[i]);
  }
  free(matrix);
  free(snake);
  free(board_map);
  free(board_map_index);

  return 0;
}