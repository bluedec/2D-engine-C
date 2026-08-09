#ifndef PLAYER_H
#define PLAYER_H

#include "SDL3/SDL_rect.h"
#include "camera.h"
#include "constants.h"
#include <stdbool.h>

typedef struct Player Player;

typedef struct {
  float x;
  float y;
} Coordinates;

typedef struct {
  bool is_colliding_bottom, is_colliding_left,is_colliding_top, is_colliding_right;
} Collisions;

typedef enum {
  COLL_TOP,
  COLL_LEFT,
  COLL_RIGHT,
  COLL_BOTTOM,
} CollisionDirection;

typedef struct {
  float jump;
} HabilitiesTimestamps;

typedef enum {
  LEFT = -1,
  NONE = 0, 
  RIGHT = 1,
} Direction;

struct Player {
  char name[100];
  float hor_velocity;
  float ver_velocity;
  int damage;
  SDL_FRect hitbox;
  Collisions collisions;
  int jumps_max;
  int jumps_used;
  bool is_jumping;
  HabilitiesTimestamps hab_times;
  Color color;
};

int horizontal_direction_to_move();
//int vertical_direction_to_move();

typedef struct Stage Stage;
void player_handle_logic(Player *player, Stage *stage, const double delta, GameCamera *gamecam);

void player_handle_collisions(Player *player, SDL_FRect *objects, int n_objects, const Coordinates camcords);
Coordinates player_get_position(const Player *player, const Coordinates camcords);
void player_handle_direction(float *hor_vel, Direction dir);

#endif // !PLAYER_H
