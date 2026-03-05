#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include "config.h"
#include "score.h"
#include "vector.h"

void initial_render(char** matrix);
void update_index(char** matrix, Vector pos, char value);
void clscreen(void);
void update_score_display(void);

#endif