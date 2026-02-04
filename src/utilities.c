#include "entities.h"
#include <stdbool.h>
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

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
    return (getYEntity(bullet) <= (getYEnemy(e) + getHEnemy(e))) && (getYEntity(bullet) + getHEntity(bullet) >= getYEnemy(e)) 
    && (getXEntity(bullet) <= (getXEnemy(e) + getWEnemy(e))) && (getXEntity(bullet) + getWEntity(bullet) >= getXEnemy(e));
}

bool collisionPlayerEnemy(Player *p, Enemy *e){
    return (getYPlayer(p) <= (getYEnemy(e) + getHEnemy(e))) && (getYPlayer(p) + getHPlayer(p) >= getYEnemy(e)) 
    && (getXPlayer(p) <= (getXEnemy(e) + getWEnemy(e))) && (getXPlayer(p) + getWPlayer(p) >= getXEnemy(e));
}

bool collisionEntityPlayer(Player *p, Entity *bullet){
    return (getYEntity(bullet) <= (getYPlayer(p) + getHPlayer(p))) && (getYEntity(bullet) + getHEntity(bullet) >= getYPlayer(p)) 
    && (getXEntity(bullet) <= (getXPlayer(p) + getWPlayer(p))) && (getXEntity(bullet) + getWEntity(bullet) >= getXPlayer(p));
}



void spawnEnemyBullet(Enemy *e){
    e->is_bullet_active = true;
    Entity *bullet = &e->bullet;
    setXEntity(bullet, getXEnemy(e) + getWEnemy(e) / 2 - NORMAL_ENNEMY_BULLET_WIDTH / 2);
    setYEntity(bullet, getYEnemy(e));
    setWEntity(bullet, NORMAL_ENNEMY_BULLET_WIDTH);
    setHEntity(bullet, NORMAL_ENNEMY_BULLET_HEIGHT);
    setVyEntity(bullet, NORMAL_ENNEMY_BULLET_SPEED);
}

void spawnHeart(Game *game, float x, float y){
    size_t new_len = game->hearts_len + 1;
    Entity *tmp = realloc(game->hearts, new_len * sizeof(Entity));
    if (tmp == NULL) {
        return;
    }
    game->hearts = tmp;
    game->hearts_len = (int)new_len;

    Entity heart = {
        .x = x,
        .y = y,
        .vy = HEART_SPEED,
        .is_visible = true,
        .h = 16,
        .w = 16
    };

    game->hearts[game->hearts_len - 1] = heart;
}

void playerCollectHeart(Game *game, Entity *heart){
    Player *p = &game->p;
    if(p->HP < 5){
        p->HP += 1;
    }

    deleteHeart(heart);
}

void deleteHeart(Entity *heart){
    heart->is_visible = false;
}

void hurtPlayer(Player *p, int damage, GamePhase *phase){
    p->HP -= damage;
    if(p->HP <= 0){
        *phase = END_GAME_LOSE;
    }
}

void hurtEnemy(Enemy *e, int damage, Game *game, Entity *bullet){
    bullet->is_visible = false;
    e->HP -= damage;
    if(e->HP <= 0){
        e->is_dead = true;
        if(rand() % HEART_RATE == 0){
        spawnHeart(game, e->entity.x + e->entity.w / 2 - 8, e->entity.y + e->entity.h / 2 - 8);
        }
    }
    
}
