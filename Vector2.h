#ifndef __VECTOR2_H__
#define __VECTOR2_H__

typedef struct Vector2
{
    float x;
    float y;
} Vector2;

/* TODO: Figure out if there's a better place to declare this */
typedef struct Transform
{
    Vector2 position;
    Vector2 rotation;
} Transform;

Vector2 Difference(Vector2 position1, Vector2 position2);

float Length(Vector2 vector);

float Distance(Vector2 position1, Vector2 position2);

Vector2 ZeroVector();

#endif
