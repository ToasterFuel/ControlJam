#include <stdint.h>
#include <libdragon.h>
#include <n64sys.h>
#include <time.h>
#include "Time.h"

#define MS_IN_SEC_F (1000.0f)

static unsigned long lastFrameMS;
static unsigned long currentFrameMS;
static float deltaTime;

void TimeInit()
{
    timer_init();
    lastFrameMS = get_ticks_ms();
    currentFrameMS = lastFrameMS;
}

void TimeNewFrame()
{
    lastFrameMS = currentFrameMS;
    currentFrameMS = get_ticks_ms();
    deltaTime = (float)(currentFrameMS - lastFrameMS)/MS_IN_SEC_F;
}

float TimeGetDeltaTime()
{
    return deltaTime;
}

float TimeGetTimeSeconds()
{
    return (float)get_ticks_ms() / MS_IN_SEC_F;
}
