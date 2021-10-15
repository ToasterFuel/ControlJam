#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <libdragon.h>

#include "LinkedList.h"
#include "Vector2.h"

typedef struct RectangleGraphic
{
    Transform *transform;
    float width;
    float height;
    uint32_t colour;
} RectangleGraphic;

void RectangleGraphic_Draw(RectangleGraphic *rectangle, display_context_t disp);

void RectangleGraphic_DrawAll(LinkedList *list, display_context_t disp);

#endif
