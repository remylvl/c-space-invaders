#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "utilities.h"
#include "entities.h"
#include <stdio.h>
#include "game.h"

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
    //SDL_SetWindowFullscreen(*window, SDL_WINDOW_FULLSCREEN);

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


void renderGame(SDL_Renderer *renderer, TTF_Font *font, Game *game)
{

    Player *p = &game->p;
    Enemy *enemies = game->enemies;
    int lines = game->lines;
    int columns = game->columns; 

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
    for(int i = 0; i < (lines * columns); i++){
        Enemy *e = &enemies[i];
        if(!e->is_dead){
            SDL_Rect enemy_rect = {
                (int)getXEnemy(e), (int)getYEnemy(e),
                getWEnemy(e), getHEnemy(e)};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &enemy_rect);
        }
        if(e->is_bullet_active){
            SDL_Rect bullet_rect = {
            (int)getXEntity(&e->bullet), (int)getYEntity(&e->bullet),
            getWEntity(&e->bullet), getHEntity(&e->bullet)};
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderFillRect(renderer, &bullet_rect);
        }
    }

    //Bullets
    for(int i = 0; i < MAX_BULLETS; i++)
    {
        Entity bullet = p->bullets[i];
        if(bullet.is_visible){

            SDL_Rect bullet_rect = {
            (int)bullet.x, (int)bullet.y,
            bullet.w, bullet.h};
            
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &bullet_rect);
    }}

    //Hearts
    for(int i = 0; i < game->hearts_len; i++){
        if(!game->hearts[i].is_visible) continue;
        SDL_Rect case_rect = {
            game->hearts[i].x, game->hearts[i].y, game->hearts[i].w, game->hearts[i].h};
        SDL_Surface *s = SDL_LoadBMP("textures/heart.bmp");
        SDL_Texture *t = SDL_CreateTextureFromSurface(renderer,s);
        SDL_FreeSurface(s);
        SDL_RenderCopy(renderer,t,NULL,&case_rect);
    }

    //HP
    SDL_Surface *text = TTF_RenderUTF8_Solid(font, "Lives : ", (SDL_Color) {255, 255, 255, 255});
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect text_rect = {
        SCREEN_WIDTH / 20,  // x position
        SCREEN_HEIGHT / 40,  // y position
        text->w,  // width
        text->h   // height
    };
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);


    for(int i = 0; i < p->HP; i++){
        SDL_Rect case_rect = {
            SCREEN_WIDTH / 18 + text->w + i * (50 + SCREEN_WIDTH / 60), SCREEN_HEIGHT / 35,
            50, 50};
        SDL_Surface *s = SDL_LoadBMP("textures/heart.bmp");
        SDL_Texture *t = SDL_CreateTextureFromSurface(renderer,s);
        SDL_FreeSurface(s);
        SDL_RenderCopy(renderer,t,NULL,&case_rect);
    }

    SDL_RenderPresent(renderer);
}



void renderStartMenu(SDL_Renderer *renderer, TTF_Font *font, Game *game)
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
         SCREEN_HEIGHT / 2,  // y position
        start->w,  // width
        start->h  // height
    };
    SDL_RenderCopy(renderer, start_texture, NULL, &start_rect);

    //Difficulty Button
    SDL_Surface *diff = TTF_RenderUTF8_Solid(font, "Difficulty", (SDL_Color) {255, 0, 0, 255});
    SDL_Texture *diff_texture = SDL_CreateTextureFromSurface(renderer, diff);

    SDL_Rect diff_rect = {
        (SCREEN_WIDTH - diff->w) / 2,  // x position
         SCREEN_HEIGHT / 2 + 2 * start->h,  // y position
        diff->w,  // width
        diff->h  // height
    };
    SDL_RenderCopy(renderer, diff_texture, NULL, &diff_rect);

    //Exit button
    SDL_Surface *exit = TTF_RenderUTF8_Solid(font, "Exit", (SDL_Color) {255, 0, 0, 255});
    SDL_Texture *exit_texture = SDL_CreateTextureFromSurface(renderer, exit);

    SDL_Rect exit_rect = {
        (SCREEN_WIDTH - exit->w) / 2,  // x position
         SCREEN_HEIGHT / 2 + + 2*start->h + 2 * diff->h,  // y position
        exit->w,  // width
        exit->h  // height
    };
    SDL_RenderCopy(renderer, exit_texture, NULL, &exit_rect);


    int height;
    int width;
    int x;
    int y;
    switch(game->current_start_button){
        case 0: 
        width = start->w * 1.5;
        height = start->h * 1.2;
        x = (SCREEN_WIDTH - start->w) / 2 - 0.25 * start->w;
        y = SCREEN_HEIGHT / 2 - 0.1 * start->h;
        break;
        case 1: 
        height = diff->h * 1.2;
        width = diff->w * 1.5;
        x = (SCREEN_WIDTH - diff->w) / 2 - 0.25 * diff->w;
        y = SCREEN_HEIGHT / 2 + 2 * start->h - 0.1 * diff->h;
        break;
        case 2: 
        height = exit->h * 1.2;
        width = exit->w * 1.5;
        x = (SCREEN_WIDTH - exit->w) / 2 - 0.25 * exit->w;
        y = SCREEN_HEIGHT / 2 + 2*start->h + 2 * diff->h - 0.1 * start->h;
        break;
        default: break;


    }
    //Selected Button
    SDL_Rect unfill_rect = {
        x,  // x position
        y,  // y position
        width,  // width
        height  // height
    };
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &unfill_rect);

    SDL_RenderPresent(renderer);
}

