#include <stdbool.h>
#include <math.h>

#include "Physics.h"

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

bool IsBoxColliding(BoxCollider first, BoxCollider second)
{
    if (first.position.x - first.width / 2 < second.position.x + second.width / 2 &&
        first.position.x + first.width / 2 > second.position.x - second.width / 2 &&
        first.position.y - first.height / 2 < second.position.y + second.height / 2 &&
        first.position.y + first.height / 2 > second.position.y - second.height / 2)
    {
          return true;
    }
    return false;
}

bool IsCircleColliding(CircleCollider first, CircleCollider second)
{
    if (Distance(first.position, second.position) < first.radius + second.radius) {
        return true;
    }
    return false;
}
