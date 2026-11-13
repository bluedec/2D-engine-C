#ifndef PLATFORM_H
#define PLATFORM_H

#include "SDL3/SDL_rect.h"

typedef enum PlatformType {
  STATIC,
  DYNAMIC,
} PlatformType;

typedef struct Platform {
  SDL_FRect hitbox;
  PlatformType type;
  float hor_vel;
  float ver_vel;
} Platform;

#endif // !PLATFORM_H