void renderLevelMenu(SDL_Renderer *renderer, TTF_Font *font, Game *game)
{
    //Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Title
    SDL_Surface *text = TTF_RenderUTF8_Solid(font, "Space Invaders", (SDL_Color) {192, 192, 192, 200});
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect text_rect = {
        (SCREEN_WIDTH - text->w) / 2,  // x position
        SCREEN_HEIGHT / 6,  // y position
        text->w,  // width
        text->h   // height
    };
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    //Level 1 button
    SDL_Surface *level1 = TTF_RenderUTF8_Solid(font, "Level 1", (SDL_Color) {0, 255, 0, 255});
    SDL_Texture *level1_texture = SDL_CreateTextureFromSurface(renderer, level1);

    SDL_Rect level1_rect = {
        (SCREEN_WIDTH - level1->w) / 2,  // x position
         SCREEN_HEIGHT / 3,  // y position
        level1->w,  // width
        level1->h  // height
    };
    SDL_RenderCopy(renderer, level1_texture, NULL, &level1_rect);

    //Level 2 button
    SDL_Surface *level2 = TTF_RenderUTF8_Solid(font, "Level 2", (SDL_Color) {255, 255, 0, 255});
    SDL_Texture *level2_texture = SDL_CreateTextureFromSurface(renderer, level2);

    SDL_Rect level2_rect = {
        (SCREEN_WIDTH - level2->w) / 2,  // x position
         SCREEN_HEIGHT / 3 + 1.5 * level1->h,  // y position
        level2->w,  // width
        level2->h  // height
    };
    SDL_RenderCopy(renderer, level2_texture, NULL, &level2_rect);

    //Level 3 button
    SDL_Surface *level3 = TTF_RenderUTF8_Solid(font, "Level 3", (SDL_Color) {255, 128, 0, 255});
    SDL_Texture *level3_texture = SDL_CreateTextureFromSurface(renderer, level3);

    SDL_Rect level3_rect = {
        (SCREEN_WIDTH - level3->w) / 2,  // x position
         SCREEN_HEIGHT / 3 + 1.5 * (level1->h + level2->h),  // y position
        level3->w,  // width
        level3->h  // height
    };
    SDL_RenderCopy(renderer, level3_texture, NULL, &level3_rect);

    //Level 4 button
    SDL_Surface *level4 = TTF_RenderUTF8_Solid(font, "Level 4", (SDL_Color) {0, 0, 255, 255});
    SDL_Texture *level4_texture = SDL_CreateTextureFromSurface(renderer, level4);

    SDL_Rect level4_rect = {
        (SCREEN_WIDTH - level4->w) / 2,  // x position
         SCREEN_HEIGHT / 3 + 1.5 * (level1->h + level2->h + level3->h),  // y position
        level4->w,  // width
        level4->h  // height
    };
    SDL_RenderCopy(renderer, level4_texture, NULL, &level4_rect);

    //Level 5 button
    SDL_Surface *level5 = TTF_RenderUTF8_Solid(font, "Level 5", (SDL_Color) {128, 0, 128, 255});
    SDL_Texture *level5_texture = SDL_CreateTextureFromSurface(renderer, level5);

    SDL_Rect level5_rect = {
        (SCREEN_WIDTH - level5->w) / 2,  // x position
         SCREEN_HEIGHT / 3 + 1.5 * (level1->h + level2->h + level3->h + level4->h),  // y position
        level5->w,  // width
        level5->h  // height
    };
    SDL_RenderCopy(renderer, level5_texture, NULL, &level5_rect);

    //Return button
    SDL_Surface *exit = TTF_RenderUTF8_Solid(font, "Return", (SDL_Color) {255, 255, 255, 255});
    SDL_Texture *exit_texture = SDL_CreateTextureFromSurface(renderer, exit);

    SDL_Rect exit_rect = {
        (SCREEN_WIDTH - exit->w) / 2,  // x position
         SCREEN_HEIGHT / 3 + 1.5 * (level1->h + level2->h + level3->h + level4->h +level5->h),  // y position
        exit->w,  // width
        exit->h  // height
    };
    SDL_RenderCopy(renderer, exit_texture, NULL, &exit_rect);


    int height;
    int width;
    int x;
    int y;
    switch(game->current_level_button){
        case 0: 
        width = level1->w * 1.5;
        height = level1->h * 1.2;
        x = (SCREEN_WIDTH - level1->w) / 2 - 0.25 * level1->w;
        y = SCREEN_HEIGHT / 3 - 0.1 * level1->h;
        break;
        case 1: 
        width = level2->w * 1.5;
        height = level2->h * 1.2;
        x = (SCREEN_WIDTH - level2->w) / 2 - 0.25 * level2->w;
        y = SCREEN_HEIGHT / 3 + 1.5 * level1->h - 0.1 * level2->h;
        break;
        case 2: 
        width = level3->w * 1.5;
        height = level3->h * 1.2;
        x = (SCREEN_WIDTH - level3->w) / 2 - 0.25 * level3->w;
        y = SCREEN_HEIGHT / 3 + 1.5 * (level1->h +level2->h) - 0.1 * level3->h;
        break;
        case 3: 
        width = level4->w * 1.5;
        height = level4->h * 1.2;
        x = (SCREEN_WIDTH - level4->w) / 2 - 0.25 * level4->w;
        y = SCREEN_HEIGHT / 3 + 1.5 * (level1->h +level2->h + level3->h) - 0.1 * level4->h;
        break;
        case 4: 
        width = level5->w * 1.5;
        height = level5->h * 1.2;
        x = (SCREEN_WIDTH - level5->w) / 2 - 0.25 * level5->w;
        y = SCREEN_HEIGHT / 3  + 1.5 * (level1->h +level2->h + level3->h + level4->h) - 0.1 * level5->h;
        break;
        case 5: 
        width = exit->w * 1.5;
        height = exit->h * 1.2;
        x = (SCREEN_WIDTH - exit->w) / 2 - 0.25 * exit->w;
        y = SCREEN_HEIGHT / 3 + 1.5 * (level1->h +level2->h + level3->h + level4->h + level5->h) - 0.1 * exit->h;
        break;
        default: break;


    }
    //Selected Button
    SDL_Rect unfill_rect = {
        x,  // x position
        y,  // y position
        width,  // width
        height  // height
    };
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &unfill_rect);

    SDL_RenderPresent(renderer);
}




