#include <libdragon.h>

#include "Graphics.h"
#include "Vector2.h"

void DrawRectangle(RectangleGraphic *rectangle, display_context_t disp)
{
    graphics_draw_box(disp, rectangle->transform->position.x,
                            rectangle->transform->position.y,
                            rectangle->width,
                            rectangle->height,
                            rectangle->colour
    );
}