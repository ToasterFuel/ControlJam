#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <libdragon.h>
#include "ControllerTesting.h"

static resolution_t res = RESOLUTION_320x240;
static bitdepth_t bit = DEPTH_32_BPP;

int main(void)
{
    /* enable interrupts (on the CPU) */
    init_interrupts();

    /* Initialize peripherals */
    display_init( res, bit, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE );
    console_init();
    controller_init();
    timer_init();
    rtc_init();

    console_set_render_mode(RENDER_MANUAL);

    while(1) 
    {
        console_clear();
        PrintControllerStats();
        console_render();
        continue;
    }
}
