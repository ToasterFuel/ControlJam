#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <stdbool.h>

typedef struct
{
    float x;
    float y;
}Vector2;

typedef struct
{
    Vector2 position;
    float width;
    float height;
}BoxCollider;

typedef struct
{
    Vector2 position;
    float radius;
}CircleCollider;

Vector2 Difference(Vector2 position1, Vector2 position2);

float Length(Vector2 vector);

float Distance(Vector2 position1, Vector2 position2);

bool IsBoxColliding(BoxCollider first, BoxCollider second);

bool IsCircleColliding(CircleCollider first, CircleCollider second);

#endif
