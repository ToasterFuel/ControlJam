#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "ECS.h"
#include "Globals.h"
#include "Graphics.h"
#include "Physics.h"
#include "Vector2.h"

void ECS_FreeByUUID(size_t uuid)
{
    for (std::vector<Entity>::iterator it = componentsList.entities.begin();
         it != componentsList.entities.end();
         it++)
    {
        if ((*it).uuid == uuid)
        {
            componentsList.entities.erase(it);
            break;
        }
    }

    componentsList.transformComponents.erase(uuid);
    componentsList.rectangleGraphicComponents.erase(uuid);
    componentsList.rigidBodyComponents.erase(uuid);
    componentsList.boxColliderComponents.erase(uuid);
    componentsList.circleColliderComponents.erase(uuid);
}

void ECS_AddEntity(Entity entity)
{
    componentsList.entities.push_back(entity);
}

void ECS_AddComponentTransform(size_t uuid, Vector2 position, Vector2 rotation)
{
    componentsList.transformComponents.insert(std::pair<size_t, Transform *>(uuid, (Transform *)malloc(sizeof(Transform))));
    std::unordered_map<size_t, Transform *>::iterator it = componentsList.transformComponents.find(uuid);
    it->second->position = position;
    it->second->rotation = rotation;

    for (std::vector<Entity>::iterator it = componentsList.entities.begin();
         it != componentsList.entities.end();
         it++)
    {
        if ((*it).uuid == uuid)
        {
            (it)->mask.set(1);
            break;
        }
    }
}

void ECS_AddComponentRectangleGraphic(size_t uuid, float width, float height, uint32_t colour)
{
    componentsList.rectangleGraphicComponents.insert(std::pair<size_t, RectangleGraphic *>(uuid, (RectangleGraphic *)malloc(sizeof(RectangleGraphic))));

    std::unordered_map<size_t, RectangleGraphic *>::iterator it = componentsList.rectangleGraphicComponents.find(uuid);
    it->second->width = width;
    it->second->height = height;
    it->second->colour = colour;

    if (componentsList.transformComponents.find(uuid) == componentsList.transformComponents.end())
        ECS_AddComponentTransform(uuid, ZeroVector(), ZeroVector());

    for (std::vector<Entity>::iterator it = componentsList.entities.begin();
         it != componentsList.entities.end();
         it++)
    {
        if ((*it).uuid == uuid)
        {
            (it)->mask.set(2);
            break;
        }
    }
}

void ECS_AddComponentRigidBody(size_t uuid, float mass)
{
    componentsList.rigidBodyComponents.insert(std::pair<size_t, RigidBody *>(uuid, (RigidBody *)malloc(sizeof(RigidBody))));

    std::unordered_map<size_t, RigidBody *>::iterator it = componentsList.rigidBodyComponents.find(uuid);
    it->second->mass = mass;
    it->second->velocity = ZeroVector();
    it->second->acceleration = ZeroVector();

    if (componentsList.transformComponents.find(uuid) == componentsList.transformComponents.end())
        ECS_AddComponentTransform(uuid, ZeroVector(), ZeroVector());

    for (std::vector<Entity>::iterator it = componentsList.entities.begin();
         it != componentsList.entities.end();
         it++)
    {
        if ((*it).uuid == uuid)
        {
            (it)->mask.set(3);
            break;
        }
    }
}

void ECS_AddComponentBoxCollider(size_t uuid, Vector2 localPosition, float width, float height)
{
    componentsList.boxColliderComponents.insert(std::pair<size_t, BoxCollider *>(uuid, (BoxCollider *)malloc(sizeof(BoxCollider))));

    std::unordered_map<size_t, BoxCollider *>::iterator it = componentsList.boxColliderComponents.find(uuid);
    it->second->localPosition = localPosition;
    it->second->width = width;
    it->second->height = height;

    if (componentsList.transformComponents.find(uuid) == componentsList.transformComponents.end())
        ECS_AddComponentTransform(uuid, ZeroVector(), ZeroVector());

    for (std::vector<Entity>::iterator it = componentsList.entities.begin();
         it != componentsList.entities.end();
         it++)
    {
        if ((*it).uuid == uuid)
        {
            (it)->mask.set(4);
            break;
        }
    }
}

void ECS_AddComponentCircleCollider(size_t uuid, Vector2 localPosition, float radius)
{
    componentsList.circleColliderComponents.insert(std::pair<size_t, CircleCollider *>(uuid, (CircleCollider *)malloc(sizeof(CircleCollider))));

    std::unordered_map<size_t, CircleCollider *>::iterator it = componentsList.circleColliderComponents.find(uuid);
    it->second->localPosition = localPosition;
    it->second->radius = radius;

    if (componentsList.transformComponents.find(uuid) == componentsList.transformComponents.end())
        ECS_AddComponentTransform(uuid, ZeroVector(), ZeroVector());

    for (std::vector<Entity>::iterator it = componentsList.entities.begin();
         it != componentsList.entities.end();
         it++)
    {
        if ((*it).uuid == uuid)
        {
            (it)->mask.set(5);
            break;
        }
    }
}

void ECS_UpdateComponents(float deltaTime)
{
    RigidBody_UpdateAll(deltaTime);
}

void ECS_DrawComponents(display_context_t disp)
{
    RectangleGraphic_DrawAll(disp);
}
