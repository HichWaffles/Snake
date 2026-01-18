#include "render.h"

void move_cursor(int row, int col) {
  printf("\033[%d;%dH", row, col);
}

void move_to_grid(int x, int y) {
  move_cursor(y + 2, (x * 2) + 3);
}

void initial_render(char** matrix) {
  clscreen();

  for (int i = 0; i < WIDTH + 2; i++)
    printf("%c ", BOUND_CHAR);
  printf("\n");

  for (int i = 0; i < HEIGHT; i++) {
    printf("%c", BOUND_CHAR);
    for (int j = 0; j < WIDTH; j++) {
      printf(" %c", matrix[i][j]);
    }
    printf(" %c\n", BOUND_CHAR);
  }

  for (int i = 0; i < WIDTH + 2; i++)
    printf("%c ", BOUND_CHAR);

  update_score_display();
}

void update_index(char** matrix, Vector pos, char value) {
  matrix[pos.y][pos.x] = value;
  move_to_grid(pos.x, pos.y);
  printf("%c", value);

  move_cursor(HEIGHT + 4, 1);
  fflush(stdout);
}

void clscreen() {
  printf("\033[2J");
  move_cursor(1, 1);
}

void update_score_display() {
  int score = get_score();
  int high = get_highscore();
  int current_high = (score > high) ? score : high;

  move_cursor(HEIGHT + 3, 1);
  printf("Score: %d; Highscore: %d\n", score, current_high);
}