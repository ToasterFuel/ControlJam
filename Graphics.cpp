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
    for (std::vector<Entity>::iterator it = componentsList.entities.begin();
        it != componentsList.entities.end();
        it++)
    {
        if ((*it).mask.test(2) /*componentsList.rectangleGraphicComponents.count((*it).uuid)*/)
            RectangleGraphic_Draw((*it).uuid, componentsList.rectangleGraphicComponents.at((*it).uuid), disp);
    }
}