#include "ControllerTesting.h"
#include <libdragon.h>

void PrintControllerStats()
{
    controller_scan();
    struct controller_data keys = get_keys_pressed();
    printf("A is %spressed\n", (keys.c[0].A) ? "": "not ");
    printf("B is %spressed\n", (keys.c[0].B) ? "": "not ");
    printf("Z is %spressed\n", (keys.c[0].Z) ? "": "not ");
    printf("L is %spressed\n", (keys.c[0].L) ? "": "not ");
    printf("R is %spressed\n", (keys.c[0].R) ? "": "not ");
    printf("C up is %spressed\n", (keys.c[0].C_up) ? "": "not ");
    printf("C down is %spressed\n", (keys.c[0].C_down) ? "": "not ");
    printf("C left is %spressed\n", (keys.c[0].C_left) ? "": "not ");
    printf("C right is %spressed\n", (keys.c[0].C_right) ? "": "not ");
    printf("start is %spressed\n", (keys.c[0].start) ? "": "not ");
    printf("up is %spressed\n", (keys.c[0].up) ? "": "not ");
    printf("down is %spressed\n", (keys.c[0].down) ? "": "not ");
    printf("left is %spressed\n", (keys.c[0].left) ? "": "not ");
    printf("right is %spressed\n", (keys.c[0].right) ? "": "not ");
    printf("left analog %d\n", keys.c[0].x);
    printf("right analog %d\n", keys.c[0].y);
}
