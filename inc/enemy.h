#ifndef ENEMY_H
#define ENEMY_H

#include "engine.h"

#define ENEMY_WIDTH 32
#define ENEMY_HEIGHT 32
#define ENEMY_LIFE 600
#define ENEMY_SHOOT 3000
#define LASER_POWER 200

void enemy_shoot(struct game_state *ga_st, struct game_object *e);

#endif /* ! ENEMY_H */
