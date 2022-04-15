#ifndef ENIGME_IMAGE_H
#define ENIGME_IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>



typedef struct 
{
    SDL_Surface* img;
    SDL_Surface* img1;
    SDL_Rect pos_img;
    
}enigme;

typedef struct 
{
    Mix_Chunk *sound;
    SDL_Surface* img;
    SDL_Rect pos_img,pos_sprite;
    int timer,niveau,enig_start,enig_lvl,monkey_number,status,random;
}monkey;



void init_enigme(enigme *e);
void init_monkey(monkey *m);
void afficher_enigme(enigme e,SDL_Surface* screen);
void monkey_animation(enigme e,monkey* m,SDL_Surface* screen,int x,int y);
void monkey_pop(enigme e,monkey* m,SDL_Surface* screen);
void liberer_enigme(enigme e,monkey m);





#endif