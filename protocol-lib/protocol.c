#include <stdint.h>
#include <stdio.h>

#include "base64.h"

#include "protocol.h"

int protocol_encode(struct protocol_frame *p_frame) {
  if (p_frame == NULL) {
    return PROTOCOL_ERROR_NO_FRAME;
  }

  if (p_frame->data == NULL) {
    return PROTOCOL_ERROR_NO_DATA;
  }

  uint8_t raw_data[512] = { 0 };

  return PROTOCOL_OK;
}

int protocol_decode(void) {
  return PROTOCOL_OK;
}
