#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "base64.h"

#include "protocol.h"

int protocol_encode(struct protocol_frame *p_frame, char *out_encoded_buffer, size_t encoded_buffer_size) {
  if (p_frame == NULL) {
    return PROTOCOL_ERROR_NO_FRAME;
  }

  if (out_encoded_buffer== NULL) {
    return PROTOCOL_ERROR_NO_OUT;
  }

  if (p_frame->data == NULL) {
    return PROTOCOL_ERROR_NO_DATA;
  }

  uint8_t raw_data[512] = { 0 };
  size_t raw_data_size = 10 + p_frame->data_size;
  memcpy(raw_data, p_frame, 10);
  memcpy(&raw_data[10], p_frame->data, p_frame->data_size);

  int encoded_frame_len = 0;
  char *encoded_frame = base64(raw_data, raw_data_size, &encoded_frame_len);
  memset(out_encoded_buffer, 0, encoded_buffer_size);
  if (encoded_buffer_size <= encoded_frame_len) {
    free(encoded_frame);
    return PROTOCOL_ERROR_OUT_TOO_SMALL;
  }
  memcpy(out_encoded_buffer, encoded_frame, encoded_frame_len);
  free(encoded_frame);

  return PROTOCOL_OK;
}

int protocol_decode(void) {
  return PROTOCOL_OK;
}
