#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
int main()
{
    int width, height, channels;
    char input_path[100], output_path[100];

    printf("Enter the path of the input RGB image: ");
    scanf("%99s", input_path);
    printf("Enter the path for the output grayscale image: ");
    scanf("%99s", output_path);

    unsigned char *img = stbi_load(input_path, &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("Error in loading the image\n");
        exit(1);
    }

    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
    int gray_channels = 1;
    size_t img_size = width * height * gray_channels;
    unsigned char *gray_img = malloc(img_size);

    if (gray_img == NULL)
    {
        printf("Unable to allocate memory for the grayscale image.\n");
        exit(1);
    }

    for (unsigned char *p = img, *pg = gray_img; p != img + width * height * channels; p += channels, pg += gray_channels)
    {
        *pg = (uint8_t)((*p * 0.299) + (*(p + 1) * 0.587) + (*(p + 2) * 0.114));
    }

    stbi_write_png(output_path, width, height, gray_channels, gray_img, width * gray_channels);
    
    printf("Grayscale image saved to %s\n", output_path);
    stbi_image_free(img);
    free(gray_img);
    return 0;
}