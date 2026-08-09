
#ifndef MENU_H
#define MENU_H

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
typedef struct {
  int selected_index;

} MenuState;

void menuInit(MenuState *state);
void menuHandle(MenuState *state, const SDL_Event event);
void menuRender(MenuState *state, SDL_Renderer *renderer);

#endif


