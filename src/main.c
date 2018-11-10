#include "engine.h"
#include "graphical_engine.h"

int main(int argc, char *argv[])
{
    if (!argc || !argv)
        return 1;
    struct game_state ga_st;
    init_sdl(&ga_st);
    SDL_Delay(1024);
    free_sdl(&ga_st);
    return 0;
}
