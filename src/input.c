#include <stdio.h>
#include "input.h"
#include "scene.h"

static int nb = 0;

int input_update(struct game_state *ga_st)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return 1;
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                player_jump(&ga_st->player);
            else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                return 2;
            else if (event.key.keysym.scancode == SDL_SCANCODE_L)
            {
                if (!nb)
                    player_shoot(&ga_st->player);
                nb = 1;
            }
        }
        else if (event.type == SDL_KEYUP)
            if (event.key.keysym.scancode == SDL_SCANCODE_L)
                nb = 0;

    }

    const Uint8 *key = SDL_GetKeyboardState(NULL);

    if (key[SDL_SCANCODE_D] || key[SDL_SCANCODE_RIGHT])
        player_run(&ga_st->player, 1);
    else if (key[SDL_SCANCODE_A] || key[SDL_SCANCODE_LEFT])
        player_run(&ga_st->player, -1);
    else if (key[SDL_SCANCODE_LCTRL])
    {
        cheatcodewin(ga_st);
        return 3;
    }
    else
        player_run(&ga_st->player, 0);

    return 0;
}
