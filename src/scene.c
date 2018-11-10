#include "graphical_engine.h"
#include "physical_engine.h"

int game_loop(struct game_state *ga_st)
{
    while (1)
    {
        physical_update(ga_st);
        update_graphic(ga_st);
        //ga_st->player.go->frame = (ga_st->player.go->frame + 1) % 7;
        SDL_Delay(30);
    }

    return 0;
}
