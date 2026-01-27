#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

    if (TTF_Init() == -1)
    {
        SDL_Log("Erreur TTF_Init: %s", TTF_GetError());
        SDL_Quit();
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

void handle_input_playing(GamePhase *phase, const Uint8 *keys, Player *p, Entity *bullet, bool *bullet_active)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *phase = QUITTING;
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

void handle_input(GamePhase *phase)
{
    

}

void handle_input_starting(GamePhase *phase, const Uint8 *keys)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *phase = QUITTING;
    }

    if(keys[SDL_SCANCODE_RETURN]){
        *phase = PLAYING;
    }
}

void handle_input_ending(GamePhase *phase, const Uint8 *keys)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *phase = QUITTING;
    }

    if(keys[SDL_SCANCODE_RETURN]){
        *phase = QUITTING;
    }
}




void update(Player *p, Entity *bullet, bool *bullet_active, Enemy *enemies, GamePhase *phase, float dt)
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
            *phase = QUITTING;
            return;
        }

    }
}

void renderGame(SDL_Renderer *renderer, Player *p, Entity *bullet, bool bullet_active, Enemy *enemies)
{
    //Background
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

void renderStartMenu(SDL_Renderer *renderer, TTF_Font *font)
{
    //Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Title
    SDL_Surface *text = TTF_RenderUTF8_Solid(font, "Space Invaders", (SDL_Color) {192, 192, 192, 200});
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect text_rect = {
        (SCREEN_WIDTH - text->w) / 2,  // x position
        SCREEN_HEIGHT / 4,  // y position
        text->w,  // width
        text->h   // height
    };
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    //Start button
    SDL_Surface *start = TTF_RenderUTF8_Solid(font, "Start", (SDL_Color) {255, 0, 0, 255});
    SDL_Texture *start_texture = SDL_CreateTextureFromSurface(renderer, start);

    SDL_Rect start_rect = {
        (SCREEN_WIDTH - start->w) / 2,  // x position
        2 * SCREEN_HEIGHT / 3,  // y position
        start->w,  // width
        start->h  // height
    };

    SDL_Rect unfill_rect = {
        (SCREEN_WIDTH - start->w) / 2 - 0.25 * start->w,  // x position
        2 * SCREEN_HEIGHT / 3 - 0.1 * start->h,  // y position
        start->w * 1.5,  // width
        start->h * 1.2  // height
    };
    SDL_RenderCopy(renderer, start_texture, NULL, &start_rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &unfill_rect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(start_texture);
    SDL_FreeSurface(start);
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
