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
    Uint32 ticks = SDL_GetTicks();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *phase = QUITTING;
    }

    if(keys[SDL_SCANCODE_RETURN] && ticks - game->last_button_change_ticks > 200.0f){
        switch(game->current_start_button){
        case 0 : *phase = CHOOSING_LEVEL;
        game->last_button_change_ticks = ticks;
        break;
        case 2 : *phase = QUITTING;
        break;
        default: break;
    }}

    if((keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_LEFT]) && ticks - game->last_button_change_ticks > 200.0f){
        game->last_button_change_ticks = ticks;
        switch(game->current_start_button){
        case 0 : game->current_start_button = 2;
        break;
        default: game->current_start_button -= 1;
        break;
    }}
    if((keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_RIGHT]) && ticks - game->last_button_change_ticks > 200.0f){
        game->last_button_change_ticks = ticks;
        switch(game->current_start_button){
        case 2 : game->current_start_button = 0;
        break;
        default: game->current_start_button += 1;
        break;
    }}
}

void handle_input_level_choosing(Game *game, const Uint8 *keys)
{
    GamePhase *phase = &game->gamephase;
    SDL_Event event;
    Uint32 ticks = SDL_GetTicks();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *phase = QUITTING;
    }

    if(keys[SDL_SCANCODE_RETURN] && ticks - game->last_button_change_ticks > 200.0f){
        switch(game->current_level_button){
        case 0 : *phase = PLAYING;
        break;
        case 5 : *phase = START_MENU;
        game->last_button_change_ticks = ticks;
        break;
        default: break;
    }}

    if((keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_LEFT]) && ticks - game->last_button_change_ticks > 200.0f){
        game->last_button_change_ticks = ticks;
        switch(game->current_level_button){
        case 0 : game->current_level_button = 5;
        break;
        default: game->current_level_button -= 1;
        break;
    }}
    if((keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_RIGHT]) && ticks - game->last_button_change_ticks > 200.0f){
        game->last_button_change_ticks = ticks;
        switch(game->current_level_button){
        case 5 : game->current_level_button = 0;
        break;
        default: game->current_level_button += 1;
        break;
    }}
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

