#include <err.h>
#include "engine.h"
#include "graphical_engine.h"

int g_size;

void load_textures(struct game_state *ga_st)
{
    g_size = 9;
    struct tabTex *tabTex = malloc(sizeof(struct tabTex) * g_size);
    for (int i = 0; i < g_size - 3; i++)
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
    tabTex[g_size - 3].tex = tex_pro;
    tabTex[g_size - 3].type = PROJECTILE;
    SDL_Surface *img = IMG_Load("./resources/Sprites/Player.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ga_st->renderer, img);
    tabTex[g_size - 2].tex = tex;
    tabTex[g_size - 2].type = DECOR;
    SDL_Surface *image = IMG_Load("./resources/Backgrounds/background.png");
    SDL_Texture *textur = SDL_CreateTextureFromSurface(ga_st->renderer, image);
    tabTex[g_size - 1].tex = textur;
    tabTex[g_size - 1].type = DECOR;


    SDL_FreeSurface(img);
    SDL_FreeSurface(pro);
    SDL_FreeSurface(image);
    ga_st->tab = tabTex;
    return;
}

void update_graphic(struct game_state *ga_st)
{
    SDL_RenderCopy(ga_st->renderer, ga_st->tab[g_size - 1].tex, NULL, NULL);
    struct game_object *cur = ga_st->l_go_dec;
    for (; cur != NULL; cur = cur->next)
    {
        SDL_Rect srcrect = {0.,0.,16,16};
        SDL_Rect dstrect = {cur->pos.x, cur->pos.y, 16,16};
        int i = 2;
        if (cur->type == DECOR_SUP)
            i = 0;
        else if (cur->type == DEATH_BLOCK)
            i = 1;
        else if (cur->type == EXIT)
            i = 5;
        SDL_RenderCopy(ga_st->renderer, ga_st->tab[i].tex, &srcrect, &dstrect);
    }

    for (cur = ga_st->l_go_ent; cur != NULL; cur = cur->next)
    {
        int i = 0;
        int s = 16; //size
        if (cur->type == PLAYER)
        {
            i = g_size - 2;
            s = 67;
        }
        else if (cur->type == PROJECTILE)
            i = g_size - 3;
        else if (cur->type == ENEMY)
        {
            i = 4;
            s = 32;
        }
        SDL_Rect srcrect = {cur->frame * s, cur->animation * s, s, s};
        SDL_Rect dstrect = {cur->pos.x - 23, cur->pos.y - 10,s , s};
        SDL_RenderCopy(ga_st->renderer, ga_st->tab[i].tex, &srcrect, &dstrect);
    }
    SDL_RenderPresent(ga_st->renderer);
    SDL_RenderClear(ga_st->renderer);
}

void init_music(struct game_state *ga_st)
{
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *mus = Mix_LoadMUS("resources/audio/main_theme.mp3");
    Mix_Chunk *cri = Mix_LoadWAV("resources/audio/SF-cri54.mp3");
    Mix_Chunk *def = Mix_LoadWAV("resources/audio/sf_defenestration_01.mp3");
    Mix_Chunk *win = Mix_LoadWAV("resources/audio/SF-yehaw.mp3");
    Mix_PlayMusic(mus, -1);

    ga_st->music = mus;
    ga_st->win = win;
    ga_st->def = def;
    ga_st->cri = cri;
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
    bg = IMG_Load("resources/Backgrounds/forest_name.png");
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
    init_music(ga_st);

    ga_st->window = window;
    ga_st->renderer = renderer;
    ga_st->texture = text;
    ga_st->surface = bg;

}

void free_sdl(struct game_state *ga_st)
{
    for (int i = 0; i < g_size; i++)
        SDL_DestroyTexture(ga_st->tab[i].tex);
    free(ga_st->tab);

    SDL_DestroyTexture(ga_st->texture);
    SDL_FreeSurface(ga_st->surface);
    SDL_DestroyWindow(ga_st->window);
    SDL_DestroyRenderer(ga_st->renderer);
    Mix_FreeMusic(ga_st->music);
    Mix_FreeChunk(ga_st->cri);
    Mix_FreeChunk(ga_st->win);
    Mix_FreeChunk(ga_st->def);
    Mix_CloseAudio();
    IMG_Quit();
}
