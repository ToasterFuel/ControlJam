#ifndef __ECS_H__
#define __ECS_H__

#include "Graphics.h"
#include "Physics.h"
#include "Vector2.h"

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

void FreeEntity(Entity *entity);

void AddComponentTransform(Entity *entity, Vector2 position, Vector2 rotation);

void AddComponentRectangleGraphic(Entity *entity, float width, float height, uint32_t colour);

void AddComponentRigidBody(Entity *entity, float mass);

void AddComponentBoxCollider(Entity *entity, Vector2 localPosition, float width, float height);

void AddComponentCircleCollider(Entity *entity, Vector2 localPosition, float radius);

#endif
