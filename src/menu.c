#include <err.h>
#include "menu.h"

void print_background_menu(struct game_state *ga_st)
{

    SDL_RenderCopy(ga_st->renderer, text, NULL, &pos_bg);
    SDL_RenderPresent(ga_st->renderer);
    //SDL_Delay(1000);
    //SDL_DestroyTexture(text);

    /*SDL_RenderClear(ga_st->renderer);
      SDL_RenderPresent(ga_st->renderer);*/
}

void perform_selec(enum selec selec, struct game_state *ga_st)
{
    SDL_Quit();
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
    pos_bg.w = ga_st->suface->w;
    pos_bg.h = ga_st->surface->h;

    SDL_SetRenderDrawColor(renderer, 128, 43, 226, 255);
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

    SDL_RenderFillRect(renderer, &pos_selec);
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

    window = S
        DL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, 600, 400, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bg = IMG_Load("ressources/background_menu_3_names.png");
    text = SDL_CreateTextureFromSurface(ga_st->renderer, bg);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    ga_st->window = window;
    ga_st->renderer = renderer;
    ga_st->texture = text;
    ga_st->suface = bg;
}


void menu(struct game_state *ga_st)
{
    init_sdl_tmp(ga_st);
    SDL_Event event;
    enum selec selec = PLAY;
    int state = 1;
    int enter_selec = 0;

    while (state == 1)
    {
        SDL_WaitEvent(&event);
        //manage_update(selec, ga_st, 1);
        // while (SDL_PollEvent(&event))
        // {
        if (event.type == SDL_QUIT)
            state = 0;
        const Uint8 *key = SDL_GetKeyboardState(NULL);

        if (key[SDL_SCANCODE_ENTER])
            enter_selec = 1;

        else if (key[SDLK_SCANCODE_UP])
        {
            if (selec == 0)
                selec = COPYRIGHT;
            else
                selec -= 1;
        }

        else if (key[SDLK_SCANCODE_DOWN])
        {
            if (selec == 4)
                selec = PLAY;
            else
                selec += 1;
        }
        manage_update(selec, ga_st, enter_selec);
        enter_selec = 0;
        // }
    }

    SDL_DestroyTexture(ga_st->text);
    SDL_FreeSurface(bg);

}
