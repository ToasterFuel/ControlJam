#include <stdlib.h>

#include "ECS.h"
#include "Graphics.h"
#include "LinkedList.h"
#include "Physics.h"
#include "Vector2.h"

void FreeEntity(Entity *entity, ComponentsList *componentsList)
{
    if (entity->components.transform)
        free(entity->components.transform);
    if (entity->components.rigidBody)
        free(entity->components.rigidBody);
    if (entity->components.boxCollider)
        free(entity->components.boxCollider);
    if (entity->components.circleCollider)
        free(entity->components.circleCollider);
}

void AddComponentTransform(Entity *entity, ComponentsList *componentsList, Vector2 position, Vector2 rotation)
{
    entity->components.transform = malloc(sizeof(Transform));
    entity->components.transform->position = position;
    entity->components.transform->rotation = rotation;
    LL_Insert(entity->components.transform, componentsList->transformComponents);
}

void AddComponentRectangleGraphic(Entity *entity, ComponentsList *componentsList, float width, float height, uint32_t colour)
{
    entity->components.rectangleGraphic = malloc(sizeof(RectangleGraphic));
    if (!(entity->components.transform))
        AddComponentTransform(entity, componentsList, ZeroVector(), ZeroVector());
    entity->components.rectangleGraphic->transform = entity->components.transform;
    entity->components.rectangleGraphic->width = width;
    entity->components.rectangleGraphic->height = height;
    entity->components.rectangleGraphic->colour = colour;
    LL_Insert(entity->components.rectangleGraphic, componentsList->rectangleGraphicComponents);
}

void AddComponentRigidBody(Entity *entity, ComponentsList *componentsList, float mass)
{
    entity->components.rigidBody = malloc(sizeof(RigidBody));
    if (!(entity->components.transform))
        AddComponentTransform(entity, componentsList, ZeroVector(), ZeroVector());
    entity->components.rigidBody->transform = entity->components.transform;
    entity->components.rigidBody->mass = mass;
    entity->components.rigidBody->velocity = ZeroVector();
    entity->components.rigidBody->acceleration = ZeroVector();
    LL_Insert(entity->components.rigidBody, componentsList->rigidBodyComponents);
}

void AddComponentBoxCollider(Entity *entity, ComponentsList *componentsList, Vector2 localPosition, float width, float height)
{
    entity->components.boxCollider = malloc(sizeof(BoxCollider));
    if (!(entity->components.transform))
        AddComponentTransform(entity, componentsList, ZeroVector(), ZeroVector());
    entity->components.boxCollider->transform = entity->components.transform;
    entity->components.boxCollider->localPosition = localPosition;
    entity->components.boxCollider->width = width;
    entity->components.boxCollider->height = height;
    LL_Insert(entity->components.boxCollider, componentsList->boxColliderComponents);
}

void AddComponentCircleCollider(Entity *entity, ComponentsList *componentsList, Vector2 localPosition, float radius)
{
    entity->components.circleCollider = malloc(sizeof(CircleCollider));
    if (!(entity->components.transform))
        AddComponentTransform(entity, componentsList, ZeroVector(), ZeroVector());
    entity->components.circleCollider->transform = entity->components.transform;
    entity->components.circleCollider->localPosition = localPosition;
    entity->components.circleCollider->radius = radius;
    LL_Insert(entity->components.circleCollider, componentsList->circleColliderComponents);
}

void ECS_CreateComponentsList(ComponentsList *componentsList) {
    LL_Create(componentsList->transformComponents);
    LL_Create(componentsList->rectangleGraphicComponents);
    LL_Create(componentsList->rigidBodyComponents);
    LL_Create(componentsList->boxColliderComponents);
    LL_Create(componentsList->circleColliderComponents);
}

void ECS_UpdateComponents(ComponentsList *componentsList, float deltaTime)
{
    RigidBody_UpdateAll(componentsList->rigidBodyComponents, deltaTime);
}

void ECS_DrawComponents(ComponentsList *componentsList, display_context_t disp) {
    RectangleGraphic_DrawAll(componentsList->rectangleGraphicComponents, disp);
}
