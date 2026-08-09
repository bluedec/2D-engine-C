#include "app.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "constants.h"
#include "player.h"
#include "stage.h"
#include "stages.h"
#include "state.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void app_init(App *app, GlobalState *globalState) {
  app->gameState = STATE_GAME;
  //app->gameState = STATE_MENU;
  SDL_SetRenderDrawBlendMode(app->renderer ,SDL_BLENDMODE_BLEND);

  if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_InitSubSystem Failed: %s\n", SDL_GetError());
  }
  app->windowSettings.w = SCREEN_WIDTH;
  app->windowSettings.h = SCREEN_HEIGHT;
  SDL_Window *window = SDL_CreateWindow("GameTest", app->windowSettings.w, app->windowSettings.h, 0);

  globalState->stages = malloc(sizeof(Stage) * 2);
  globalState->stages[0] = (Stage) {
    .id = GREEN_FOREST,
    .name = STAGE_1_NAME,
  };
  globalState->stages[1] = (Stage) {
    .id = BLUE_FOREST,
    .name = STAGE_2_NAME,
  };
  globalState->currentStage = &globalState->stages[0];

  if (!window) {
    SDL_Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
  } else {
    app->window = window;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("SDL_CreateRenderer failed: %s\n", SDL_GetError());
  } else {
    app->renderer = renderer;
  }
}


void app_loop(App *app, GlobalState *globalState) {
  bool running = true;
  bool fading = false;
  float i = 0;
  Player player = {
    .name = "Juli",
    .hor_velocity = 0,
    .ver_velocity = 0,
    .damage = 10,
    .hab_times = (HabilitiesTimestamps) { clock() },
    .jumps_max = 200,
    .jumps_used = 0,
    .hitbox = (SDL_FRect) { 
      (float) app->windowSettings.w / 2,
      (float) app->windowSettings.h / 2,
      20,
      20
    },
    .collisions = (Collisions) { false, false, false, false },
    .color = (Color) { 255, 0, 0, 255},
    .is_jumping = false,
  };

  globalState->currentStage->camera = (GameCamera) { 
    .x = 0,
    .y = 0,
  };

  SDL_Renderer *r = app->renderer;
  SDL_Window *w = app->window;

  SDL_FRect *entities = malloc(sizeof(*entities) * 5);
  if (entities == NULL) {
    SDL_Log("Failed to allocate entities");
  }
  Stage currentStage = { 
    .id = 1,
    .name = STAGE_1_NAME,
    .player = &player,
    .renderer = r,
    .entities = entities,
    .n_entities = 2,
    .transitionScreen = 0.0,
    .camera = { 0, 0, &app->windowSettings },
    
  };

  globalState->currentStage = &currentStage;

  struct timespec current_time, last_time;
  timespec_get(&last_time, TIME_UTC);

  while (running) {
    globalState->key_states = SDL_GetKeyboardState(NULL);
    SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(r);
    timespec_get(&current_time, TIME_UTC);
    globalState->delta = (current_time.tv_sec - last_time.tv_sec) + (current_time.tv_nsec - last_time.tv_nsec) / 1e9;
    last_time = current_time;

    // IMPLEMENT 
    // listen_for_events()
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
          running = false;
        }
        if (event.key.key == SDLK_R) {
          globalState->currentStage->camera.x = 0;
          globalState->currentStage->camera.y = 0;
          player.hitbox.x = (float) app->windowSettings.w / 2;
          player.hitbox.y = (float) app->windowSettings.h / 2;
          player.ver_velocity = 0;
          player.jumps_used = 0;
        }
      }
    }
    switch (app->gameState) {
      case STATE_MENU:
        // Fade to black
        //if (fading) {
        //  i = i + (100.0 * delta_time);
        //  printf("%f\n", i);
        //  SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
        //  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, i);
        //  SDL_RenderFillRect(r, &app->transitionScreen);
        //  if (i > 255) {
        //    fading = false;
        //  }
        //}
        break;
      case STATE_GAME:
        switch (globalState->currentStage->id) {
          case GREEN_FOREST: 
            greenForest(globalState);
            break;
          case BLUE_FOREST:
            blueForest(globalState);
            break;
        }
        break;
      case STATE_PAUSE:
        SDL_Log("Paused.");
        break;
    }
    SDL_RenderPresent(r);
  }
}

void app_cleanup(App *app, GlobalState *globalState) {
  free(globalState->currentStage->entities);
  free(globalState->stages);
  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  SDL_Quit();
}


double get_delta_time() {
  return 0.0;
}

