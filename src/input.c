#include "game.h"
#include "utilities.h"
#include "entities.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>


void handle_input_playing(Game *game, const Uint8 *keys)
{
    Player *p = &game->p;
    bool *bullet_active = &p->is_bullet_active;
    Entity *bullet = &p->bullet;
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

