#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

#define PLAYER_LIFE 1000
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

struct player
{
    struct game_object *go;
};

#endif /* ! PLAYER_H */
