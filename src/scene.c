#include "graphical_engine.h"
#include "input.h"
#include "physical_engine.h"

int game_loop(struct game_state *ga_st)
{
    unsigned int before = SDL_GetTicks();
    unsigned int after;
    int tmp;

    load_textures(ga_st);
    while (1)
    {
        tmp = input_update(ga_st);
        if (tmp)
            return tmp;
        physical_update(ga_st);
        if (before + 10 <= (after = SDL_GetTicks()))
        {
            update_graphic(ga_st);
            before = after;
        }
        if (!ga_st->player.alive)
            return 0;
        if (ga_st->player.won)
            return 3;
        SDL_Delay(1);
    }

    return 0;
}
