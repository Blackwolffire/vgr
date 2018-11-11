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
    if (direction == 0)
    {
        player->go->animation = 0;
        if (player->go->animation == 2)
            player->go->frame = 1;
        else
            player->go->frame = 0;
    }
    else if (direction == 1)
    {
        player->go->animation = 1;
        player->go->frame = (player->go->frame + 1) % 7;
    }
    else
    {
        player->go->animation = 2;
        player->go->frame = (player->go->frame + 1) % 7;
    }
}
