#include "graphical_engine.h"

void init_sdl(game_state *g_st)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 600, 400, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    g_st->window = window;
    g_st->rendere = renderer;
}
