#pragma once

#include <stdbool.h>

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
    bool is_bullet_active;
    Entity bullet;

} Player;


typedef struct
{
    Entity entity;
    bool is_dead;
    Entity bullet;
    bool is_bullet_active;

} Enemy;