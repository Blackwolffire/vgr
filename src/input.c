#include "input.h"

int input_update(struct game_state *ga_st)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return 1;
        if (event.type == SDL_KEYDOWN)
    }
}
