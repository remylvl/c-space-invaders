#include "utilities.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "entities.h"


void handle_input_playing(Game *game, const Uint8 *keys)
{
    Player *p = &game->p;
    GamePhase *phase = &game->gamephase;


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

    Uint32 ticks = SDL_GetTicks();

    if (keys[SDL_SCANCODE_SPACE] && ticks - p->last_shot_ticks > BULLET_RELOAD_TIME)
    {
        for(int i = 0; i < MAX_BULLETS; i++){
            if(!p->bullets[i].is_visible){
                p->bullets[i].is_visible = true;
                p->bullets[i].x = p->entity.x + p->entity.w / 2 - BULLET_WIDTH / 2;
                p->bullets[i].y = p->entity.y;
                p->bullets[i].w = BULLET_WIDTH;
                p->bullets[i].h = BULLET_HEIGHT;
                p->bullets[i].vy = -BULLET_SPEED;
                p->last_shot_ticks = ticks;
                break;
            }
        }
        
    }
}

void handle_input_starting(Game *game, const Uint8 *keys)
{
    GamePhase *phase = &game->gamephase;
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

void handle_input_ending(Game *game, const Uint8 *keys)
{
    GamePhase *phase = &game->gamephase;
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

