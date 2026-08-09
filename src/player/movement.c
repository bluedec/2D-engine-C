#include "movement.h"
#include "app.h"
#include "constants.h"
#include "player.h"

void handle_direction(int hor, Player *player, double delta_time, WindowSettings ws) {
  if (hor == -1) {
    if (player->hitbox.x > 0) { // if inside the window horizontally
      player->hitbox.x -= PLAYER_SPEED * delta_time;
    }
  } else if (hor == 1) {
    if (player->hitbox.x < ws.w - player->hitbox.w) {
      player->hitbox.x += PLAYER_SPEED * delta_time;
    }
  }

  //if (ver == -1) { 
  //  if (player->hitbox.y > 0) { // if inside the window vertically
  //    player->hitbox.y -= PLAYER_SPEED * delta_time;
  //  }
  //} else if (ver == 1) {
  //  if (player->hitbox.y < ws.h - player->hitbox.h) {
  //    player->hitbox.y += PLAYER_SPEED * delta_time;
  //  }
  //}
}
