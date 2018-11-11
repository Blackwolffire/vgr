#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

#define PLAYER_LIFE 1000
#define PLAYER_WIDTH 19
#define PLAYER_HEIGHT 52
#define PLAYER_JUMP 7
#define PLAYER_SPEED 2

struct player
{
    char alive;
    char can_jump;
    struct game_object *go;
};

void player_jump(struct player *player);
void player_run(struct player *player, char direction);

#endif /* ! PLAYER_H */
