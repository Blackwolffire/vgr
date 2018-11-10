#include "graphical_engine.h"
#include <SDL_image.h>

static void load_textures(struct game_state *ga_st)
{
    int size = 4;
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
    SDL_Surface *pro = IMG_Load("./resources/Sprites/Projectile.png");
    SDL_Texture *tex_pro = SDL_CreateTextureFromSurface(ga_st->renderer, pro);
    tabTex[3].tex = tex_pro;
    tabTex[3].type = PROJECTILE;
    SDL_Surface *img = IMG_Load("./resources/Sprites/Player2.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ga_st->renderer, img);
    tabTex[size - 2].tex = tex;
    tabTex[size - 2].type = DECOR;
    SDL_Surface *image = IMG_Load("./resources/Backgrounds/background.png");
    SDL_Texture *textur = SDL_CreateTextureFromSurface(ga_st->renderer, image);
    tabTex[size - 1].tex = textur;
    tabTex[size - 1].type = DECOR;
    SDL_FreeSurface(img);
    ga_st->tab = tabTex;
    return;
}

void update_graphic(struct game_state *ga_st)
{
    IMG_Init(IMG_INIT_PNG);
    load_textures(ga_st);

    SDL_RenderCopy(ga_st->renderer, ga_st->tab[3].tex, NULL, NULL);
    struct game_object *cur = ga_st->l_go_dec;
    for (; cur != NULL; cur = cur->next)
    {
        //cur->frame = 0;
        //cur->animation = 0;
        SDL_Rect srcrect = {0.,0.,16,16};
        SDL_Rect dstrect = {cur->pos.x, cur->pos.y, 16,16};
        SDL_RenderCopy(ga_st->renderer, ga_st->tab[1].tex, &srcrect, &dstrect);
    }

    for (cur = ga_st->l_go_ent; cur != NULL; cur = cur->next)
    {
        //cur->animation = 1;
        SDL_Rect srcrect = {cur->frame * 66, cur->animation * 66, 66, 66};
        SDL_Rect dstrect = {cur->pos.x, cur->pos.y, 66,66};
        SDL_RenderCopy(ga_st->renderer, ga_st->tab[2].tex, &srcrect, &dstrect);
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
    IMG_Quit();
    SDL_Quit();
}
