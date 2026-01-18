#include "score.h"

int score = 0;
int highscore = -1;

int get_highscore() {
  if (highscore != -1)
    return highscore;

  FILE* file = fopen("highscore.txt", "r");
  if (file == NULL) {
    return 0;
  }
  int highscore;
  fscanf(file, "%d", &highscore);
  fclose(file);
  return highscore;
}

int set_highscore(int score) {
  highscore = score;
  FILE* file = fopen("highscore.txt", "w");
  if (file == NULL) {
    return -1;
  }
  fprintf(file, "%d", score);
  fclose(file);
  return 0;
}

int check_and_update_highscore() {
  int highscore = get_highscore();
  if (score > highscore) {
    set_highscore(score);
    return 1;
  }
  return 0;
}

void update_score(int points) {
  score += points;
}

int get_score() {
  return score;
}

void reset_score() {
  score = 0;
}