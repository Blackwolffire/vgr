#include "player.h"

void player_jump(struct player *player)
{
    if (!player->can_jump)
        return;
    player->go->speed.y = -PLAYER_JUMP;
    player->can_jump = 0;
}

void player_run(struct player *player, char direction)
{
    player->go->speed.x = direction * PLAYER_SPEED;
}
