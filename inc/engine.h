#ifndef ENGINE_H
#define ENGINE_H

#include "player.h"
#include <SDL_audio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define GRAVITY 1.981

struct tabTex
{
    SDL_Texture *tex;
    enum go_type type;
};

struct game_state
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;

    /*Mix_Music *music;
    Mix_Chunk *win;
    Mix_Chunk *cri;
    Mix_Chunk *def;*/

    int lv_w;
    int lv_h;

    struct player player;
    struct game_object *l_go_ent;
    struct game_object *l_go_dec;
    unsigned int go_tick;
    unsigned int ph_up_tick;
    struct tabTex *tab;
};

struct vec2 vadd(struct vec2 a, struct vec2 b);
struct vec2 vsub(struct vec2 a, struct vec2 b);

void go_ent_list_add(struct game_state *ga_st, struct game_object *go);
void go_dec_list_add(struct game_state *ga_st, struct game_object *go);
void load_level(struct game_state *ga_st, char *fin);
void free_level(struct game_state *ga_st);

#endif /* ! ENGINE_H */
