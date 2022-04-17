 #include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

typedef struct 
{SDL_Surface *tab[20],*tabvie[4];
SDL_Rect posperso,posvie;
double vitesse,acc,v_x,v_grav,v_y;
int dep;
int up;
Uint32 dt;
int dr,num,vie,saut;
}personne;



void initperso(personne *p,SDL_Surface *screen);
void afficherperso(personne *p, SDL_Surface *screen);
void deplacerperso(personne *p,Uint32 dt);
void animerperso(personne *p);
void saut(personne *p);
#endif // FONCTION_H_INCLUDED
