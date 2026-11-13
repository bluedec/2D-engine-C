#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "platform.h"
#include "player.h"
#include "stage.h"
#include "state.h"
#include <time.h>

void greenForest(GlobalState *globalState) {
  int stageId = globalState->currentStage;
  Stage *stage = &globalState->stages[stageId];
  Player *player = stage->player;
  SDL_Renderer *r = stage->renderer;
  Collisions *pc = &player->collisions;
  GameCamera *camera = &stage->camera;
  Coordinates camcords = { camera->x, camera->y };
  SDL_FRect *entities = stage->entities;
  SDL_FRect floor = (SDL_FRect) { .x = 30, .y = 600, .w = 1800, .h = 200 };
  entities[0] = floor;
  SDL_FRect box = { .x = 100, .y = 467, .w = 50, .h = 30 };
  entities[1] = box; 
  SDL_FRect secondBox = { .x = 320, .y = 390, .w = 150, .h = 30 };
  entities[2] = secondBox; 
  SDL_FRect thirdBox = { .x = 700, .y = 300, .w = 150, .h = 30 };
  entities[3] = thirdBox;
  SDL_FRect fourthBox = { .x = 1000, .y = 200, .w = 150, .h = 30 };
  entities[4] = fourthBox;
  SDL_FRect fifthBox = { .x = 1350, .y = 100, .w = 150, .h = 30 };
  entities[5] = fifthBox;
  SDL_FRect s = { .x = 1850, .y = 200, .w = 150, .h = 30 };
  entities[6] = s;
  stage->n_entities = 7;

  if (stage->n_platforms == 0) {
    Platform moving = { { .x = 1850, .y = 200, .w = 150, .h = 30 }, DYNAMIC, 0, 0 };
    stage_add_platform(stage, &moving);
  }

  SDL_SetRenderDrawColor(r, 0x22, 0x99, 0xff, 255);
  SDL_RenderClear(r);

  // Time
  const double delta = globalState->delta;
  clock_t current_time = clock();
  double elapsed_seconds = (double)(current_time - player->hab_times.jump) / CLOCKS_PER_SEC;

  player_handle_collisions(player, stage->entities, stage->n_entities, camcords);
  player_handle_logic(player, stage, delta, camera);

  stage_render_entities(stage);
  stage_render_platforms(stage);
}
