#ifndef STAGE_H
#define STAGE_H

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "camera.h"
#include "player.h"
#include <stdbool.h>

typedef struct Stage Stage;

typedef enum StageId {
  GREEN_FOREST = 1,
  BLUE_FOREST = 2,
} StageId;

struct Stage {
  StageId id;
  const char *name;
  Player *player;
  SDL_Renderer* renderer;
  SDL_FRect *entities;
  int n_entities;
  SDL_FRect transitionScreen;
  GameCamera camera;
};

void stage_render_world_objects(Stage *stage);


#endif // !STAGE_H
