#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

typedef struct {
  int x;
  int y;
} Vector;

Vector add_vector(Vector a, Vector b);
Vector create_vector(int x, int y);
Vector vector_from_direction(char direction);

#endif
