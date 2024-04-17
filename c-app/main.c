#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "protocol-lib/protocol.h"

void decoded_callback(struct protocol_frame *p_protocol_frame);
void animal_handler(struct animal *p_animal);
void car_handler(struct car *p_car);

int main(void) {
        struct animal animal = {
                .name = "Bob",
                .age = 1,
                .legs = 2,
        };
        struct protocol_frame animal_frame = {
                .id = 1,
                .ts = 1337,
                .data_size = sizeof(animal),
                .data = (uint8_t *)&animal
        };

        struct car car = {
                .brand = "Brand A",
                .model = "Model B",
                .horsepower = 100,
                .max_speed = 200,
        };
        struct protocol_frame car_frame = {
                .id = 2,
                .ts = 1338,
                .data_size = sizeof(car),
                .data = (uint8_t *)&car
        };

        char encoded_frame[512];

        protocol_encode(&animal_frame, encoded_frame, 512);
        printf("Encoded frame is: '%s'\n", encoded_frame);
        protocol_decode(decoded_callback, encoded_frame, strnlen(encoded_frame, 512));

        memset(encoded_frame, 0, 512);

        protocol_encode(&car_frame, encoded_frame, 512);
        printf("Encoded frame is: '%s'\n", encoded_frame);
        protocol_decode(decoded_callback, encoded_frame, strnlen(encoded_frame, 512));

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

void car_handler(struct car *p_car) {
        printf("It is an PROTOCOL_CAR!\n");
        printf("struct car {\n");
        printf("        brand: %s\n",p_car->brand);
        printf("        model: %s\n",p_car->model);
        printf("        horsepower: %d\n", p_car->horsepower);
        printf("        max_speed: %d\n", p_car->max_speed);
        printf("};\n");
}

