
#include "stage.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "player.h"

void stage_render_world_objects(Stage *stage) {
  int i, x, y;
  SDL_Renderer *r = stage->renderer;
  SDL_FRect *entity = stage->entities;
  Coordinates camcords = { stage->camera.x, stage->camera.y };
  int n = stage->n_entities;


  SDL_FRect player_hitbox = stage->player->hitbox;
  Color pcolor = stage->player->color;

  // Render player
  SDL_SetRenderDrawColor(r, pcolor.r, pcolor.g, pcolor.b, pcolor.a);
  SDL_RenderFillRect(r, &(SDL_FRect) {
    .x = player_hitbox.x - camcords.x,
    .y = player_hitbox.y - camcords.y,
    .w = player_hitbox.w,
    .h = player_hitbox.h,
  });

  // Render entities
  for (i = 0; i < n; i++) {
    SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 255);

    SDL_FRect temp = { 
      .x = entity->x - camcords.x,
      .y = entity->y - camcords.y,
      .w = entity->w,
      .h = entity->h
    };
    SDL_RenderFillRect(r, &temp);
    entity++;
  }

}
