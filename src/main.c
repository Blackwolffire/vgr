#include "graphical_engine.h"
#include "scene.h"
#include "menu.h"

int main(void)
{
    struct game_state ga_st;
    load_level(&ga_st, "resources/maps/lv0.map");
    menu(&ga_st);
    free_sdl(&ga_st);
    free_level(&ga_st);
    return 0;
}
