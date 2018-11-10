#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "player.h"
#include <SDL_image.h>

#define GRAVITY 9.81

struct game_state
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;

    struct player player;
    struct game_object *l_go_ent;
    struct game_object *l_go_dec;
    unsigned int go_tick;
    unsigned int ph_up_tick;
};

struct vec2 vadd(struct vec2 a, struct vec2 b);
struct vec2 vsub(struct vec2 a, struct vec2 b);

#endif /* ! ENGINE_H */
