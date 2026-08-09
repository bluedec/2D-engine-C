#ifndef APP_H
#define APP_H
#include "SDL3/SDL_render.h"
#include "state.h"

typedef struct WindowSettings WindowSettings;

struct WindowSettings{
  float w;
  float h;
};

typedef struct App {
  GameState gameState;
  SDL_Renderer *renderer;
  SDL_Window *window;
  WindowSettings windowSettings;
} App;

extern void app_init(App *self, GlobalState *globalState);
extern void app_loop(App *self, GlobalState *globalState);
extern void app_cleanup(App *self, GlobalState *globalState);

#endif // !APP_H
