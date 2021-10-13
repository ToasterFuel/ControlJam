#include <stdbool.h>
#include <math.h>

#include "Physics.h"
#include "Vector2.h"

/* TODO: This needs to take localPosition into account, but it works for now */
bool IsBoxColliding(BoxCollider *first, BoxCollider *second)
{
    if (first->transform->position.x - first->width / 2 < second->transform->position.x + second->width / 2 &&
        first->transform->position.x + first->width / 2 > second->transform->position.x - second->width / 2 &&
        first->transform->position.y - first->height / 2 < second->transform->position.y + second->height / 2 &&
        first->transform->position.y + first->height / 2 > second->transform->position.y - second->height / 2)
    {
        return true;
    }
    return false;
}

/* TODO: This needs to take localPosition into account, but it works for now */
bool IsCircleColliding(CircleCollider *first, CircleCollider *second)
{
    if (Distance(first->transform->position, second->transform->position) < first->radius + second->radius)
    {
        return true;
    }
    return false;
}

/* TODO: Implement this correctly */
void AddForce(RigidBody *self, Vector2 force, bool isImpulse)
{
    self->acceleration.x += force.x / self->mass;
    self->acceleration.y += force.y / self->mass;
}

void UpdateRigidBody(RigidBody *self, float deltaTime)
{
    self->velocity.x += self->acceleration.x * deltaTime;
    self->velocity.y += self->acceleration.y * deltaTime;

    self->transform->position.x += self->velocity.x * deltaTime;
    self->transform->position.y += self->velocity.y * deltaTime;

    /* Reset acceleration so it does not carry over */
    self->acceleration.x = 0;
    self->acceleration.y = 0;
}
