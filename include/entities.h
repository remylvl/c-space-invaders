#include <stdbool.h>

#ifndef ENTITY_H
#define ENTITY_H

typedef struct
{
    float x, y;
    float vx, vy;
    int w, h;
} Entity;

#endif

#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    Entity entity;

} Player;

#endif

#ifndef ENNEMY_H
#define ENNEMY_H

typedef struct
{
    Entity entity;
    bool is_dead;

} Enemy;

#endif