#include "graphical_engine.h"

void init_sdl(struct game_state *g_st)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 600, 400, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawColor(renderer, 128, 43, 226, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    g_st->window = window;
    g_st->renderer = renderer;
}
