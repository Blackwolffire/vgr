#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

#define GRAVITY 9.81

struct vec2
{
    float x;
    float y;
};

enum entity
{
    DECOR,
    PLAYER,
    ENNEMY,
    PROJECTILE
};

struct game_object
{
    SDL_Rect gpos;
    SDL_Rect gprev;
    struct vec2 pos;
    struct vec2 speed;
    char isupdate;
    int life;
    enum ENTITY type;

    struct game_object *next;
};

struct game_state
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    //struct player;
    struct game_object *l_go_ent;
    struct game_object *l_go_dec;
    unsigned int go_tick;
}

struct vec2 vadd(struct vec2 a, struct vec2 b);
struct vec2 vsub(struct vec2 a, struct vec2 b);

#endif /* ! ENGINE_H */
