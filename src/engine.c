#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "engine.h"

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
        ga_st->player->go = go;
        go->life = PLAYER_LIFE;
        go->type = PLAYER;
        go_ent_list_add(ga_st, go);
        go->gpos.w = PLAYER_WIDTH;
        go->gpos.h = PLAYER_HEIGHT;
    }
    if (type == '3')
    {
        go->type = DECOR;
        go_dec_list_add(ga_st, go);
        go->gpos.w = FLOOR_WIDTH;
        go->gpos.h = FLOOR_HEIGHT;
    }
}

void load_level(struct game_state *ga_st, char *fin)
{
    char *data;
    int fd;
    int width;
    int height;
    struct stat buf;

    fd = open(fin, O_RDONLY);
    if (fd == -1)
        return;
    if (fstat(fd, &buf) < 0)
    {
        close(fd);
        return;
    }
    data = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    for (width = 1; width < buf.st_size && data[width] != '\n'; ++width)
        continue;
    height = buf.st_size / width;
    ga_st->lv_w = width * 16;
    ga_st->lv_h = height * 16;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width - 1; ++j)
        {
            if (data[i * width + j] != '0')
                load_go(ga_st, y * 16, i * 16, data[i * width + j]);
        }
    }

    munmap(data, buf.st_size);
    close(fd);
}
