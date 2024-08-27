#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FRAMES 3600
#define SIZE 28
#define CHANNELS 3
void print_video_data(int ****video) {
    for (int frame = 0; frame < FRAMES; frame++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int pixel_number = i * SIZE + j + 1;
                int red = video[frame][0][i][j];
                int green = video[frame][1][i][j];
                int blue = video[frame][2][i][j];
                printf("Frame %d | Pixel %d | RGB Value (%d,%d,%d)\n", 
                       frame + 1, pixel_number, red, green, blue);
            }
        }
    }
}
int main() {
    int ****video;
    video = (int ****)malloc(FRAMES * sizeof(int ***));
    if (video == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int frame = 0; frame < FRAMES; frame++) {
        video[frame] = (int ***)malloc(CHANNELS * sizeof(int **));
        if (video[frame] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        for (int channel = 0; channel < CHANNELS; channel++) {
            video[frame][channel] = (int **)malloc(SIZE * sizeof(int *));
            if (video[frame][channel] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            for (int i = 0; i < SIZE; i++) {
                video[frame][channel][i] = (int *)malloc(SIZE * sizeof(int));
                if (video[frame][channel][i] == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    return 1;
                }
            }
        }
    }
    srand(time(NULL));
    for (int frame = 0; frame < FRAMES; frame++) {
        for (int channel = 0; channel < CHANNELS; channel++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    video[frame][channel][i][j] = rand() % 256;
                }
            }
        }
    }
    print_video_data(video);
    for (int frame = 0; frame < FRAMES; frame++) {
        for (int channel = 0; channel < CHANNELS; channel++) {
            for (int i = 0; i < SIZE; i++) {
                free(video[frame][channel][i]);
            }
            free(video[frame][channel]);
        }
        free(video[frame]);
    }
    free(video);
    return 0;
}