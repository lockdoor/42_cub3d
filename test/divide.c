#include <stdio.h>

int main(void)
{
    int map_x = 9;
    int map_y = 9;
    int screen_x = 645;
    int screen_y = 645;
    // double size_x = screen_x / map_x;
    // double size_y = screen_y / map_y;
    double size_x = (double) screen_x / (double) map_x;
    double size_y = (double) screen_y / (double) map_y;
    printf("size_x: %f\n", size_x);
    printf("size_y: %f\n", size_y);
    return (0);
}
