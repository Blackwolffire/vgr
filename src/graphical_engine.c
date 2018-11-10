#include "graphical_engine.h"

static void print(struct game_state *ga_st)
{
    SDL_Surface *pSprite = SDL_LoadBMP("./ressources/OrOS9.bmp");

    SDL_SetRenderDrawColor(ga_st->renderer, 128, 43, 226, 255);
    SDL_RenderClear(ga_st->renderer);
    SDL_RenderPresent(ga_st->renderer);

    if ( pSprite )
    {
        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(ga_st->renderer,pSprite);
        if ( pTexture )
        {
            SDL_Rect dest = { 640/2 - pSprite->w/2,480/2 - pSprite->h/2, pSprite->w, pSprite->h};
            SDL_RenderCopy(ga_st->renderer,pTexture,NULL,&dest);
            
            SDL_RenderPresent(ga_st->renderer);
            SDL_Delay(2048);
            
            SDL_DestroyTexture(pTexture);
        }
        else
        {
            fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
        }

        SDL_FreeSurface(pSprite);
    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }
    SDL_RenderClear(ga_st->renderer);
    SDL_RenderPresent(ga_st->renderer);

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

    print(ga_st);
}

void free_sdl(struct game_state *ga_st)
{
    SDL_DestroyWindow(ga_st->window);
    SDL_DestroyRenderer(ga_st->renderer);
    SDL_Quit();
}
