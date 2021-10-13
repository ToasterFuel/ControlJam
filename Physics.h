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

bool IsBoxColliding(BoxCollider *first, BoxCollider *second);

bool IsCircleColliding(CircleCollider *first, CircleCollider *second);

void AddForce(RigidBody *self, Vector2 force, bool isImpulse);

void UpdateRigidBody(RigidBody *self, float deltaTime);

#endif
