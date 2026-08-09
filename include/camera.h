
#ifndef CAMERA_H
#define CAMERA_H

typedef struct WindowSettings WindowSettings;

typedef struct {
  float x;
  float y;
  WindowSettings *windowSettings;
} GameCamera;


#endif // !CAMERA_H
