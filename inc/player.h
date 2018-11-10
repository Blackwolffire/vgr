#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

#define PLAYER_LIFE 1000
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define PLAYER_JUMP 50
#define PLAYER_SPEED 10

struct player
{
    struct game_object *go;
    char can_jump;
};

void player_jump(struct player *player);
void player_run(struct player *player, char direction);

#endif /* ! PLAYER_H */
