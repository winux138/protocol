#pragma once

#include <stdint.h>

#define PROTOCOL_ANIMAL 1

struct animal {
  char name[16];
  uint8_t age;
  uint8_t legs;
};
