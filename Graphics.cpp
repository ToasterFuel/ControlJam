#include <iterator>
#include <unordered_map>
#include <libdragon.h>

#include "ECS.h"
#include "Graphics.h"
#include "Vector2.h"

void RectangleGraphic_Draw(std::unordered_map<size_t, Transform *> transformMap, size_t uuid, RectangleGraphic *rectangle, display_context_t disp)
{
    graphics_draw_box(disp, transformMap.at(uuid)->position.x,
                      transformMap.at(uuid)->position.y,
                      rectangle->width,
                      rectangle->height,
                      rectangle->colour);
}

void RectangleGraphic_DrawAll(std::unordered_map<size_t, RectangleGraphic *> map, std::unordered_map<size_t, Transform *> transformMap, display_context_t disp)
{
    for (std::unordered_map<size_t, RectangleGraphic *>::iterator it = map.begin(); it != map.end(); it++)
    {
        RectangleGraphic_Draw(transformMap, it->first, it->second, disp);
    }
}