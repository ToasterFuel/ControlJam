#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>
#include "Time.h"
#include "ControllerTesting.h"

int main(void)
{
    /* enable interrupts (on the CPU) */
    init_interrupts();

    /* Initialize peripherals */
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE );
    dfs_init(DFS_DEFAULT_LOCATION);
    controller_init();
    rdp_init();
    TimeInit();

    console_set_render_mode(RENDER_MANUAL);
    sprite_t *planeSprite = NULL;
    sprite_t *testSprite = NULL;
    int fp = dfs_open("/plane.sprite");
    if(fp > 0)
    {
        planeSprite = (sprite_t*) malloc( dfs_size( fp ) );
        dfs_read( planeSprite, 1, dfs_size( fp ), fp );
        dfs_close( fp );
    }
    fp = dfs_open("/TestSprite.sprite");
    if(fp > 0)
    {
        testSprite = (sprite_t*) malloc( dfs_size( fp ) );
        dfs_read( testSprite, 1, dfs_size( fp ), fp );
        dfs_close( fp );
    }

    char buff[1024];
    unsigned int frameCount = 0;
    float timerStart = TimeGetTimeSeconds();
    float fps = 0;

    while(1) 
    {
        static display_context_t disp = 0;
        while( !(disp = display_lock()) );
        TimeNewFrame();
        frameCount++;
        graphics_fill_screen( disp, 0xFFFFFFFF );
        graphics_set_color( 0x0, 0xFFFFFFFF );
        console_clear();
        //PrintControllerStats();
        if(testSprite == NULL)
        {
            graphics_draw_text(disp, 20, 20, "Test sprite is null :(" );
        }
        else
        {
            float currentTime = TimeGetTimeSeconds();
            if(currentTime - timerStart > .1f)
            {
                fps = (float)frameCount / (currentTime - timerStart);
                timerStart = currentTime;
                frameCount = 0;
            }
            sprintf(buff, "fps: %f deltaTime: %f uptime: %f", fps, TimeGetDeltaTime(), currentTime);
            graphics_draw_text(disp, 20, 20, "Test sprite is NOT null :)" );
            graphics_draw_text(disp, 0, 0, buff);
            rdp_sync( SYNC_PIPE );
            rdp_set_default_clipping();
            rdp_enable_texture_copy();
            rdp_attach_display( disp );
            rdp_sync( SYNC_PIPE );
            if(planeSprite != NULL)
            {
                rdp_load_texture( 1, 0, MIRROR_DISABLED, planeSprite);
                rdp_draw_sprite( 1, 20, 50, MIRROR_DISABLED );
            }
            rdp_sync( SYNC_PIPE );
            rdp_load_texture( 0, 0, MIRROR_DISABLED, testSprite);
            rdp_draw_sprite( 0, 100, 100, MIRROR_DISABLED );
            rdp_draw_sprite( 0, 200, 200, MIRROR_DISABLED );
            rdp_draw_sprite( 0, 300, 300, MIRROR_DISABLED );
            rdp_detach_display();
        }

        display_show(disp);
        continue;
    }
}
