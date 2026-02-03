#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef enum EnemyType{
    NORMAL,
    FAST_MOVING,
    FAST_SHOOTING,
    RESISTENT,
    BOSS
} EnemyType;

typedef struct 
{
    float x, y;
    float vx, vy;
    int w, h;
    bool is_visible;
} Entity;


typedef struct
{
    Entity entity;
    int HP;
    Entity *bullets;
    Uint32 last_shot_ticks;
} Player;


typedef struct
{
    Entity entity;
    bool is_dead;
    Entity bullet;
    bool is_bullet_active;
    int HP;
    int bullet_rate;
    EnemyType type;

} Enemy;