#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <libdragon.h>
#include <stdbool.h>

#include "ControllerTesting.h"
#include "Physics.h"

static resolution_t res = RESOLUTION_640x480;
static bitdepth_t bit = DEPTH_32_BPP;

static float moveSpeed = 0.1;

int main(void)
{
    /* enable interrupts (on the CPU) */
    init_interrupts();

    /* Initialize peripherals */
    display_init( res, bit, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE );
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

    /* Basic Collision Testing */
    BoxCollider playerCollider;
    playerCollider.position.x = 100;
    playerCollider.position.y = 100;
    playerCollider.width = 50;
    playerCollider.height = 50;

    BoxCollider obstacleCollider;
    obstacleCollider.position.x = 200;
    obstacleCollider.position.y = 150;
    obstacleCollider.width = 50;
    obstacleCollider.height = 50;


    /* Main loop test */
    while(1)
    {
        static display_context_t disp = 0;

        /* Grab a render buffer */
        while( !(disp = display_lock()) );

        /* Fill the screen */
        graphics_fill_screen( disp, 0x0 );

        /* Set the text output color */
        graphics_set_color(0xFFFFFFFF, 0x0);

        if (IsBoxColliding(playerCollider, obstacleCollider)) {
            graphics_draw_text( disp, 20, 20, "OMG COLLIDING!!!" );
        }
        else {
            graphics_draw_text( disp, 20, 20, "SAFE" );
        }

        /* Draw boxes */
        graphics_draw_box(disp, playerCollider.position.x, playerCollider.position.y, playerCollider.width, playerCollider.height, 0xFF0000FF);
        graphics_draw_box(disp, obstacleCollider.position.x, obstacleCollider.position.y, obstacleCollider.width, obstacleCollider.height, 0x0000FFFF);

        /* To do initialize routines */
        controller_scan();

        struct controller_data keys = get_keys_pressed();

        /* Only checking player 1's controller */
        playerCollider.position.x += moveSpeed * keys.c[0].x;
        playerCollider.position.y -= moveSpeed * keys.c[0].y;

        /* PrintControllerStats(); */
        /* printf("Is it null? %s\n", (testSprite == NULL) ? "YES": "NO"); */

        /* Force backbuffer flip */
        display_show(disp);

        continue;
    }
}
