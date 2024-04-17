#pragma once

#include <stddef.h>
#include <stdint.h>

#include "animal.h"
#include "car.h"

enum PROTOCOL_RESULTS {
  PROTOCOL_OK = 0,
  PROTOCOL_NOK = 1,
  PROTOCOL_ERROR = -1,
  PROTOCOL_ERROR_NO_FRAME = -2,
  PROTOCOL_ERROR_NO_OUT = -3,
  PROTOCOL_ERROR_NO_DATA = -4,
  PROTOCOL_ERROR_OUT_TOO_SMALL = -5,
  PROTOCOL_ERROR_INVALID_ENCODED_FRAME = -6,
};

struct protocol_frame {
  int64_t ts;
  uint8_t id;
  uint8_t data_size;
  uint8_t *data;
} __attribute__((packed)); ;

int protocol_encode(struct protocol_frame *p_frame, char *out_encoded_buffer, size_t encoded_buffer_size);
int protocol_decode( void(* decoded_callback)(struct protocol_frame *out_p_frame), const char *encoded_frame, size_t encoded_frame_len);
