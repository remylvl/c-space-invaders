#include "entities.h"
#include <stdbool.h>

//GETTERS
//getX
float getXPlayer(Player *p){
    return p->entity.x;
}

float getXEntity(Entity *e){
    return e->x;
}

float getXEnemy(Enemy *e){
    return e->entity.x;
}

//getY
float getYPlayer(Player *p){
    return p->entity.y;
}

float getYEntity(Entity *e){
    return e->y;
}

float getYEnemy(Enemy *e){
    return e->entity.y;
}

//getVx
float getVxPlayer(Player *p){
    return p->entity.vx;
}

float getVxEntity(Entity *e){
    return e->vx;
}

float getVxEnemy(Enemy *e){
    return e->entity.vx;
}

//getVy
float getVyPlayer(Player *p){
    return p->entity.vy;
}

float getVyEntity(Entity *e){
    return e->vy;
}

float getVyEnemy(Enemy *e){
    return e->entity.vy;
}

//getW
int getWPlayer(Player *p){
    return p->entity.w;
}

int getWEntity(Entity *e){
    return e->w;
}

int getWEnemy(Enemy *e){
    return e->entity.w;
}

//getH
int getHPlayer(Player *p){
    return p->entity.h;
}

int getHEntity(Entity *e){
    return e->h;
}

int getHEnemy(Enemy *e){
    return e->entity.h;
}

//SETTERS
//setX
void setXPlayer(Player *p, float x){
    p->entity.x = x;
}

void setXEntity(Entity *e, float x){
    e->x = x;
}

void setXEnemy(Enemy *e, float x){
    e->entity.x = x;
}

//setY
void setYPlayer(Player *p, float y){
    p->entity.y = y;
}

void setYEntity(Entity *e, float y){
    e->y = y;
}

void setYEnemy(Enemy *e, float y){
    e->entity.y = y;
}

//setVx
void setVxPlayer(Player *p, float vx){
    p->entity.vx = vx;
}

void setVxEntity(Entity *e, float vx){
    e->vx = vx;
}

void setVxEnemy(Enemy *e, float vx){
    e->entity.vx = vx;
}

//setVy
void setVyPlayer(Player *p, float vy){
    p->entity.vy = vy;
}

void setVyEntity(Entity *e, float vy){
    e->vy = vy;
}

void setVyEnemy(Enemy *e, float vy){
    e->entity.vy = vy;
}

//setW
void setWPlayer(Player *p, int w){
    p->entity.w = w;
}

void setWEntity(Entity *e, int w){
    e->w = w;
}

void setWEnemy(Enemy *e, int w){
    e->entity.w = w;
}

//setH
void setHPlayer(Player *p, int h){
    p->entity.h = h;
}

void setHEntity(Entity *e, int h){
    e->h = h;
}

void setHEnemy(Enemy *e, int h){
    e->entity.h = h;
}

//Autres

bool collisionBulletEnemy(Enemy *e, Entity *bullet){
    return (getYEntity(bullet) <= (getYEnemy(e) + getHEnemy(e))) && (getYEntity(bullet) >= getYEnemy(e)) 
    && (getXEntity(bullet) <= (getXEnemy(e) + getWEnemy(e))) && (getXEntity(bullet) + getWEntity(bullet) >= getXEnemy(e));
}

bool collisionPlayerEnemy(Player *p, Enemy *e){
    return (getYPlayer(p) <= (getYEnemy(e) + getHEnemy(e))) && (getYPlayer(p) >= getYEnemy(e)) 
    && (getXPlayer(p) <= (getXEnemy(e) + getWEnemy(e))) && (getXPlayer(p) + getWPlayer(p) >= getXEnemy(e));
}
