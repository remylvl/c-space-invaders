#include <SDL2/SDL.h>
#include "game.h"
#include "utilities.h"
#include <stdio.h>

int n;
int l;

void setn(int n0){n = n0;}
void setl(int l0){l = l0;}

bool init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur SDL_Init: %s", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Space Invaders (SDL)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!*window)
    {
        SDL_Log("Erreur SDL_CreateWindow: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer)
    {
        SDL_Log("Erreur SDL_CreateRenderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;
}

void handle_input(bool *running, const Uint8 *keys, Player *p, Entity *bullet, bool *bullet_active)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *running = false;
    }

    setVxPlayer(p, 0.0f);
    if (keys[SDL_SCANCODE_LEFT])
        setVxPlayer(p, -PLAYER_SPEED);
    if (keys[SDL_SCANCODE_RIGHT])
        setVxPlayer(p, PLAYER_SPEED);

    if (keys[SDL_SCANCODE_SPACE] && !*bullet_active)
    {
        *bullet_active = true;
        setXEntity(bullet, getXPlayer(p) + getWPlayer(p) / 2 - BULLET_WIDTH / 2);
        setYEntity(bullet, getYPlayer(p));
        setWEntity(bullet, BULLET_WIDTH);
        setHEntity(bullet, BULLET_HEIGHT);
        setVyEntity(bullet, -BULLET_SPEED);
    }
}

void update(Player *p, Entity *bullet, bool *bullet_active, Enemy *enemies, bool *running, float dt)
{
    //Update Player
    setXPlayer(p, getXPlayer(p) + getVxPlayer(p) * dt);
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
    for(int i = 0; i < (n * l); i++){
        Enemy *e = &enemies[i];
        if(!e->is_dead){
            setYEnemy(e, getYEnemy(e) + getVyEnemy(e) * dt);
            if (*bullet_active)
    {
        if(collisionBulletEnemy(e, bullet)){
            e->is_dead = true;
            *bullet_active = false;
        }
    }
        }
        
        

        if (getYEnemy(e) > SCREEN_HEIGHT - getHEnemy(e) || collisionPlayerEnemy(p, e)){
            *running = false;
            return;
        }

    }
}

void render(SDL_Renderer *renderer, Player *p, Entity *bullet, bool bullet_active, Enemy *enemies)
{
    //Bakcground
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Player
    SDL_Rect p_rect = {
        (int)getXPlayer(p), (int)getYPlayer(p),
        getWPlayer(p), getHPlayer(p)};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &p_rect);

    //Enemies
    for(int i = 0; i < (n * l); i++){
        Enemy *e = &enemies[i];
        if(!e->is_dead){
            SDL_Rect enemy_rect = {
                (int)getXEnemy(e), (int)getYEnemy(e),
                getWEnemy(e), getHEnemy(e)};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &enemy_rect);
        }
    }

    //Bullet
    if (bullet_active)
    {
        SDL_Rect bullet_rect = {
            (int)getXEntity(bullet), (int)getYEntity(bullet),
            getWEntity(bullet), getHEntity(bullet)};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &bullet_rect);
    }

    SDL_RenderPresent(renderer);
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
