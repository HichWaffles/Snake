#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>

#define BODY_CHAR 'O'
#define HEAD_CHAR 'C'
#define FOOD_CHAR '*'
#define EMPTY_CHAR ' '
#define BOUND_CHAR 'X'

typedef enum { CELL_EMPTY, CELL_FOOD, CELL_BOUNDARY, CELL_UNKNOWN } CellType;

static CellType get_cell_type(char cell) {
  switch (cell) {
    case EMPTY_CHAR:
      return CELL_EMPTY;
    case FOOD_CHAR:
      return CELL_FOOD;
    case BODY_CHAR:
      return CELL_BOUNDARY;
    case HEAD_CHAR:
      return CELL_BOUNDARY;
    case BOUND_CHAR:
      return CELL_BOUNDARY;
    default:
      return CELL_UNKNOWN;
  }
}

int get_highscore();
int check_and_update_highscore();
void update_score(int points);
int get_score();
void reset_score();
int get_length(int first_snake_index, int last_snake_index);

#endif