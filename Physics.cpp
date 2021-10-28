#include <stdbool.h>
#include <math.h>
#include <iterator>
#include <unordered_map>

#include "Physics.h"
#include "Vector2.h"

/* TODO: This needs to take localPosition into account, but it works for now */
bool BoxCollider_IsColliding(std::unordered_map<size_t, Transform *> transformMap, BoxCollider *first, size_t firstUUID, BoxCollider *second, size_t secondUUID)
{
    if (transformMap.at(firstUUID)->position.x - first->width / 2 < transformMap.at(secondUUID)->position.x + second->width / 2 &&
        transformMap.at(firstUUID)->position.x + first->width / 2 > transformMap.at(secondUUID)->position.x - second->width / 2 &&
        transformMap.at(firstUUID)->position.y - first->height / 2 < transformMap.at(secondUUID)->position.y + second->height / 2 &&
        transformMap.at(firstUUID)->position.y + first->height / 2 > transformMap.at(secondUUID)->position.y - second->height / 2)
    {
        return true;
    }
    return false;
}

/* TODO: This needs to take localPosition into account, but it works for now */
bool CircleCollider_IsColliding(std::unordered_map<size_t, Transform *> transformMap, CircleCollider *first, size_t firstUUID, CircleCollider *second, size_t secondUUID)
{
    if (Distance(transformMap.at(firstUUID)->position, transformMap.at(secondUUID)->position) < first->radius + second->radius)
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

void RigidBody_Update(std::unordered_map<size_t, Transform *> transformMap, size_t uuid, RigidBody *self, float deltaTime)
{
    self->velocity.x += self->acceleration.x * deltaTime;
    self->velocity.y += self->acceleration.y * deltaTime;

    transformMap.at(uuid)->position.x += self->velocity.x * deltaTime;
    transformMap.at(uuid)->position.y += self->velocity.y * deltaTime;

    /* Reset acceleration so it does not carry over */
    self->acceleration.x = 0;
    self->acceleration.y = 0;
}

void RigidBody_UpdateAll(std::unordered_map<size_t, RigidBody *> map, std::unordered_map<size_t, Transform *> transformMap, float deltaTime)
{
    for (std::unordered_map<size_t, RigidBody *>::iterator it = map.begin(); it != map.end(); it++)
    {
        RigidBody_Update(transformMap, it->first, it->second, deltaTime);
    }
}
