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

void RectangleGraphic_Draw(std::unordered_map<size_t, Transform *> transformMap, size_t uuid, RectangleGraphic *rectangle, display_context_t disp);

void RectangleGraphic_DrawAll(std::unordered_map<size_t, RectangleGraphic *> map, std::unordered_map<size_t, Transform *> transformMap, display_context_t disp);

#endif
