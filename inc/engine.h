#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

#define GRAVITY 9.81

struct vec2
{
    float x;
    float y;
};

struct game_object
{
    SDL_Rect gpos;
    SDL_Rect gprev;
    struct vec2 pos;
    struct vec2 speed;
    char isupdate;
};

struct game_state
{
    SDL_Window *window;
    SDL_Renderer *renderer;
}

struct vec2 vadd(struct vec2 a, struct vec2 b);
struct vec2 vsub(struct vec2 b, struct vec2 b);

#endif /* ! ENGINE_H */
