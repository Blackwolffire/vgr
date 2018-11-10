#include "graphical_engine.h"
#include "scene.h"
#include "menu.h"

int main(void)
{
    struct game_state ga_st;
    load_level(&ga_st, "resources/maps/lv0.map");
    init_sdl(&ga_st);
    menu(&ga_st);
    SDL_Delay(2000);
    free_sdl(&ga_st);
    free_level(&ga_st);
    return 0;
}
