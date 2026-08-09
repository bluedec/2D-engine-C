#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "player.h"
#include "state.h"
#include <time.h>

void greenForest(GlobalState *globalState) {
  Stage *stage = globalState->currentStage;
  Player *player = stage->player;
  SDL_Renderer *r = stage->renderer;
  Collisions *pc = &player->collisions;
  GameCamera *camera = &stage->camera;
  Coordinates camcords = { camera->x, camera->y };
  SDL_FRect *entities = stage->entities;
  SDL_FRect floor = (SDL_FRect) { .x = 30, .y = 600, .w = 1200, .h = 200 };
  entities[0] = floor;
  SDL_FRect box = { .x = 100, .y = 500, .w = 150, .h = 50 };
  entities[1] = box; 
  SDL_FRect secondBox = { .x = 300, .y = 400, .w = 150, .h = 30 };
  entities[2] = secondBox; 
  SDL_FRect thirdBox = { .x = 700, .y = 300, .w = 150, .h = 30 };
  entities[3] = thirdBox;
  SDL_FRect fourthBox = { .x = 1000, .y = 200, .w = 150, .h = 30 };
  entities[4] = fourthBox;
  stage->n_entities = 5;

  SDL_SetRenderDrawColor(r, 0x22, 0x99, 0xff, 255);
  SDL_RenderClear(r);

  // Time
  const double delta = globalState->delta;
  clock_t current_time = clock();
  double elapsed_seconds = (double)(current_time - player->hab_times.jump) / CLOCKS_PER_SEC;

  player_handle_collisions(player, stage->entities, stage->n_entities, (Coordinates) { camera->x, camera->y });
  player_handle_logic(player, stage, delta, camera);

  stage_render_world_objects(stage);
}
