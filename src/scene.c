#include "graphical_engine.h"
#include "input.h"
#include "physical_engine.h"
#include <SDL_ttf.h>

void winScreen(struct game_state *ga_st)
{
    //SDL_SetRenderDrawColor(ga_st->renderer,0,0,0,255);
    SDL_RenderClear(ga_st->renderer);
    SDL_Surface *surf = IMG_Load("./resources/Backgrounds/win.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ga_st->renderer, surf);
    SDL_RenderCopy(ga_st->renderer, tex, NULL, NULL);
    SDL_RenderPresent(ga_st->renderer);
    Mix_PlayChannel(-1, ga_st->win, 0);
    SDL_Delay(2000);
}

void failScreen(struct game_state *ga_st)
{
    SDL_RenderClear(ga_st->renderer);
    SDL_Surface *surf = IMG_Load("./resources/Backgrounds/fail.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ga_st->renderer, surf);
    SDL_RenderCopy(ga_st->renderer, tex, NULL, NULL);
    SDL_RenderPresent(ga_st->renderer);
    Mix_PlayChannel(-1, ga_st->def, 0);
    SDL_Delay(400);
}


int game_loop(struct game_state *ga_st)
{
    unsigned int before = SDL_GetTicks();
    unsigned int after;
    int lvl = 0;
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
        {
            failScreen(ga_st);
            return 0;
        }
        if (ga_st->player.won)
        {
            if (lvl == 0)
            {
                load_level(ga_st, "./resources/maps/lv1.map");
                lvl++;
            }
            else if (lvl == 1)
            {
                winScreen(ga_st);
                return 3;
            }
        }
        SDL_Delay(1);
    }

    return 0;
}
