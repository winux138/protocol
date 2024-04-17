#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "protocol-lib/protocol.h"

void decoded_callback(struct protocol_frame *p_protocol_frame);
void animal_handler(struct animal *p_animal);
void car_handler(struct car *p_car);

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

/* Internal functions */

void decoded_callback(struct protocol_frame *p_protocol_frame) {
        if (p_protocol_frame == NULL) {
                printf("%s(): Got a NULL ptr\n", __func__);
                return;
        }

        switch (p_protocol_frame->id) {
                case PROTOCOL_ANIMAL:
                        animal_handler((struct animal *)p_protocol_frame->data);
                        break;
                case PROTOCOL_CAR:
                        car_handler((struct car *)p_protocol_frame->data);
                        break;
                default:
                        printf("%s(): Unknown frame id: %u\n", __func__, p_protocol_frame->id);
                        break;
        }
}

void animal_handler(struct animal *p_animal) {
        printf("It is an PROTOCOL_ANIMAL!\n");
        printf("struct animal {\n");
        printf("        name: %s\n",p_animal->name);
        printf("        age: %d\n", p_animal->age);
        printf("        legs: %d\n", p_animal->legs);
        printf("};\n");
}

