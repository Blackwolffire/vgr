#include <stdlib.h>
#include "game_object.h"

void go_free(struct game_object *list, struct game_object *go)
{
    struct game_object *e = list;

    if (!go)
        return;

    while (e && e->next != go)
        e = e->next;
    if (!e)
        return;
    e->next = go->next;
    free(go);
}

void go_list_free(struct game_object *go)
{
    struct game_object *torm;

    while (go)
    {
        torm = go;
        go = go->next;
        free(torm);
    }
}
