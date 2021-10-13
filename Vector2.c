#include <math.h>

#include "Vector2.h"

Vector2 Difference(Vector2 position1, Vector2 position2)
{
    Vector2 result;
    result.x = position1.x - position2.x;
    result.y = position1.y - position2.y;
    return result;
}

float Length(Vector2 vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Distance(Vector2 position1, Vector2 position2)
{
    return Length(Difference(position1, position2));
}

static Vector2 zeroVector = {.x = 0, .y = 0};
Vector2 ZeroVector()
{
    return zeroVector;
}