#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entities.h"
#include "game.h"
#include "render.h"
#include "input.h"
#include "utilities.h"
#include <SDL2/SDL_ttf.h>


int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (!init(&window, &renderer))
    {
        return 1;
    }

    /*A BOUGER*/
    // Charger une police
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/opentype/ipafont-gothic/ipag.ttf", 64);
    if (!font)
    {
        SDL_Log("Erreur chargement police: %s", TTF_GetError());
        cleanup(window, renderer);
        return 1;
    }

    TTF_Font *hp_font = TTF_OpenFont("/usr/share/fonts/opentype/ipafont-gothic/ipag.ttf", 48);
    if (!font)
    {
        SDL_Log("Erreur chargement police: %s", TTF_GetError());
        cleanup(window, renderer);
        return 1;
    }

    Uint32 last_ticks = SDL_GetTicks();
    Uint32 speed_ticks = SDL_GetTicks();


    Game game = {
        .columns = 0,
        .lines = 0,
        .enemies = NULL,
        .gamephase = START_MENU,
        .p = {},
        .hearts = NULL,
        .hearts_len = 0,
        .boost_enemies = false,
        .current_start_button = 0,
        .last_button_change_ticks = 0
    };

    while (game.gamephase != QUITTING)
    {
        Uint32 ticks = SDL_GetTicks();
        float dt = (ticks - last_ticks) / 1000.0f;
        if (dt > 0.05f)
            dt = 0.05f;

        if(ticks - speed_ticks > NORMAL_ENEMY_BOOST_INTERVAL) {
            game.boost_enemies = true;
            speed_ticks = ticks;
        }

        last_ticks = ticks;
        SDL_PumpEvents();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        switch(game.gamephase){
        case PLAYING : 
            
            handle_input_playing(&game, keys);
            update(&game, dt);
            renderGame(renderer, hp_font, &game);
            break;
        case START_MENU :
            handle_input_starting(&game, keys);
            renderStartMenu(renderer, font, &game);
            break;
        case CHOOSING_LEVEL:
            handle_input_level_choosing(&game, keys);
            renderLevelMenu(renderer, font, &game);
            break;
        case END_GAME_LOSE:
            handle_input_ending(&game, keys);
            renderLoseMenu(renderer, font, &game);
            break;
        case END_GAME_WIN : 
            handle_input_ending(&game, keys);
            renderWinMenu(renderer, font, &game);
            break;
        default : break;
        }
    }
    if (font) TTF_CloseFont(font);
    if (hp_font) TTF_CloseFont(hp_font);
    cleanup(window, renderer);
    return 0;
}
