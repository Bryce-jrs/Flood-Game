#include "random_generator.h"

void init_rand() {
  srand(time(NULL));
}

int generate_rand(int upperBound) {
  return rand()%upperBound;
}
