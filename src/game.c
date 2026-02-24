#include "utilities.h"
#include "render.h"
#include "entities.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "game.h"


void update(Game *game, float dt)
{
    Player *p = &game->p;
    Enemy *enemies = game->enemies;
    GamePhase *phase = &game->gamephase;
    int lines = game->lines;
    int columns = game->columns;



    //Update Player
    setXPlayer(p, getXPlayer(p) + getVxPlayer(p) * dt);
    if (getXPlayer(p) < 0)
        setXPlayer(p, 0);
    if (getXPlayer(p) + getWPlayer(p) > SCREEN_WIDTH)
        setXPlayer(p, SCREEN_WIDTH - getWPlayer(p));
        
    //Update Bullets
    for(int i = 0; i < MAX_BULLETS; i++)
    {
        Entity *bullet = &p->bullets[i];
        if(bullet->is_visible){
            bullet->y += bullet->vy * dt;

        if (bullet->y + bullet->h < 0)
            bullet->is_visible = false;
    }}

    //Update Upgrades
    for(int i = 0; i < game->hearts_len; i++){
        if(!game->hearts[i].is_visible) continue;

        game->hearts[i].y += game->hearts[i].vy * dt;
        if(collisionEntityPlayer(p, &game->hearts[i])){
            playerCollectHeart(game, &game->hearts[i]);
        }

        if (game->hearts[i].y + game->hearts[i].h > SCREEN_HEIGHT)
        deleteHeart(&game->hearts[i]);
    }

    //Update Enemies
    int counter = 0;
    for(int i = 0; i < (columns * lines); i++){
        Enemy *e = &enemies[i];
        
        if(!e->is_dead){
            counter = 1;
            setYEnemy(e, getYEnemy(e) + getVyEnemy(e) * dt);

            if(game->boost_enemies){
                e->entity.vy *= NORMAL_ENEMY_BOOST_FACTOR;
            }

            if(!e->is_bullet_active){
                int rate = NORMAL_ENNEMY_SHOOT_RATE;
                if(e->type == FAST_SHOOTING){
                    rate = FAST_ENNEMY_SHOOT_RATE;
                }
                    if(rand() % (rate * columns * lines) == 0){
                        spawnEnemyBullet(e);
                }
            }

            for(int i = 0; i < MAX_BULLETS; i++){
                Entity *bullet = &p->bullets[i];
                if(collisionBulletEnemy(e, bullet) && bullet->is_visible){
                    hurtEnemy(e, p->damage, game, bullet);
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
            if(collisionEntityPlayer(p, &e->bullet)){
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

    game->boost_enemies = false;
}