void renderLoseMenu(SDL_Renderer *renderer, TTF_Font *font, Game *game)
{
    //Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Title
    SDL_Surface *text = TTF_RenderUTF8_Solid(font, "You lost !", (SDL_Color) {255, 0, 0, 255});
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect text_rect = {
        (SCREEN_WIDTH - text->w) / 2,  // x position
        SCREEN_HEIGHT / 4,  // y position
        text->w,  // width
        text->h   // height
    };
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    //leave text
    SDL_Surface *leave = TTF_RenderUTF8_Solid(font, "Press Enter to leave", (SDL_Color) {255, 0, 0, 255});
    SDL_Texture *leave_texture = SDL_CreateTextureFromSurface(renderer, leave);

    SDL_Rect leave_rect = {
        (SCREEN_WIDTH - leave->w) / 2,  // x position
        2 * SCREEN_HEIGHT / 3,  // y position
        leave->w,  // width
        leave->h  // height
    };
    SDL_RenderCopy(renderer, leave_texture, NULL, &leave_rect);
    
    SDL_RenderPresent(renderer);
}

void renderWinMenu(SDL_Renderer *renderer, TTF_Font *font, Game *game)
{
    //Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Title
    SDL_Surface *text = TTF_RenderUTF8_Solid(font, "You won !", (SDL_Color) {0, 255, 0, 255});
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect text_rect = {
        (SCREEN_WIDTH - text->w) / 2,  // x position
        SCREEN_HEIGHT / 4,  // y position
        text->w,  // width
        text->h   // height
    };
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    //leave text
    SDL_Surface *leave = TTF_RenderUTF8_Solid(font, "Press Enter to leave", (SDL_Color) {0, 255, 0, 255});
    SDL_Texture *leave_texture = SDL_CreateTextureFromSurface(renderer, leave);

    SDL_Rect leave_rect = {
        (SCREEN_WIDTH - leave->w) / 2,  // x position
        2 * SCREEN_HEIGHT / 3,  // y position
        leave->w,  // width
        leave->h  // height
    };
    SDL_RenderCopy(renderer, leave_texture, NULL, &leave_rect);
    
    SDL_RenderPresent(renderer);
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