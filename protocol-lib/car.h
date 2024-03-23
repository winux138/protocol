#pragma once

#include <stdint.h>

struct car {
  char brand[16];
  char model[16];
  uint16_t horsepower;
  uint16_t max_speed;
};
