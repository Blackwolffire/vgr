#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "engine.h"
#include "constant_sprite.h"
#include "enemy.h"

struct vec2 vadd(struct vec2 a, struct vec2 b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

struct vec2 vsub(struct vec2 a, struct vec2 b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

void go_ent_list_add(struct game_state *ga_st, struct game_object *go)
{
    go->next = ga_st->l_go_ent;
    ga_st->l_go_ent = go;
}

void go_dec_list_add(struct game_state *ga_st, struct game_object *go)
{
    go->next = ga_st->l_go_dec;
    ga_st->l_go_dec = go;
}

static void game_state_init(struct game_state *ga_st)
{
    ga_st->l_go_ent = NULL;
    ga_st->l_go_dec = NULL;
    ga_st->go_tick = 0;
    ga_st->ph_up_tick = 0;
    ga_st->player.alive = 1;
    ga_st->player.won = 0;
    ga_st->player.hit_tick = 0;
    ga_st->player.shoot_tick = 0;
    ga_st->enemy_tick = 0;
}

static void load_go(struct game_state *ga_st, int x, int y, char type)
{
    struct game_object *go = malloc(sizeof(struct game_object));

    go->pos.x = x;
    go->pos.y = y;
    go->speed.x = 0.;
    go->speed.y = 0.;
    go->isupdate = 1;

    if (type == '1')
    {
        ga_st->player.go = go;
        go->life = PLAYER_LIFE;
        go->type = PLAYER;
        go_ent_list_add(ga_st, go);
        go->gpos.w = PLAYER_WIDTH;
        go->gpos.h = PLAYER_HEIGHT;
    }
    else if (type == '3')
    {
        go->type = DECOR;
        go_dec_list_add(ga_st, go);
        go->gpos.w = FLOOR_WIDTH;
        go->gpos.h = FLOOR_HEIGHT;
    }
    else if (type == '5')
    {
        go->type = ENEMY;
        go->life = ENEMY_LIFE;
        go_ent_list_add(ga_st, go);
        go->gpos.w = ENEMY_WIDTH;
        go->gpos.h = ENEMY_HEIGHT;
    }
    else if (type == 'a')
    {
        go->type = DEATH_BLOCK;
        go_dec_list_add(ga_st, go);
        go->gpos.w = FLOOR_WIDTH;
        go->gpos.h = FLOOR_HEIGHT; 
    }
    else if (type == '4')
    {
        go->type = DECOR_SUP;
        go_dec_list_add(ga_st, go);
        go->gpos.w = FLOOR_WIDTH;
        go->gpos.h = FLOOR_HEIGHT;
    }
    else if (type == 'b')
    {
        go->type = EXIT;
        go_dec_list_add(ga_st, go);
        go->gpos.w = FLOOR_WIDTH;
        go->gpos.h = FLOOR_HEIGHT;
    }
    else
        free(go);
}

void load_level(struct game_state *ga_st, char *fin)
{
    char *data;
    int fd;
    int width;
    int height;
    struct stat buf;

    game_state_init(ga_st);

    fd = open(fin, O_RDONLY);
    if (fd == -1)
        return;
    if (fstat(fd, &buf) < 0)
    {
        close(fd);
        return;
    }
    data = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    for (width = 0; width < buf.st_size && data[width] != '\n'; ++width)
        continue;
    ++width;
    height = buf.st_size / width;
    ga_st->lv_w = width * 16;
    ga_st->lv_h = height * 16;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width - 1; ++j)
        {
            char c = data[i * width + j];
            if (c != '0' && c != '\n')
                load_go(ga_st, j * 16, i * 16, data[i * width + j]);
        }
    }

    munmap(data, buf.st_size);
    close(fd);
}

void free_level(struct game_state *ga_st)
{
    go_list_free(ga_st->l_go_ent);
    go_list_free(ga_st->l_go_dec);
}

void shoot_enemy(struct game_state *ga_st)
{
    unsigned int tick = SDL_GetTicks();
    struct game_object *go;

    if (ga_st->enemy_tick + ENEMY_SHOOT <= tick)
        ga_st->enemy_tick = tick;
    else
        return;

    go = ga_st->l_go_ent;
    while (go)
    {
        if (go->type != ENEMY)
        {
            go = go->next;
            continue;
        }
        enemy_shoot(ga_st, go);
        go = go->next;
    }
}
