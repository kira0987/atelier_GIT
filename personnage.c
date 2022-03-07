#include"personnage.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

void initPerso(personne *p)
{
    //inistialisation personnage
    p->sprite=IMG_Load("spritesheet.png");
    if(p->sprite==NULL){return;}
    p->possprite.x=0;
    p->possprite.y=0;
    p->possprite.w=("largeur image du spritesheet/nombre de colonnes de sprite");
    p->possprite.h=("hauteur image du spritesheet/nombre de lignes de sprite");
    //initialisation score
    p->score=IMG_Load("score.png");
    if(p->score==NULL){return;}
    p->posscore.x=("position en haut à droite");
    p->posscore.y=("position en haut à droite");
    p->posscore.w=("largeur image de score");
    p->posscore.h=("hauteur image de score");
    //initialisation vies max x5
    p->vies=IMG_Load("vies.png");
    if(p->vies==NULL){return;}
    p->posvies.x=("position en haut à gauche");
    p->posvies.y=("position en haut à gauche");
    p->posvies.w=("largeur image de vie");
    p->posvies.h=("hauteur image de vie");
    //initialisation healthbar
    p->healthbar=IMG_Load("healthbar.png");
    if(p->healthbar==NULL){return;}
    p->posbar.x=("position en haut à gauche");
    p->posbar.y=("position en haut à gauche");
    p->posbar.w=("largeur image de vie");
    p->posbar.h=("hauteur image de vie");
}

void afficherPerso(personne p,SDL_Surface *screen)
{
SDL_BlitSurface(p.sprite,NULL,screen,&p.possprite);
SDL_BlitSurface(p.score,NULL,screen,&p.posscore);
SDL_BlitSurface(p.vies,NULL,screen,&p.posvies);
SDL_BlitSurface(p.healthbar,NULL,screen,&p.posbar);

}
void animerPerso(personne *p)
{
    p->possprite.y=p->direction*p->possprite.h; 
      if(p->possprite.x=="largeur sprite"-p->possprite.w)
 p->possprite.x=0;
 else
 p->possprite.x=p->possprite.x+p->possprite.w;     
}

void moveperso(personne *p,Uint32 dt)
{
p->vitesse=5;
p->acceleration=0;
p->possprite.x=((1/2)*p->acceleration*dt*dt)+(p->vitesse*dt);
}



