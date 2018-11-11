#include <stdlib.h>
#include "player.h"
#include "constant_sprite.h"

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
        if (player->go->animation == 0)
            player->go->frame = 2;
        else
            player->go->frame = 1;
        player->go->animation = 0;
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

void player_shoot(struct player *player)
{
    unsigned int tick = SDL_GetTicks();
    struct game_object *go;

    if (player->shoot_tick + PLAYER_SHOOT < tick)
        player->shoot_tick = tick;
    else
        return;
    go = malloc(sizeof(struct game_object));
    go->pos.y = player->go->pos.y;
    go->speed.y = 0.;
    if (player->go->speed.x < 0.)
    {
        go->pos.x = player->go->pos.x - FLOOR_WIDTH * 2.;
        go->speed.x = -PLAYER_SPEED * 2;
    }
    else
    {
        go->pos.x = player->go->pos.x + player->go->gpos.w + FLOOR_WIDTH * 2.;
        go->speed.x = PLAYER_SPEED * 2;
    }
    go->type = PROJECTILE;
    go->next = player->go->next;
    player->go->next = go;
}
