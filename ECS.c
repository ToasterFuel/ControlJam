#include <stdlib.h>

#include "ECS.h"
#include "Physics.h"
#include "Vector2.h"

void FreeEntity(Entity *entity)
{
    if (entity->components.transform) free(entity->components.transform);
    if (entity->components.rigidBody) free(entity->components.rigidBody);
    if (entity->components.boxCollider) free(entity->components.boxCollider);
    if (entity->components.circleCollider) free(entity->components.circleCollider);
}

void AddComponentTransform(Entity *entity, Vector2 position, Vector2 rotation)
{
    entity->components.transform = malloc(sizeof(Transform));
    entity->components.transform->position = position;
    entity->components.transform->rotation = rotation;
}

void AddComponentRectangleGraphic(Entity *entity, float width, float height, uint32_t colour)
{
    entity->components.rectangleGraphic = malloc(sizeof(RectangleGraphic));
    if (!(entity->components.transform)) AddComponentTransform(entity, ZeroVector(), ZeroVector());
    entity->components.rectangleGraphic->width = width;
    entity->components.rectangleGraphic->height = height;
    entity->components.rectangleGraphic->colour = colour;
}

void AddComponentRigidBody(Entity *entity, float mass)
{
    entity->components.rigidBody = malloc(sizeof(RigidBody));
    if (!(entity->components.transform)) AddComponentTransform(entity, ZeroVector(), ZeroVector());
    entity->components.boxCollider->transform = entity->components.transform;
    entity->components.rigidBody->mass = mass;
    entity->components.rigidBody->velocity = ZeroVector();
    entity->components.rigidBody->acceleration = ZeroVector();
}

void AddComponentBoxCollider(Entity *entity, Vector2 localPosition, float width, float height)
{
    entity->components.boxCollider = malloc(sizeof(BoxCollider));
    if (!(entity->components.transform)) AddComponentTransform(entity, ZeroVector(), ZeroVector());
    entity->components.boxCollider->transform = entity->components.transform;
    entity->components.boxCollider->localPosition = localPosition;
    entity->components.boxCollider->width = width;
    entity->components.boxCollider->height = height;
}

void AddComponentCircleCollider(Entity *entity, Vector2 localPosition, float radius)
{
    entity->components.circleCollider = malloc(sizeof(CircleCollider));
    if (!(entity->components.transform)) AddComponentTransform(entity, ZeroVector(), ZeroVector());
    entity->components.circleCollider->transform = entity->components.transform;
    entity->components.circleCollider->localPosition = localPosition;
    entity->components.circleCollider->radius = radius;
    
}
