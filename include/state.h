#ifndef APPSTATE_H
#define APPSTATE_H


#include "stage.h"
typedef enum {
  STATE_MENU,
  STATE_GAME,
  STATE_PAUSE,
} GameState;

typedef struct {
  Stage *stages;
  Stage *currentStage;
  double delta;
  const bool *key_states;
} GlobalState;


double get_delta_time();

#endif // !APPSTATE_H
