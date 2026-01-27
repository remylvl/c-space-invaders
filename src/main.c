#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entities.h"
#include "game.h"
#include "utilities.h"
#include <SDL2/SDL_ttf.h>


int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    const int n = 6;
    const int l = 2; 
    const int offsetX = NORMAL_ENNEMY_WIDTH / 2;
    const int offsetY = SCREEN_HEIGHT / 20;

    setl(l);
    setn(n);

    if (!init(&window, &renderer))
    {
        return 1;
    }

    // Charger une police
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/opentype/ipafont-gothic/ipag.ttf", 64);
    if (!font)
    {
        SDL_Log("Erreur chargement police: %s", TTF_GetError());
        cleanup(window, renderer);
        return 1;
    }

    GamePhase phase = START_MENU;
    Uint32 last_ticks = SDL_GetTicks();

    Player player = {
        .entity = {
        .x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2,
        .y = SCREEN_HEIGHT - 60,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT,
        .vx = 0,
        .vy = 0}
    };

    Entity bullet = {0};
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

        .is_dead = false        
        };
        enemies[i] = e;
    }

    

    bool bullet_active = false;

    while (phase != QUITTING)
    {
        Uint32 ticks = SDL_GetTicks();
        float dt = (ticks - last_ticks) / 1000.0f;
        if (dt > 0.05f)
            dt = 0.05f;
        last_ticks = ticks;
        SDL_PumpEvents();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        switch(phase){
        case PLAYING : 
            handle_input_playing(&phase, keys, &player, &bullet, &bullet_active);
            update(&player, &bullet, &bullet_active, enemies, &phase, dt);
            renderGame(renderer, &player, &bullet, bullet_active, enemies);
            break;
        case START_MENU :
            handle_input_starting(&phase, keys);
            renderStartMenu(renderer, font);
            break;
        default : break;
        }
    }
    if (font) TTF_CloseFont(font);
    cleanup(window, renderer);
    free(enemies);
    return 0;
}
