#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


typedef struct 
{
    //sprite personne
        SDL_Surface *sprite;
        SDL_Rect possprite;
        int direction;//(0:droite||1:gauche)
    //position ecran
        SDL_Rect posscreen;
    //score personne
        SDL_Surface *score;
        SDL_Rect posscore;
        TTF_Font *font_score;
        SDL_Color scorecolor;
    //vie personne
        SDL_Surface *vies;
        SDL_Rect posvies;
        TTF_Font *font_vies;
        SDL_Color viecolor;
    //helthbar personne
        SDL_Surface *healthbar;
        SDL_Rect posbar;
    //mouvement et acceleration
        double vitesse,acceleration;

}personne;

void initPerso(personne *p);
void afficherPerso(personne p,SDL_Surface *screen);
void animerPerso(personne *p);
void moveperso(personne *p,Uint32 dt);
#endif