#include "player.h"

void player_jump(struct game_state *ga_st)
{
    if (!ga_st->player.can_jump)
        return;
    ga_st->player.go->speed.y = -PLAYER_JUMP;
    ga_st->player.can_jump = 0;
}

void player_run(struct game_state *ga_st, char direction)
{
    ga_st->player.go->speed.x = direction * PLAYER_SPEED;
}
