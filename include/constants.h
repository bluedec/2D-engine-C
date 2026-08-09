#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

// Camera
extern const int CAMERA_DISTANCE_TO_DRAG;

// Screen
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

// Player
extern const float PLAYER_SPEED;
extern const float GRAVITY_STRENGTH;
extern const float JUMP_STRENGTH;
extern const float JUMP_HOLD_MULTIPLIER;

// Ambient constants
extern const float FRICTION_STRENGTH;

// Stage Names
extern const char* STAGE_1_NAME;
extern const char* STAGE_2_NAME;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} Color;

#endif // !CONSTANTS_H
