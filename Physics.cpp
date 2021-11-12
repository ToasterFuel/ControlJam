#include <stdbool.h>
#include <math.h>
#include <iterator>
#include <unordered_map>

#include "Globals.h"
#include "Physics.h"
#include "Vector2.h"

/* TODO: This needs to take localPosition into account, but it works for now */
bool BoxCollider_IsColliding(BoxCollider *first, size_t firstUUID, BoxCollider *second, size_t secondUUID)
{
    if (componentsList.transformComponents.at(firstUUID)->position.x < componentsList.transformComponents.at(secondUUID)->position.x + second->width  &&
        componentsList.transformComponents.at(firstUUID)->position.x + first->width > componentsList.transformComponents.at(secondUUID)->position.x &&
        componentsList.transformComponents.at(firstUUID)->position.y < componentsList.transformComponents.at(secondUUID)->position.y + second->height &&
        componentsList.transformComponents.at(firstUUID)->position.y + first->height > componentsList.transformComponents.at(secondUUID)->position.y)
    {
        return true;
    }
    return false;
}

/* TODO: This needs to take localPosition into account, but it works for now */
bool CircleCollider_IsColliding(CircleCollider *first, size_t firstUUID, CircleCollider *second, size_t secondUUID)
{
    if (Distance(componentsList.transformComponents.at(firstUUID)->position, componentsList.transformComponents.at(secondUUID)->position) < first->radius + second->radius)
    {
        return true;
    }
    return false;
}

/* TODO: Implement this correctly */
void RigidBody_AddForce(RigidBody *self, Vector2 force, bool isImpulse)
{
    self->acceleration.x += force.x / self->mass;
    self->acceleration.y += force.y / self->mass;
}

void RigidBody_Update(size_t uuid, RigidBody *self, float deltaTime)
{
    self->velocity.x += self->acceleration.x * deltaTime;
    self->velocity.y += self->acceleration.y * deltaTime;

    componentsList.transformComponents.at(uuid)->position.x += self->velocity.x * deltaTime;
    componentsList.transformComponents.at(uuid)->position.y += self->velocity.y * deltaTime;

    // Stop moving if moving out of bounds
    if (componentsList.transformComponents.at(uuid)->position.x < 0)
    {
        componentsList.transformComponents.at(uuid)->position.x = 0;
        self->velocity.x = 0;
    }
    else if (componentsList.transformComponents.at(uuid)->position.x + componentsList.boxColliderComponents.at(uuid)->width > SCREEN_X)
    {
        componentsList.transformComponents.at(uuid)->position.x = SCREEN_X - componentsList.boxColliderComponents.at(uuid)->width;
        self->velocity.x = 0;
    }
    if (componentsList.transformComponents.at(uuid)->position.y < 0)
    {
        componentsList.transformComponents.at(uuid)->position.y = 0;
        self->velocity.y = 0;
    }
    else if (componentsList.transformComponents.at(uuid)->position.y + componentsList.boxColliderComponents.at(uuid)->height > SCREEN_Y)
    {
        componentsList.transformComponents.at(uuid)->position.y = SCREEN_Y - componentsList.boxColliderComponents.at(uuid)->height;
        self->velocity.y = 0;
    }

    /* Reset acceleration so it does not carry over */
    self->acceleration.x = 0;
    self->acceleration.y = 0;
}

void RigidBody_UpdateAll(float deltaTime)
{
    for (std::vector<Entity>::iterator it = componentsList.entities.begin();
        it != componentsList.entities.end();
        it++)
    {
        if ((*it).mask.test(3) /*componentsList.rigidBodyComponents.count((*it).uuid)*/)
            RigidBody_Update((*it).uuid, componentsList.rigidBodyComponents.at((*it).uuid), deltaTime);
    }
}
