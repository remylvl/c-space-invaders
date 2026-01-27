#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "entities.h"
#include "utilities.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 30
#define PLAYER_SPEED 500.0f

#define NORMAL_ENNEMY_WIDTH 50
#define NORMAL_ENNEMY_HEIGHT 20
#define NORMAL_ENNEMY_SPEED 30.0f

#define BULLET_WIDTH 10
#define BULLET_HEIGHT 20
#define BULLET_SPEED 600.0f

bool init(SDL_Window **window, SDL_Renderer **renderer);
void handle_input_playing(GamePhase *phase, const Uint8 *keys, Player *player, Entity *bullet, bool *bullet_active);
void handle_input(GamePhase *phase);
void handle_input_starting(GamePhase *phase, const Uint8 *keys);
void handle_input_losing(GamePhase *phase, const Uint8 *keys);
void update(Player *player, Entity *bullet, bool *bullet_active, Enemy *enemies, GamePhase *phase, float dt);
void renderGame(SDL_Renderer *renderer, Player *player, Entity *bullet, bool bullet_active, Enemy *enemies);
void renderStartMenu(SDL_Renderer *renderer, TTF_Font *font);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);
void setn(int n0);
void setl(int l0);

#endif
