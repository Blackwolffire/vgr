#include <math.h>
#include "audio.h"
#include "physical_engine.h"
#include "enemy.h"

static void collision(struct game_state *ga_st, struct game_object *go,
                      struct game_object *gob)
{
    if (gob->type == DEATH_BLOCK)
    {
        if (go == ga_st->player.go)
            ga_st->player.alive = 0;
    }
    else if (gob->type == EXIT)
    {
        if (go == ga_st->player.go)
            ga_st->player.won = 1;
    }
    else if (gob->type == PROJECTILE)
    {
        go->life -= LASER_POWER;
        if (go->life <= 0)
        {
            if (go == ga_st->player.go)
                ga_st->player.alive = 0;
            go_free(ga_st->l_go_ent, go);
        }
        go_free(ga_st->l_go_ent, gob);
    }
    else if (go->type == PROJECTILE)
    {
        gob->life -= LASER_POWER;
        if (gob->life <= 0)
        {
            if (gob == ga_st->player.go)
                ga_st->player.alive = 0;
            go_free(ga_st->l_go_ent, gob);
        }
        go_free(ga_st->l_go_ent, go);
    }
    else if (go->type == PLAYER && gob->type == ENEMY)
    {
        go->life -= LASER_POWER;
        if (go->life <= 0)
            ga_st->player.alive = 0;
    }
    play_chunk(ga_st, gob);
}

static void update_speed(struct game_object *go)
{
    if (go->type == PROJECTILE)
        return;
    go->speed.y += GRAVITY;
}

static void ph_go_dec_update(struct game_state *ga_st, struct game_object *go)
{
    if (!ga_st)
        return;
    char whrx = 0. < go->target.x;
    char whry = 0. < go->target.y;
    struct vec2 tmp;

    if (!go->target.x && !go->target.y)
        return;
    tmp = vsub(go->target, go->speed);
    if ((whrx && tmp.x < 0.) || (!whrx && tmp.x > 0.))
    {
        go->pos.x += go->target.x;
        go->target.x = 0.;
        go->speed.x = 0.;
    }
    if ((whry && tmp.y < 0.) || (!whry && tmp.y > 0.))
    {
        go->pos.y += go->target.y;
        go->target.y = 0.;
        go->speed.y = 0.;
    }
    go->isupdate = 1;
}

static void ph_go_ent_update(struct game_state *ga_st, struct game_object *go,
                             char up_speed)
{
    char collid = 0;
    char floor_col = 0;
    char first_floor_col = 0;
    struct game_object *dec = ga_st->l_go_dec;
    struct vec2 pos = vadd(go->pos, go->speed);

    if (go->speed.x || go->speed.y)
        go->isupdate = 1;

    while (dec)
    {
        if (go == dec)
        {
            dec = dec->next;
            continue;
        }
        if (pos.x >= dec->pos.x && pos.x <= dec->pos.x + dec->gpos.w
            && pos.y >= dec->pos.y && pos.y <= dec->pos.y + dec->gpos.h)
        {
            collid = 1;
            collision(ga_st, go, dec);
            dec->isupdate = 1;
        }
        else if (pos.x + go->gpos.w >= dec->pos.x
                && pos.x + go->gpos.w <= dec->pos.x + dec->gpos.w
                && pos.y >= dec->pos.y && pos.y <= dec->pos.y + dec->gpos.h)
        {
            collid = 1;
            collision(ga_st, go, dec);
            dec->isupdate = 1;
        }
        else if (pos.x >= dec->pos.x && pos.x <= dec->pos.x + dec->gpos.w
                 && pos.y + go->gpos.h >= dec->pos.y
                 && pos.y + go->gpos.h <= dec->pos.y + dec->gpos.h)
        {
            collid = floor_col = 1;
            collision(ga_st, go, dec);
            dec->isupdate = 1;
        }
        else if (pos.x + go->gpos.w >= dec->pos.x
                 && pos.x + go->gpos.w <= dec->pos.x + dec->gpos.w
                 && pos.y + go->gpos.h >= dec->pos.y
                 && pos.y + go->gpos.h <= dec->pos.y + dec->gpos.h)
        {
            collid = floor_col = 1;
            collision(ga_st, go, dec);
            dec->isupdate = 1;
        }
        if (!first_floor_col && floor_col)
        {
            go->speed.y = dec->speed.y;
            go->speed.x += dec->speed.x;
            first_floor_col = 1;
        }
        dec = dec->next;
    }
    if (!collid)
    {
        go->pos = pos;
        if (go->pos.y > ga_st->lv_h)
        {
            if (go == ga_st->player.go)
                ga_st->player.alive = 0;
            go_free(ga_st->l_go_ent, go);
            return;
        }
    }
    if (up_speed)
        update_speed(go);
    if (floor_col)
    {
        go->speed.y = 0;
        if (go == ga_st->player.go)
            ga_st->player.can_jump = 1;
    }
}

static void ph_go_ent_ent_up(struct game_state *ga_st, struct game_object *go)
{
    struct game_object *ent = ga_st->l_go_ent;
    struct vec2 pos = go->pos;

    while (ent)
    {
        if (go == ent)
        {
            ent = ent->next;
            continue;
        }
        if (pos.x >= ent->pos.x && pos.x <= ent->pos.x + ent->gpos.w
            && pos.y >= ent->pos.y && pos.y <= ent->pos.y + ent->gpos.h)
        {
            collision(ga_st, go, ent);
            ent->isupdate = 1;
        }
        else if (pos.x + go->gpos.w >= ent->pos.x
                && pos.x + go->gpos.w <= ent->pos.x + ent->gpos.w
                && pos.y >= ent->pos.y && pos.y <= ent->pos.y + ent->gpos.h)
        {
            collision(ga_st, go, ent);
            ent->isupdate = 1;
        }
        else if (pos.x >= ent->pos.x && pos.x <= ent->pos.x + ent->gpos.w
                 && pos.y + go->gpos.h >= ent->pos.y
                 && pos.y + go->gpos.h <= ent->pos.y + ent->gpos.h)
        {
            collision(ga_st, go, ent);
            ent->isupdate = 1;
        }
        else if (pos.x + go->gpos.w >= ent->pos.x
                 && pos.x + go->gpos.w <= ent->pos.x + ent->gpos.w
                 && pos.y + go->gpos.h >= ent->pos.y
                 && pos.y + go->gpos.h <= ent->pos.y + ent->gpos.h)
        {
            collision(ga_st, go, ent);
            ent->isupdate = 1;
        }
        ent = ent->next;
    }
}

static void ph_update(struct game_state *ga_st, char up_speed)
{
    struct game_object *go = ga_st->l_go_ent;

    while (go)
    {
        ph_go_ent_update(ga_st, go, up_speed);
        if (go->type != ENEMY)
            ph_go_ent_ent_up(ga_st, go);
        go = go->next;
    }
    go = ga_st->l_go_dec;
    while (go)
    {
        ph_go_dec_update(ga_st, go);
        go = go->next;
    }
}

void physical_update(struct game_state *ga_st)
{
    char up_speed = 0;
    unsigned int tick;

    if(ga_st->ph_up_tick + PHYSICAL_UPDATE_DELAY <= (tick = SDL_GetTicks()))
    {
        ga_st->ph_up_tick = tick;
        if(ga_st->go_tick + GRAVITY_DELAY <= tick)
        {
            up_speed = 1;
            ga_st->go_tick = tick;
        }
        ph_update(ga_st, up_speed);
    }
}
