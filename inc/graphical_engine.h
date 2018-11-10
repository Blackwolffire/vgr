#ifndef GRAPHICAL_ENGINE_H
#define GRAPHICAL_ENGINE_H

#include "engine.h"

void update_graphic(struct game_state *ga_st);
void init_sdl(struct game_state *ga_st);
void free_sdl(struct game_state *ga_st);

#endif /* ! GRAPHICAL_ENGINE_H */
