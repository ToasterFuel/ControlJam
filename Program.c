#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <libdragon.h>
#include "ControllerTesting.h"

static resolution_t res = RESOLUTION_640x480;
static bitdepth_t bit = DEPTH_32_BPP;

int main(void)
{
    /* enable interrupts (on the CPU) */
    init_interrupts();

    /* Initialize peripherals */
    display_init( res, bit, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE );
    console_init();
    dfs_init(DFS_DEFAULT_LOCATION);
    controller_init();
    timer_init();
    rtc_init();

    console_set_render_mode(RENDER_MANUAL);
    sprite_t *testSprite = NULL;
    int fp = dfs_open("/TestSprite.sprite");
    if(fp > 0)
    {
        testSprite = malloc( dfs_size( fp ) );
        dfs_read( testSprite, 1, dfs_size( fp ), fp );
        dfs_close( fp );
    }

    while(1) 
    {
        console_clear();
        PrintControllerStats();
        printf("Is it null? %s\n", (testSprite == NULL) ? "YES": "NO");
        console_render();
        continue;
    }
}
