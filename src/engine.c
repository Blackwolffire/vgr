#include "engine.h"

struct vec2 vadd(struct vec2 a, struct vec2 b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

struct vec2 vsub(struct vec2 a, struct vec2 b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}
