#include "snake.h"

void remove_from_board_map(Vector pos,
                           int snake_length,
                           Vector* board_map,
                           int* board_map_index) {
  int spatial_idx = pos.y * WIDTH + pos.x;
  int map_idx_of_pos = board_map_index[spatial_idx];

  int last_empty_map_idx = (WIDTH * HEIGHT) - snake_length - 1;

  Vector last_v = board_map[last_empty_map_idx];

  board_map[map_idx_of_pos] = last_v;

  board_map_index[last_v.y * WIDTH + last_v.x] = map_idx_of_pos;
}

void add_to_board_map(Vector pos,
                      int snake_length,
                      Vector* board_map,
                      int* board_map_index) {
  int new_empty_map_idx = (WIDTH * HEIGHT) - snake_length - 1;

  board_map[new_empty_map_idx] = pos;
  board_map_index[pos.y * WIDTH + pos.x] = new_empty_map_idx;
}

int get_length(int first_snake_index, int last_snake_index) {
  return (last_snake_index - first_snake_index + WIDTH * HEIGHT) %
         (WIDTH * HEIGHT);
}

int increment_index(int index) {
  return (index + 1) % (WIDTH * HEIGHT);
}

int decrement_index(int index) {
  return (index - 1 + WIDTH * HEIGHT) % (WIDTH * HEIGHT);
}

Vector get_head(Vector* snake, int last_snake_index) {
  return snake[decrement_index(last_snake_index)];
}

Vector get_tail(Vector* snake, int first_snake_index) {
  return snake[first_snake_index];
}

Vector project_head(Vector* snake,
                    int first_snake_index,
                    int last_snake_index,
                    char direction) {
  return add_vector(get_head(snake, last_snake_index),
                    vector_from_direction(direction));
}

Vector push_head(Vector* snake,
                 int first_snake_index,
                 int* last_snake_index,
                 Vector new_head,
                 int* board_map_index,
                 Vector* board_map,
                 char** matrix) {
  int snake_length = get_length(first_snake_index, *last_snake_index);

  Vector original_head = get_head(snake, *last_snake_index);

  char original_value = matrix[new_head.y][new_head.x];

  update_index(matrix, new_head, HEAD_CHAR);

  remove_from_board_map(new_head, snake_length, board_map, board_map_index);

  snake[*last_snake_index] = new_head;
  *last_snake_index = increment_index(*last_snake_index);

  return original_head;
}

void push_head_and_update(Vector* snake,
                          int first_snake_index,
                          int* last_snake_index,
                          Vector new_head,
                          int* board_map_index,
                          Vector* board_map,
                          char** matrix) {
  Vector original_head =
      push_head(snake, first_snake_index, last_snake_index, new_head,
                board_map_index, board_map, matrix);
  update_index(matrix, original_head, BODY_CHAR);
}

Vector pop_tail(Vector* snake,
                int* first_snake_index,
                int last_snake_index,
                int* board_map_index,
                Vector* board_map,
                char** matrix) {
  Vector tail = get_tail(snake, *first_snake_index);
  *first_snake_index = increment_index(*first_snake_index);

  int snake_length = get_length(*first_snake_index, last_snake_index);
  add_to_board_map(tail, snake_length, board_map, board_map_index);
  update_index(matrix, tail, EMPTY_CHAR);
  return tail;
}