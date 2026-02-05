#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "entities.h"
#include "utilities.h"

bool init(SDL_Window **window, SDL_Renderer **renderer);
void renderGame(SDL_Renderer *renderer, TTF_Font *font, Game *game);
void renderStartMenu(SDL_Renderer *renderer, TTF_Font *font, Game *game);
void renderWinMenu(SDL_Renderer *renderer, TTF_Font *font, Game *game);
void renderLoseMenu(SDL_Renderer *renderer, TTF_Font *font, Game *game);
void renderLevelMenu(SDL_Renderer *renderer, TTF_Font *font, Game *game);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);