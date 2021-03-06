#include <err.h>
#include "menu.h"
#include "scene.h"

void perform_selec(enum selec selec, struct game_state *ga_st, int *state)
{
    int tmp;

    ga_st = ga_st;
    if (selec == 1)
    {
        *state = 0;
        SDL_Quit();
    }
    else if (selec == 0)
    {
        load_level(ga_st, "resources/maps/lv0.map");
        tmp = game_loop(ga_st);
        free_level(ga_st);
        if (tmp == 1)
        {
            *state = 0;
            SDL_Quit();
        }
    }
    else
    {
        Mix_PlayChannel(-1, ga_st->win, 0);
        SDL_Delay(40);
    }
}

void manage_update(enum selec selec, struct game_state *ga_st, int enter,
                   int *state)
{
    if (enter == 1)
    {
        perform_selec(selec, ga_st, state);
        return;
    }
    SDL_Rect pos_bg;
    pos_bg.x = 0;
    pos_bg.y = 0;
    pos_bg.w = ga_st->surface->w;
    pos_bg.h = ga_st->surface->h;

    pos_bg = pos_bg;

    SDL_SetRenderDrawColor(ga_st->renderer, 255, 254, 254, 255);
    SDL_Rect pos_selec;
    pos_selec.w = 15;
    pos_selec.h = 15;
    pos_selec.x = 398;

    if (selec == 0)
        pos_selec.y = 250;
    else if (selec == 1)
        pos_selec.y = 370;
    else
        pos_selec.y = 490;

    SDL_RenderCopy(ga_st->renderer, ga_st->texture, NULL, NULL);
    SDL_RenderFillRect(ga_st->renderer, &pos_selec);

    SDL_RenderPresent(ga_st->renderer);
    SDL_RenderClear(ga_st->renderer);
}

void menu(struct game_state *ga_st)
{
    init_sdl(ga_st);
    SDL_Event event;
    enum selec selec = 2;
    int state = 1;
    int enter_selec = 0;

    while (state == 1)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {
            state = 0;
            break;
        }
        const Uint8 *key = SDL_GetKeyboardState(NULL);

        if (key[SDL_SCANCODE_RETURN])
            enter_selec = 1;

        else if (key[SDL_SCANCODE_UP])
        {
            if (selec == 0)
                selec = 2;
            else
                selec -= 1;
        }

        else if (key[SDL_SCANCODE_DOWN])
        {
            if (selec == 2)
                selec = 0;
            else
                selec += 1;
        }
        manage_update(selec, ga_st, enter_selec, &state);
        enter_selec = 0;
    }
    free_sdl(ga_st);
}
