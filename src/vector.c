#include "vector.h"

#if WRAP_AROUND == 1
#define APPLY_BOUNDARY(n, max) (((n) % (max) + (max)) % (max))
#else
#define APPLY_BOUNDARY(n, max) (n)
#endif

Vector add_vector(Vector a, Vector b) {
  return (Vector){APPLY_BOUNDARY(a.x + b.x, WIDTH),
                  APPLY_BOUNDARY(a.y + b.y, HEIGHT)};
}

Vector create_vector(int x, int y) {
  Vector v;
  v.x = x;
  v.y = y;
  return v;
}

// direction: 0 = right, 1 = down, 2 = left, 3 = up (clockwise)
Vector vector_from_direction(char direction) {
  Vector v;
  switch (direction) {
    case 0:
      v.x = 1;
      v.y = 0;
      break;
    case 1:
      v.x = 0;
      v.y = 1;
      break;
    case 2:
      v.x = -1;
      v.y = 0;
      break;
    case 3:
      v.x = 0;
      v.y = -1;
      break;
    default:
      // This should never happen but just in case. Panic!
      printf("What did you do?! D:\n");
      exit(1);
      break;
  }
  return v;
}