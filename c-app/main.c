#include <stdint.h>
#include <string.h>
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

  printf("Encoded frame is: '%s'\n", encoded_frame);


  uint8_t frame2_data[10];
  struct protocol_frame frame2 = { .data = frame2_data, .data_size = 10 };
  protocol_decode(&frame2, encoded_frame, strnlen(encoded_frame, 512));

  printf("decoded_frame {\n");
  printf("    .id: %d\n", frame2.id);
  printf("    .ts: %ld\n", frame2.ts);
  printf("    .data_size: %d\n", frame2.data_size);
  printf("    .data[0]: %d\n", frame2.data[0]);
  printf("    .data[1]: %d\n", frame2.data[1]);
  printf("    .data[2]: %d\n", frame2.data[2]);
  printf("    .data[3]: %d\n", frame2.data[3]);
  printf("    .data[4]: %d\n", frame2.data[4]);
  printf("    .data[5]: %d\n", frame2.data[5]);
  printf("    .data[6]: %d\n", frame2.data[6]);
  printf("    .data[7]: %d\n", frame2.data[7]);
  printf("    .data[8]: %d\n", frame2.data[8]);
  printf("    .data[9]: %d\n", frame2.data[9]);
  printf("}\n");

  return 0;
}
