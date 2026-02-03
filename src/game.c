#include "game.h"
#include "utilities.h"
#include "render.h"
#include "entities.h"
#include <stdio.h>
#include <stdlib.h>


void update(Game *game, float dt)
{
    Player *p = &game->p;
    bool *bullet_active = &p->is_bullet_active;
    Entity *bullet = &p->bullet;
    Enemy *enemies = game->enemies;
    GamePhase *phase = &game->gamephase;
    int lines = game->lines;
    int columns = game->columns;



    //Update Player
    setXPlayer(p, getXPlayer(p) + getVxPlayer(p) * dt);
    //p->x += 
    if (getXPlayer(p) < 0)
        setXPlayer(p, 0);
    if (getXPlayer(p) + getWPlayer(p) > SCREEN_WIDTH)
        setXPlayer(p, SCREEN_WIDTH - getWPlayer(p));
        
    //Update Bullets
    if (*bullet_active)
    {
        setYEntity(bullet, getYEntity(bullet) + getVyEntity(bullet) * dt);

        if (getYEntity(bullet) + getHEntity(bullet) < 0)
            *bullet_active = false;
    }

    //Update Enemies
    int counter = 0;
    for(int i = 0; i < (columns * lines); i++){
        Enemy *e = &enemies[i];
        
        if(!e->is_dead){
            counter = 1;
            setYEnemy(e, getYEnemy(e) + getVyEnemy(e) * dt);
            if (*bullet_active){
        if(collisionBulletEnemy(e, bullet)){
            e->is_dead = true;
            *bullet_active = false;
            }
        if(!e->is_bullet_active){
            if(rand() % (100 * columns * lines) == 0){
                spawnEnemyBullet(e);
            }
        }
            }
        }

        if (getYEnemy(e) > SCREEN_HEIGHT - getHEnemy(e) || collisionPlayerEnemy(p, e)){
            *phase = END_GAME_LOSE;
            return;
                }
        //Ennemy bullet
        if (e->is_bullet_active){
            setYEntity(&e->bullet, getYEntity(&e->bullet) + getVyEntity(&e->bullet) * dt);
            if(collisionBulletPlayer(p, &e->bullet)){
                e->is_bullet_active = false;
                hurtPlayer(p, 1, phase);
            }

        if (getYEntity(&e->bullet) + getHEntity(&e->bullet) > SCREEN_HEIGHT)
            e->is_bullet_active = false;
        }

    
    }
    if(counter == 0){
        *phase = END_GAME_WIN;
        return;
    }
}


