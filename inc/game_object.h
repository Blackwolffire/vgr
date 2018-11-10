#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
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

    int frame;
    int animation;

    struct game_object *next;
};

void go_free(struct game_object *list, struct game_object *go);
void go_list_free(struct game_object *go);

#endif /* ! GAME_OBJECT_H */
