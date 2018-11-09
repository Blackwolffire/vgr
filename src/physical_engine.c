#include <math.h>
#include "physical_engine.h"

static void collision(struct game_state *g_st, struct game_object *go,
                 struct game_object *dec)
{
    ;
}

static void update_speed(struct game_object *go)
{
    if (GRAVITY > fabsf(go->speed.x))
        go->speed.x = 0.;
    else
        go->speed.x += (go->speed.x < 0.) ? GRAVITY : -GRAVITY;
    if (GRAVITY > fabsf(go->speed.y))
        go->speed.y = 0.;
    else
        go->speed.y += (go->speed.y < 0.) ? GRAVITY : -GRAVITY;
}

static void go_ph_update(struct game_state *g_st, struct game_object *go/*, update speed bool*/)
{
    char collid = 0;
    char floor_col = 0;
    unsigned int tick;
    struct game_object *dec = g_st->l_go_dec;
    struct vec2 pos = vadd(go->pos, go->speed);

    if (go->speed.x || go.speed.y)
        go->isupadte = 1;

    while (dec)
    {
        if (go == dec)
            continue;
        if (pos.x >= dec->pos.x && pos.x <= dec->pos.x + dec->gpos.w
             && pos.y >= dec->pos.y && pos.y <= dec->pos.y + dec->gpos.h)
        {
            collid = 1;
            collision(g_st, go, dec);
            dec->isupdate = 1;
        }
        else if (pos.x + go->gpos.w >= dec->pos.x
                && pos.x + go->gpos.w <= dec->pos.x + dec->gpos.w
                && pos.y >= dec->pos.y && pos.y <= dec->pos.y + dec->gpos.h)
        {
            collid = 1;
            collision(g_st, go, dec);
            dec->isupdate = 1;
        }
        else if (pos.x >= dec->pos.x && pos.x <= dec->pos.x + dec->gpos.w
                && pos.y + go->gpos.h >= dec->pos.y
                && pos.y + go->gpos.h <= dec->pos.y + dec->gpos.h)
        {
            collid = floor_col = 1;
            collision(g_st, go, dec);
            dec->isupdate = 1;
        }
        else if (pos.x + go->gpos.w >= dec->pos.x
                && pos.x + go->gpos.w <= dec->pos.x + dec->gpos.w
                && pos.y + go->gpos.h >= dec->pos.y
                && pos.y + go->gpos.h <= dec->pos.y + dec->gpos.h)
        {
            collid = floor_col = 1;
            collision(g_st, go, dec);
            dec->isupdate = 1;
        }
        dec = dec->next;
    }
    if (!collid)
        go->pos = pos;
    if (g_st->go_tick + 50 >= (tick = SDL_GetTicks())) // move out of this scope
    {
        gt_st->go_tick = tick;
        update_speed(go);
    }
    if (floor_col)
        go->speed.y = 0;
}

void ph_update(struct game_state *g_st)
{
    struct game_object *eg = g_st->l_go;

    while (eg)
    {
        go_ph_update(g_st, eg);
        eg = eg->next;
    }
}
