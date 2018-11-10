#include "graphical_engine.h"
#include <SDL_image.h>

/*
   static void anim(struct game_state *ga_st) // DELETE ME
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
   SDL_Rect dstrect = {10+(i*5),10,50,50};
   SDL_RenderCopy(ga_st->renderer, texture, &srcrect, &dstrect);
   SDL_RenderPresent(ga_st->renderer);
   SDL_Delay(70);
   i++;
   }
   IMG_Quit();
   SDL_DestroyTexture(texture);
   SDL_FreeSurface(image);
   }
   */
static void load_textures(struct game_state *ga_st)
{
    int size = 5;
    struct tabTex *tabTex = malloc(sizeof(struct tabTex) * size);
    for (int i = 0; i < 2; i++)
    {
        char buff[256];
        sprintf(buff, "./resources/Sprites/Block%d.png", i);
        SDL_Surface *img = IMG_Load(buff);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(ga_st->renderer, img);
        tabTex[i].tex = tex;
        tabTex[i].type = DECOR;
        SDL_FreeSurface(img);
    }
    SDL_Surface *img = IMG_Load("./resources/Sprites/Player2.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ga_st->renderer, img);
    tabTex[3].tex = tex;
    tabTex[3].type = DECOR;
    SDL_Surface *image = IMG_Load("./resources/Backgrounds/background.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ga_st->renderer, image);
    tabTex[4].tex = texture;
    tabTex[4].type = DECOR;
    SDL_FreeSurface(img);
    ga_st->tab = tabTex;
    return;
}

void update_graphic(struct game_state *ga_st)
{
    IMG_Init(IMG_INIT_PNG);
    load_textures(ga_st);

    SDL_RenderCopy(ga_st->renderer, ga_st->tab[4].tex, NULL, NULL);
    struct game_object *current = ga_st->l_go_dec;
    for (; current != NULL; current = current->next)
    {
        current->frame = 0;
        current->animation = 0;
        SDL_Rect srcrect = {0.,0.,16,16};
        SDL_Rect dstrect = {current->pos.x, current->pos.y, 16,16};
        SDL_RenderCopy(ga_st->renderer, ga_st->tab[1].tex, &srcrect, &dstrect);
    }

    for (current = ga_st->l_go_ent; current != NULL; current = current->next)
    {
        current->animation = 1;
        SDL_Rect srcrect = {current->frame * 66,66. * current->animation,66,66};
        SDL_Rect dstrect = {current->pos.x, current->pos.y, 66,66};
        SDL_RenderCopy(ga_st->renderer, ga_st->tab[3].tex, &srcrect, &dstrect);
    }

    SDL_RenderPresent(ga_st->renderer);
    SDL_RenderClear(ga_st->renderer);
}

void init_sdl(struct game_state *ga_st)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    ga_st->window = window;
    ga_st->renderer = renderer;
}

void free_sdl(struct game_state *ga_st)
{
    SDL_DestroyWindow(ga_st->window);
    SDL_DestroyRenderer(ga_st->renderer);
    SDL_Quit();
}
