#include <err.h>
#include "graphical_engine.h"
#include <SDL_image.h>

void load_textures(struct game_state *ga_st)
{
    int size = 6;
    struct tabTex *tabTex = malloc(sizeof(struct tabTex) * size);
    for (int i = 0; i < 3; i++)
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
    tabTex[size - 3].tex = tex_pro;
    tabTex[size - 3].type = PROJECTILE;
    SDL_Surface *img = IMG_Load("./resources/Sprites/Player.png");
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

    SDL_RenderCopy(ga_st->renderer, ga_st->tab[5].tex, NULL, NULL);
    struct game_object *cur = ga_st->l_go_dec;
    for (; cur != NULL; cur = cur->next)
    {
        //cur->frame = 0;
        //cur->animation = 0;
        SDL_Rect srcrect = {0.,0.,16,16};
        SDL_Rect dstrect = {cur->pos.x, cur->pos.y, 16,16};
        int i = 2;
        if (cur->type == DECOR_SUP)
            i = 0;
        SDL_RenderCopy(ga_st->renderer, ga_st->tab[i].tex, &srcrect, &dstrect);
    }

    for (cur = ga_st->l_go_ent; cur != NULL; cur = cur->next)
    {
        //cur->animation = 1;
        int i = 0;
        if (cur->type == PLAYER)
            i = 4;
        else if (cur->type == PROJECTILE)
            i = 3;
        SDL_Rect srcrect = {cur->frame * 66, cur->animation * 66, 66, 66};
        SDL_Rect dstrect = {cur->pos.x, cur->pos.y, 66,66};
        SDL_RenderCopy(ga_st->renderer, ga_st->tab[i].tex, &srcrect, &dstrect);
    }
    SDL_RenderPresent(ga_st->renderer);
    SDL_RenderClear(ga_st->renderer);
}

void init_sdl(struct game_state *ga_st)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *bg = NULL;
    SDL_Texture *text = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if (!window)
    {
        warnx("pb window");
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        warnx("pb renderer");
        exit(1);
    }
    bg = IMG_Load("resources/background_menu_3_names.png");
    if (!bg)
    {
        warnx("pb image");
        exit(1);
    }
    text = SDL_CreateTextureFromSurface(renderer, bg);
    if (!text)
    {
        printf("%s\n", SDL_GetError());
        warnx("pb text");
        exit(1);
    }

    ga_st->window = window;
    ga_st->renderer = renderer;
    ga_st->texture = text;
    ga_st->surface = bg;

}

void free_sdl(struct game_state *ga_st)
{
    SDL_DestroyTexture(ga_st->texture);
    SDL_FreeSurface(ga_st->surface);
    SDL_DestroyWindow(ga_st->window);
    SDL_DestroyRenderer(ga_st->renderer);
    IMG_Quit();
}
