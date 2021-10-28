#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <unordered_map>

#include "ECS.h"
#include "Graphics.h"
#include "Physics.h"
#include "Vector2.h"

/* TODO: Remove node from components list as well */
void ECS_FreeEntity(Entity *entity, ComponentsList *componentsList)
{
    componentsList->transformComponents.erase(entity->uuid);
    componentsList->rectangleGraphicComponents.erase(entity->uuid);
    componentsList->rigidBodyComponents.erase(entity->uuid);
    componentsList->boxColliderComponents.erase(entity->uuid);
    componentsList->circleColliderComponents.erase(entity->uuid);
    free(entity);
    entity = NULL;
}

void ECS_AddComponentTransform(size_t uuid, ComponentsList *componentsList, Vector2 position, Vector2 rotation)
{
    componentsList->transformComponents.insert(std::pair<size_t, Transform *>(uuid, (Transform *) malloc(sizeof(Transform))));
    std::unordered_map<size_t, Transform *>::iterator it = componentsList->transformComponents.find(uuid);
    it->second->position = position;
    it->second->rotation = rotation;
}

void ECS_AddComponentRectangleGraphic(size_t uuid, ComponentsList *componentsList, float width, float height, uint32_t colour)
{
    componentsList->rectangleGraphicComponents.insert(std::pair<size_t, RectangleGraphic *>(uuid, (RectangleGraphic *) malloc(sizeof(RectangleGraphic))));
    
    std::unordered_map<size_t, RectangleGraphic *>::iterator it = componentsList->rectangleGraphicComponents.find(uuid);
    it->second->width = width;
    it->second->height = height;
    it->second->colour = colour;

    if (componentsList->transformComponents.find(uuid) == componentsList->transformComponents.end())
        ECS_AddComponentTransform(uuid, componentsList, ZeroVector(), ZeroVector());
}

void ECS_AddComponentRigidBody(size_t uuid, ComponentsList *componentsList, float mass)
{
    componentsList->rigidBodyComponents.insert(std::pair<size_t, RigidBody *>(uuid, (RigidBody *) malloc(sizeof(RigidBody))));
    
    std::unordered_map<size_t, RigidBody *>::iterator it = componentsList->rigidBodyComponents.find(uuid);
    it->second->mass = mass;
    it->second->velocity = ZeroVector();
    it->second->acceleration = ZeroVector();

    if (componentsList->transformComponents.find(uuid) == componentsList->transformComponents.end())
        ECS_AddComponentTransform(uuid, componentsList, ZeroVector(), ZeroVector());
}

void ECS_AddComponentBoxCollider(size_t uuid, ComponentsList *componentsList, Vector2 localPosition, float width, float height)
{
    componentsList->boxColliderComponents.insert(std::pair<size_t, BoxCollider *>(uuid, (BoxCollider *) malloc(sizeof(BoxCollider))));
    
    std::unordered_map<size_t, BoxCollider *>::iterator it = componentsList->boxColliderComponents.find(uuid);
    it->second->localPosition = localPosition;
    it->second->width = width;
    it->second->height = height;

    if (componentsList->transformComponents.find(uuid) == componentsList->transformComponents.end())
        ECS_AddComponentTransform(uuid, componentsList, ZeroVector(), ZeroVector());
}

void ECS_AddComponentCircleCollider(size_t uuid, ComponentsList *componentsList, Vector2 localPosition, float radius)
{
    componentsList->circleColliderComponents.insert(std::pair<size_t, CircleCollider *>(uuid, (CircleCollider *) malloc(sizeof(CircleCollider))));
    
    std::unordered_map<size_t, CircleCollider *>::iterator it = componentsList->circleColliderComponents.find(uuid);
    it->second->localPosition = localPosition;
    it->second->radius = radius;

    if (componentsList->transformComponents.find(uuid) == componentsList->transformComponents.end())
        ECS_AddComponentTransform(uuid, componentsList, ZeroVector(), ZeroVector());
}

void ECS_UpdateComponents(ComponentsList *componentsList, float deltaTime)
{
    RigidBody_UpdateAll(componentsList->rigidBodyComponents, componentsList->transformComponents, deltaTime);
}

void ECS_DrawComponents(ComponentsList *componentsList, display_context_t disp)
{
    RectangleGraphic_DrawAll(componentsList->rectangleGraphicComponents, componentsList->transformComponents, disp);
}
