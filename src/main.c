#include "app.h"
#include "state.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
  App app;
  GlobalState globalState;
  app_init(&app, &globalState);
  app_loop(&app, &globalState);
  app_cleanup(&app, &globalState);

  return 0;
}
