#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

#define PLAYER_LIFE 1000

struct player
{
    struct game_object *go;
};

#endif /* ! PLAYER_H */
