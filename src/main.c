#include "engine.h"
#include "graphical_engine.h"

int main(int argc, char *argv[])
{
    if (!argc || !argv)
        return 1;
    struct game_state g_st;
    init_sdl(&g_st);
    SDL_Delay(1024);
    free_sdl(&g_st);
    return 0;
}
