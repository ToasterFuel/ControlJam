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

void ECS_FreeEntity(Entity *entity);

void ECS_FreeByUUID(size_t uuid);

void ECS_AddComponentTransform(size_t uuid, Vector2 position, Vector2 rotation);

void ECS_AddComponentRectangleGraphic(size_t uuid, float width, float height, uint32_t colour);

void ECS_AddComponentRigidBody(size_t uuid, float mass);

void ECS_AddComponentBoxCollider(size_t uuid, Vector2 localPosition, float width, float height);

void ECS_AddComponentCircleCollider(size_t uuid, Vector2 localPosition, float radius);

void ECS_UpdateComponents(float deltaTime);

void ECS_DrawComponents(display_context_t disp);

#endif
