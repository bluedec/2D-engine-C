#include "player.h"

#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "app.h"
#include "constants.h"
#include "stdio.h"
#include <stdbool.h>

//int vertical_direction_to_move() {
//  int direction = 0;
//  const bool *key_states = SDL_GetKeyboardState(NULL);
//  if (key_states[SDL_SCANCODE_W]) {
//    direction -= 1;
//  };
//
//  if (key_states[SDL_SCANCODE_S]) {
//    direction += 1;
//  }
//  return direction;
//}
//

Direction horizontal_direction_to_move() {
  int direction = 0;
  const bool *key_states = SDL_GetKeyboardState(NULL);
  if (key_states[SDL_SCANCODE_LEFT]) {
    direction -= 1;
  };

  if (key_states[SDL_SCANCODE_RIGHT]) {
    direction += 1;
  }
  return direction;
}

void player_handle_logic(Player *player, Stage *stage, const double delta, GameCamera *gamecam) {
  const bool *key_states = SDL_GetKeyboardState(NULL);
  float x = player->hitbox.x;
  float y = player->hitbox.y;
  float hor_vel = player->hor_velocity;
  float ver_vel = player->ver_velocity;
  Collisions *pc = &player->collisions;
  int horizontal_direction = horizontal_direction_to_move();
  bool is_pressing_jump = key_states[SDL_SCANCODE_Z];
  bool can_go_up = !pc->is_colliding_top;
  bool on_floor = pc->is_colliding_bottom;
  bool no_horizontal_input = !key_states[SDL_SCANCODE_LEFT] && !key_states[SDL_SCANCODE_RIGHT];

  Coordinates cam = { gamecam->x, gamecam->y };

  player->hab_times.jump += delta;
  
  player_handle_direction(&hor_vel, horizontal_direction);

  if (!is_pressing_jump) {
    if (player->collisions.is_colliding_bottom) {
      player->jumps_used = 0;
    }
    player->is_jumping = false;
    player->color.r = 255;
    player->color.b = 0;
  } else {
    if (player->is_jumping) {
      if (player->hab_times.jump < 0.5) {
        ver_vel -= (JUMP_STRENGTH * delta) * JUMP_HOLD_MULTIPLIER;
        player->color.r = 0;
        player->color.b = 255;
      } else {
        player->color.r = 255;
        player->color.b = 0;
      }
    } else {
      if (player->jumps_used < player->jumps_max) {
        player->is_jumping = true;
        ver_vel = -JUMP_STRENGTH;
        player->jumps_used += 1;
        player->hab_times.jump = 0;
      }
    }
  } 

  // APPLY GRAVITY
  if (!on_floor) {
    ver_vel += GRAVITY_STRENGTH * delta;
  } 

  if (no_horizontal_input) {
    hor_vel = 0;
  }

  // MOVEMENT CLEANUP
  bool should_move_left = (!pc->is_colliding_left && hor_vel < 0);
  bool should_move_right = (!pc->is_colliding_right && hor_vel > 0);
  bool should_move_up = (!pc->is_colliding_top && ver_vel < 0);
  bool should_move_down = (!pc->is_colliding_bottom && ver_vel > 0);

  if (should_move_left) {
    player->hitbox.x += hor_vel * delta;
    if (x - gamecam->x < CAMERA_DISTANCE_TO_DRAG) {
      gamecam->x += hor_vel * delta;
    }
  }
  if (should_move_right) {
    player->hitbox.x += hor_vel * delta;
    if ((gamecam->x + gamecam->windowSettings->w) - (x + player->hitbox.w) < CAMERA_DISTANCE_TO_DRAG) {
      gamecam->x += hor_vel * delta;
    }
  }

  //if (should_move_right || should_move_left) {
  //  player->hitbox.x += hor_vel * delta;
  //  if (x - gamecam->x < 300 && hor_vel < 0) {
  //    gamecam->x += hor_vel * delta;
  //  }
  //  if (x - gamecam->x > 800 && hor_vel > 0) {
  //    gamecam->x += hor_vel * delta;
  //  }
  //} 
  if (should_move_up || should_move_down) {
    player->hitbox.y += ver_vel * delta;
    gamecam->y += ver_vel * delta;
  } 
  player->hor_velocity = hor_vel;
  player->ver_velocity = ver_vel;

  pc->is_colliding_top    = false;
  pc->is_colliding_left   = false;
  pc->is_colliding_right  = false;
  pc->is_colliding_bottom = false;
}

void player_handle_direction(float *hor_vel, Direction dir) {
  // HORIZONTAL MOVEMENT
  switch (dir) {
    case RIGHT: 
      *hor_vel = PLAYER_SPEED;
      break;
    case LEFT: 
      *hor_vel = -PLAYER_SPEED;
      break;
    default: break;
  }
}

Coordinates player_get_coords(const Player *player, const Coordinates camcords) {
  return (Coordinates) {
    .x = player->hitbox.x + camcords.x,
    .y = player->hitbox.y + camcords.y,
  };
}


void player_handle_collisions(Player *player, SDL_FRect *objects, int n_objects, const Coordinates camcords) {
  int i;
  float h_v, v_v, x, y;
  Collisions *player_collissions = &player->collisions;

  h_v = player->hor_velocity;
  v_v = player->ver_velocity;
  y = player->hitbox.y;
  x = player->hitbox.x;

  for (i = 0; i < n_objects; i++) {
    SDL_FRect intersection;
    SDL_FRect obj = objects[i];

    bool intersects = SDL_GetRectIntersectionFloat(&player->hitbox, &obj, &intersection);
    CollisionDirection coll_dir = COLL_BOTTOM;

    if (intersects) {
      if ((y + player->hitbox.h) < intersection.y + 1) {
        coll_dir = COLL_BOTTOM; // The bottom has prio.
      } else if ((x + player->hitbox.w) <= intersection.x + 1) {
        coll_dir = COLL_RIGHT;
      } else if (x > (obj.x + obj.w) - 1) {
        coll_dir = COLL_LEFT;
      } else if (y > (intersection.y) - 1) {
        coll_dir = COLL_TOP;
      }
      // We can only collide from one side with each object
      switch (coll_dir) {
        case COLL_BOTTOM:
          if (!player_collissions->is_colliding_bottom) {
            if (v_v >= 0) {
              player_collissions->is_colliding_bottom = true;
              v_v  = 0;
            } 
          } 
          break;
        case COLL_TOP:
          if (!player_collissions->is_colliding_top) {
            player_collissions->is_colliding_top = true;
            if (v_v < 0.0) v_v = -v_v;
          } 
          break;
        case COLL_LEFT: 
          if (!player_collissions->is_colliding_left) {
            player_collissions->is_colliding_left = true;
            if (h_v < 0) h_v = 0;
          }
          break;
        case COLL_RIGHT:
          if (!player_collissions->is_colliding_right) {
            player_collissions->is_colliding_right = true;
            if (h_v > 0) h_v = 0;
            break;
          }
        default: break;
      }
    }
  }
  player->hor_velocity = h_v;
  player->ver_velocity = v_v;
}
