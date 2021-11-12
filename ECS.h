#ifndef __ECS_H__
#define __ECS_H__

#include <iterator>
#include <iostream>
#include <unordered_map>

#include "Graphics.h"
#include "Physics.h"
#include "Vector2.h"

typedef struct ComponentsList
{
    std::unordered_map<size_t, Transform *> transformComponents;
    std::unordered_map<size_t, RectangleGraphic *> rectangleGraphicComponents;
    std::unordered_map<size_t, RigidBody *> rigidBodyComponents;
    std::unordered_map<size_t, BoxCollider *> boxColliderComponents;
    std::unordered_map<size_t, CircleCollider *> circleColliderComponents;
} ComponentsList;

typedef struct Entity
{
    size_t uuid;
    /* ComponentMask mask; */
} Entity;

void ECS_FreeEntity(Entity *entity, ComponentsList *componentsList);

void ECS_FreeByUUID(size_t uuid, ComponentsList *componentsList);

void ECS_AddComponentTransform(size_t uuid, ComponentsList *componentsList, Vector2 position, Vector2 rotation);

void ECS_AddComponentRectangleGraphic(size_t uuid, ComponentsList *componentsList, float width, float height, uint32_t colour);

void ECS_AddComponentRigidBody(size_t uuid, ComponentsList *componentsList, float mass);

void ECS_AddComponentBoxCollider(size_t uuid, ComponentsList *componentsList, Vector2 localPosition, float width, float height);

void ECS_AddComponentCircleCollider(size_t uuid, ComponentsList *componentsList, Vector2 localPosition, float radius);

void ECS_UpdateComponents(ComponentsList *componentsList, float deltaTime);

void ECS_DrawComponents(ComponentsList *componentsList, display_context_t disp);

#endif
