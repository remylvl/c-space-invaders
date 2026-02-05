#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entities.h"
#include "utilities.h"

void handle_input_playing(Game *game, const Uint8 *keys);
void handle_input_starting(Game *game, const Uint8 *keys);
void handle_input_ending(Game *game, const Uint8 *keys);
void handle_input_level_choosing(Game *game, const Uint8 *keys);