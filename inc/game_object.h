#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "vec2.h"

enum go_type
{
    DECOR,
    PLAYER,
    ENNEMY,
    PROJECTILE
};

struct game_object
{
    SDL_Rect gpos;
    struct vec2 pos;
    struct vec2 speed;
    struct vec2 target;
    char isupdate;
    int life;
    enum go_type type;

    struct game_object *next;
};

#endif /* ! GAME_OBJECT_H */