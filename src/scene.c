#include "graphical_engine.h"
#include "physical_engine.h"

int game_loop(struct game_state *ga_st)
{
    while (1)
    {
        physical_update(ga_st);
        update_graphic(ga_st);
        SDL_Delay(1000);
    }

    return 0;
}
