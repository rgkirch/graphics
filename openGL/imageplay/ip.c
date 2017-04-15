#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv) {
    char name[256];
    if(argc > 1) {
        strncpy(name, argv[1], 255);
        printf("%s\n", name);
    }
	stbi_set_flip_vertically_on_load(1);
    int width, height, comp;
    width = height = 0;
    comp = 3;
    unsigned char* image = stbi_load("./images/container.jpg", &width, &height, &comp, 3);
    stbi_image_free(image);
    return 0;
}
