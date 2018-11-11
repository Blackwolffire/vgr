#include "audio.h"
#include "engine.h"

void play_chunk(struct game_state *ga_st, struct game_object *dec)
{
    if (dec->type == DEATH_BLOCK || dec->type == ENEMY)
        Mix_PlayChannel(-1, ga_st->cri, 0);
    if (dec->type == EXIT)
        Mix_PlayChannel(-1, ga_st->win, 0);
}
