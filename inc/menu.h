#ifndef MENU_H
#define MENU_H

#include "graphical_engine.h"

enum selec
{
    PLAY,
    INSTRUCTIONS,
    QUIT,
    COPYRIGHT
};

void menu(struct game_state *ga_st);

#endif /* ! MENU_H */
