#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "base64.h"

#include "protocol.h"

int protocol_encode(struct protocol_frame *p_frame, char *out_encoded_buffer,
                    size_t encoded_buffer_size) {
        if (p_frame == NULL) {
                return PROTOCOL_ERROR_NO_FRAME;
        }

        if (out_encoded_buffer == NULL) {
                return PROTOCOL_ERROR_NO_OUT;
        }

        if (p_frame->data == NULL) {
                return PROTOCOL_ERROR_NO_DATA;
        }

        uint8_t raw_data[512] = {0};
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

int protocol_decode(
        void (*decoded_callback)(struct protocol_frame *out_p_frame),
        const char *encoded_frame, size_t encoded_frame_len) {
        if (decoded_callback == NULL) {
                return PROTOCOL_ERROR_NO_FRAME;
        }

        if (encoded_frame == NULL) {
                return PROTOCOL_ERROR_NO_OUT;
        }

        int raw_decoded_len = 0;
        uint8_t *raw_decoded =
                unbase64(encoded_frame, encoded_frame_len, &raw_decoded_len);

        if (raw_decoded_len < 10) {
                free(raw_decoded);
                return PROTOCOL_ERROR_INVALID_ENCODED_FRAME;
        }

        // TODO: Make this in a clean and safe way
        struct protocol_frame decoded_frame = {
                .ts = ((struct protocol_frame *)raw_decoded)->ts,
                .id = ((struct protocol_frame *)raw_decoded)->id,
                .data_size = ((struct protocol_frame *)raw_decoded)->data_size,
                .data = &raw_decoded[10],
        };

        decoded_callback(&decoded_frame);
        free(raw_decoded);

        return PROTOCOL_OK;
}
