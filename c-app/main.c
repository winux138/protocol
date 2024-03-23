#include <stdint.h>
#include <stdio.h>

#include "protocol-lib/protocol.h"

int main(void) {
  uint8_t frame_data[10] = {0, 1, 2 ,3 ,4 ,5 ,6 , 7 , 8, 9};
  struct protocol_frame frame = {
    .id = 1,
    .ts = 1337,
    .data_size = 10,
    .data = frame_data
  };

  char encoded_frame[512];
  protocol_encode(&frame, encoded_frame, 512);

  printf("Hello, World!\n");
  printf("Encoded frame is: '%s'\n", encoded_frame);
  return 0;
}
