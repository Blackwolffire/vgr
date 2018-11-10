#include "graphical_engine.h"
#include <SDL_image.h>

void anim(struct game_state *ga_st)
{
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *image = IMG_Load("./ressources/Sprites/Animation.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ga_st->renderer, image);

    SDL_SetRenderDrawColor(ga_st->renderer, 128, 43, 226, 255);
    int i = 0;
    while(1)
    {
        SDL_RenderClear(ga_st->renderer);
        SDL_Rect srcrect = {(i%8)*50, 0,50,50};
        SDL_Rect dstrect = {10,10,50,50};
        SDL_RenderCopy(ga_st->renderer, texture, &srcrect, &dstrect);
        SDL_RenderPresent(ga_st->renderer);
        SDL_Delay(70);
        i++;
    }
    IMG_Quit();
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}

void init_sdl(struct game_state *ga_st)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 600, 400, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    ga_st->window = window;
    ga_st->renderer = renderer;

    anim(ga_st);
}

void free_sdl(struct game_state *ga_st)
{
    SDL_DestroyWindow(ga_st->window);
    SDL_DestroyRenderer(ga_st->renderer);
    SDL_Quit();
}
