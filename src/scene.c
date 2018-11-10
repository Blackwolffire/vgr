#include "graphical_engine.h"
#include "input.h"
#include "physical_engine.h"

int game_loop(struct game_state *ga_st)
{
    unsigned int before = SDL_GetTicks();
    unsigned int after;

    while (1)
    {
        /*if (input_update(ga_st))
            return 1;
        */
        physical_update(ga_st);
        if (before + 5 <= (after = SDL_GetTicks()))
        {
            update_graphic(ga_st);
            ga_st->player.go->frame = (ga_st->player.go->frame + 1) % 7;
            before = after;
        }
    }

    return 0;
}
