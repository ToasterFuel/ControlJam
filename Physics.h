#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <iterator>
#include <iostream>
#include <unordered_map>
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

bool BoxCollider_IsColliding(std::unordered_map<size_t, Transform *> transformMap, BoxCollider *first, size_t firstUUID, BoxCollider *second, size_t secondUUID);

bool CircleCollider_IsColliding(std::unordered_map<size_t, Transform *> transformMap, CircleCollider *first, size_t firstUUID, CircleCollider *second, size_t secondUUID);

void RigidBody_AddForce(RigidBody *self, Vector2 force, bool isImpulse);

void RigidBody_Update(std::unordered_map<size_t, Transform *> transformMap, size_t uuid, RigidBody *self, float deltaTime);

void RigidBody_UpdateAll(std::unordered_map<size_t, RigidBody *> map, std::unordered_map<size_t, Transform *> transformMap, float deltaTime);

#endif
