#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <libdragon.h>

#include "Vector2.h"

typedef struct RectangleGraphic
{
    Transform *transform;
    float width;
    float height;
    uint32_t colour;
} RectangleGraphic;

void DrawRectangle(RectangleGraphic *rectangle, display_context_t disp);

#endif