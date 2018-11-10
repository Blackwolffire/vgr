#include <err.h>
#include "menu.h"

void perform_selec(enum selec selec, struct game_state *ga_st)
{
    ga_st = ga_st;
    if (selec == QUIT)
        SDL_Quit();


    else
        SDL_Delay(500);
}

void manage_update(enum selec selec, struct game_state *ga_st, int enter)
{
    if (enter == 1)
    {
        perform_selec(selec, ga_st);
        return;
    }
    SDL_Rect pos_bg;
    pos_bg.x = 0;
    pos_bg.y = 0;
    pos_bg.w = ga_st->surface->w;
    pos_bg.h = ga_st->surface->h;

    /*SDL_SetRenderDrawColor(ga_st->renderer, 0, 43, 226, 0);
      SDL_Rect pos_selec;
      pos_selec.w = 25;
      pos_selec.h = 25;
      pos_selec.x = 700;

      if (selec == PLAY)
      pos_selec.y = 165;
      if (selec == INSTRUCTIONS)
      pos_selec.y = 217;
      if (selec == QUIT)
      pos_selec.y = 277;
      else
      pos_selec.y = 333;

*/
    //SDL_RenderClear(ga_st->renderer);
    //pos_selec=pos_selec;
    //SDL_RenderFillRect(ga_st->renderer, &pos_selec);
    SDL_RenderCopy(ga_st->renderer, ga_st->texture, NULL, &pos_bg);
    SDL_RenderPresent(ga_st->renderer);
}

void init_sdl_tmp(struct game_state *ga_st)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *bg = NULL;
    SDL_Texture *text = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 600, 400, 0);
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
    bg = IMG_Load("resources/background_menu_3.png");
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

    SDL_Rect pos_bg;
    pos_bg.x = 0;
    pos_bg.y = 0;
    pos_bg.w = ga_st->surface->w;
    pos_bg.h = ga_st->surface->h;
    SDL_RenderCopy(ga_st->renderer, ga_st->texture, NULL, &pos_bg);

    SDL_RenderPresent(ga_st->renderer);
    SDL_RenderClear(ga_st->renderer);
}


void menu(struct game_state *ga_st)
{
    init_sdl_tmp(ga_st);
    SDL_Event event;
    enum selec selec = PLAY;
    int state = 1;
    int enter_selec = 0;

    //while (state == 1)
    //{
    // SDL_WaitEvent(&event);
    //manage_update(selec, ga_st, 0);
    perform_selec(PLAY, ga_st);
    //while (SDL_PollEvent(&event))
    //{
    /* if (event.type == SDL_QUIT)
       {
       state = 0;
       break;
       }
       const Uint8 *key = SDL_GetKeyboardState(NULL);

       if (key[SDL_SCANCODE_RETURN])
       enter_selec = 1;

       else if (key[SDL_SCANCODE_UP])
       {
       if (selec == 0)
       selec = COPYRIGHT;
       else
       selec -= 1;
       }

       else if (key[SDL_SCANCODE_DOWN])
       {
       if (selec == 4)
       selec = PLAY;
       else
       selec += 1;
       }
       manage_update(selec, ga_st, enter_selec);
       enter_selec = 0;
    //}
    }*/

    SDL_DestroyTexture(ga_st->texture);
    SDL_FreeSurface(ga_st->surface);

}
