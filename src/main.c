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
    const int n = 5;
    const int l = 3; 
    const int offsetX = NORMAL_ENNEMY_WIDTH / 2;
    const int offsetY = SCREEN_HEIGHT / 10;

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

    Player player = {
        .entity = {
        .x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2,
        .y = SCREEN_HEIGHT - 60,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
        .vx = 0,
        .vy = 0,},
        .HP = 3,
        .damage = 1,
        .bullets = malloc(3 * sizeof(Entity)),
        .last_shot_ticks = 0
    };

    Enemy *enemies = malloc(sizeof(Enemy) * n * l);
    if(enemies == NULL) return 1;
    for(int i = 0; i < (n * l); i++){
        Enemy e = {
            .entity = {
            .x = offsetX + i%n * ((SCREEN_WIDTH - 2 * NORMAL_ENNEMY_WIDTH)/(n-1)) ,
            .y = offsetY + (i/n) * 2 * NORMAL_ENNEMY_HEIGHT,
            .w = NORMAL_ENNEMY_WIDTH,
            .h = NORMAL_ENNEMY_HEIGHT,
            .vx = 0,
            .vy = NORMAL_ENNEMY_SPEED},

        .is_dead = false,
        .is_bullet_active = false,
        .bullet = {0},
        .type = NORMAL
        };
        enemies[i] = e;
    }

    Game game = {
        .columns = n,
        .lines = l,
        .enemies = enemies,
        .gamephase = START_MENU,
        .p = player,
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
    free(game.enemies);
    free(game.hearts);
    return 0;
}
