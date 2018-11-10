#include "graphical_engine.h"

void print_background_menu(struct game_state *ga_st)
{
    if (ga_st == NULL)
    {
        warnx("Window not created");
        return;
    }
    SDL_Surface *bg = IMG_Load("ressources/background_menu_3.png", NULL);

    struct vec2 pos_bg;
    pos_bg.x = 0;
    pos_bg.y = 0;

    SDL_BlitSurface(bg, NULL, ga_st->window, &pos_bg);
    SDL_Flip(ga_st->window);
}
