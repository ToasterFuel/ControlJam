#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <stdbool.h>
#include "Vector2.h"

typedef struct BoxCollider
{
    Transform *transform;
    Vector2 localPosition;
    float width;
    float height;
} BoxCollider;

typedef struct CircleCollider
{
    Transform *transform;
    Vector2 localPosition;
    float radius;
} CircleCollider;

typedef struct RigidBody
{
    Transform *transform;
    float mass;
    Vector2 velocity;
    Vector2 acceleration;
} RigidBody;

bool BoxCollider_IsColliding(BoxCollider *first, BoxCollider *second);

bool CircleCollider_IsColliding(CircleCollider *first, CircleCollider *second);

void RigidBody_AddForce(RigidBody *self, Vector2 force, bool isImpulse);

void RigidBody_UpdateRigidBody(RigidBody *self, float deltaTime);

void RigidBody_UpdateAll(LinkedList *list, float deltaTime);

#endif
