#include <stdio.h>
#include "enemy.h"
#include "engine.h"
#include "constant_sprite.h"

void print_go(struct game_object *go)
{
    while (go)
    {
        printf("%d x %.2f y %.2f\n", go->type, go->pos.x, go->pos.y);
        go = go->next;
    }
    printf("---------------------------\n");
}

void enemy_shoot(struct game_state *ga_st, struct game_object *e)
{
    struct game_object *go;

//    print_go(ga_st->l_go_ent);
    go = malloc(sizeof(struct game_object));
    go->pos.y = e->pos.y + ENEMY_HEIGHT / 2;
    go->speed.y = 0.;
    go->life = 1;
    if (ga_st->player.go->pos.x < e->pos.x)
    {
        go->pos.x = e->pos.x - FLOOR_WIDTH * 5.;
        go->speed.x = -PLAYER_SPEED * 2;
    }
    else
    {
        go->pos.x = e->pos.x + e->gpos.w + FLOOR_WIDTH * 5.;
        go->speed.x = PLAYER_SPEED * 2;
    }
    go->type = PROJECTILE;
    go->next = ga_st->l_go_ent;
    ga_st->l_go_ent = go;
}

