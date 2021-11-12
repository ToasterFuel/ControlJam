#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <iterator>
#include <unordered_map>
#include <libdragon.h>

#include "Vector2.h"

typedef struct RectangleGraphic
{
    Transform *transform;
    float width;
    float height;
    uint32_t colour;
} RectangleGraphic;

void RectangleGraphic_Draw(size_t uuid, RectangleGraphic *rectangle, display_context_t disp);

void RectangleGraphic_DrawAll(display_context_t disp);

#endif
