#pragma once

#include <stdbool.h>
#include "entities.h"
#include "utilities.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 30
#define PLAYER_SPEED 500.0f

#define NORMAL_ENNEMY_WIDTH 50
#define NORMAL_ENNEMY_HEIGHT 20
#define NORMAL_ENNEMY_SPEED 30.0f

#define NORMAL_ENNEMY_BULLET_WIDTH 10
#define NORMAL_ENNEMY_BULLET_HEIGHT 20
#define NORMAL_ENNEMY_BULLET_SPEED 200.0f

#define BULLET_WIDTH 10
#define BULLET_HEIGHT 20
#define BULLET_SPEED 600.0f

#define HEART_SPEED 100.0f


void update(Game *game, float dt);


