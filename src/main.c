#include "engine.h"
#include "graphical_engine.h"

int main(void)
{
    struct game_state ga_st;
    load_level(&ga_st, "resources/maps/lvl0.map");
    init_sdl(&ga_st);
    SDL_Delay(2000);
    free_sdl(&ga_st);
    free_level(&ga_st);
    return 0;
}
