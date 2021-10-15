#ifndef __ECS_H__
#define __ECS_H__

#include "Graphics.h"
#include "LinkedList.h"
#include "Physics.h"
#include "Vector2.h"

typedef struct ComponentsList
{
    LinkedList *transformComponents;
    LinkedList *rectangleGraphicComponents;
    LinkedList *rigidBodyComponents;
    LinkedList *boxColliderComponents;
    LinkedList *circleColliderComponents;

} ComponentsList;

typedef struct Components
{
    Transform *transform;
    RectangleGraphic *rectangleGraphic;
    RigidBody *rigidBody;
    BoxCollider *boxCollider;
    CircleCollider *circleCollider;
} Components;

typedef struct Entity
{
    unsigned int uuid;
    Components components;
} Entity;

void ECS_FreeEntity(Entity *entity, ComponentsList *componentsList);

void ECS_AddComponentTransform(Entity *entity, ComponentsList *componentsList, Vector2 position, Vector2 rotation);

void ECS_AddComponentRectangleGraphic(Entity *entity, ComponentsList *componentsList, float width, float height, uint32_t colour);

void ECS_AddComponentRigidBody(Entity *entity, ComponentsList *componentsList, float mass);

void ECS_AddComponentBoxCollider(Entity *entity, ComponentsList *componentsList, Vector2 localPosition, float width, float height);

void ECS_AddComponentCircleCollider(Entity *entity, ComponentsList *componentsList, Vector2 localPosition, float radius);

void ECS_CreateComponentsList(ComponentsList *componentsList);

void ECS_UpdateComponents(ComponentsList *componentsList, float deltaTime);

void ECS_DrawComponents(ComponentsList *componentsList, display_context_t disp);

#endif
