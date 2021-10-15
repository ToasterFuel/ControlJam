#include <libdragon.h>

#include "LinkedList.h"
#include "Graphics.h"
#include "Vector2.h"

void RectangleGraphic_Draw(RectangleGraphic *rectangle, display_context_t disp)
{
    graphics_draw_box(disp, rectangle->transform->position.x,
                      rectangle->transform->position.y,
                      rectangle->width,
                      rectangle->height,
                      rectangle->colour);
}

void RectangleGraphic_DrawAll(LinkedList *list, display_context_t disp)
{
    Node *temp = list->head;
    while (temp->next != NULL)
    {
        RectangleGraphic_Draw(temp->value, disp);
        temp = temp->next;
    }
}