#include <fcntl.h>
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

static void load_go(struct game_state *ga_st, int x, int y, char type)
{
    
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
    ga_st->lv_w = width * 100;
    ga_st->lv_h = height * 100;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width - 1; ++j)
        {

        }
    }

    munmap(data, buf.st_size);
    close(fd);
}
