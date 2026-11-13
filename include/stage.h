#ifndef STAGE_H
#define STAGE_H

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "camera.h"
#include "platform.h"
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
  Platform *platforms;
  int n_entities;
  int n_platforms;
  SDL_FRect transitionScreen;
  GameCamera camera;
};

void stage_render_entities(Stage *stage);
void stage_render_platforms(Stage *stage);
bool stage_add_platform(Stage *stage, Platform *platform);


#endif // !STAGE_H
