#include <iterator>
#include <unordered_map>
#include <libdragon.h>

#include "ECS.h"
#include "Globals.h"
#include "Graphics.h"
#include "Vector2.h"

void RectangleGraphic_Draw(size_t uuid, RectangleGraphic *rectangle, display_context_t disp)
{
    graphics_draw_box(disp, componentsList.transformComponents.at(uuid)->position.x,
                      componentsList.transformComponents.at(uuid)->position.y,
                      rectangle->width,
                      rectangle->height,
                      rectangle->colour);
}

void RectangleGraphic_DrawAll(display_context_t disp)
{
    for (std::unordered_map<size_t, RectangleGraphic *>::iterator it = componentsList.rectangleGraphicComponents.begin();
        it != componentsList.rectangleGraphicComponents.end();
        it++)
    {
        RectangleGraphic_Draw(it->first, it->second, disp);
    }
}