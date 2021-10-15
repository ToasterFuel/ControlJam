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
    if (list->head == NULL)
        return;
    
    Node *temp = list->head;

    RectangleGraphic_Draw(temp->value, disp);
    while (temp->next != NULL)
    {
        temp = temp->next;
        RectangleGraphic_Draw(temp->value, disp);
    }
}