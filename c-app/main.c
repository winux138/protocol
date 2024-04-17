#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "protocol-lib/protocol.h"

int main(void) {
        struct animal animal = {
                .name = "",
                .age = 1,
                .legs = 2,
        };
        struct protocol_frame frame = {.id = 1,
                .ts = 1337,
                .data_size = sizeof(animal),
                .data = (uint8_t *)&animal};

        char encoded_frame[512];
        protocol_encode(&frame, encoded_frame, 512);

        printf("Encoded frame is: '%s'\n", encoded_frame);

        struct animal frame2_data;
        struct protocol_frame frame2 = {.data = (uint8_t *)&frame2_data,
                .data_size = sizeof(frame2_data)};
        protocol_decode(&frame2, encoded_frame, strnlen(encoded_frame, 512));

        printf("decoded_frame {\n");
        printf("    .id: %d\n", frame2.id);
        printf("    .ts: %ld\n", frame2.ts);
        printf("    .data_size: %d\n", frame2.data_size);
        printf("    .data.name: %s\n", ((struct animal *)frame2.data)->name);
        printf("    .data.age: %d\n", ((struct animal *)frame2.data)->age);
        printf("    .data.legs: %d\n", ((struct animal *)frame2.data)->legs);
        printf("}\n");

        return 0;
}
