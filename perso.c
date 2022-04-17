#include "perso.h"
void initperso(personne *p,SDL_Surface *screen)  

{
    p->posperso.x = 10;  
    p->posperso.y = 400; 

    p->posvie.x = 800; 
    p->posvie.y = 0;
    p->vitesse = 5;   
    p->acc = 0;        
    p->up = 0;        
    char nomFich[20];
    int i;
    for (i = 0; i < 20; i++) 
    {
        sprintf(nomFich, "%d.png", i);
        p->tab[i] = IMG_Load(nomFich);
    }
    char nomvie[20]; 
    int j;
    for (j = 0; j < 4; j++)
    {
        sprintf(nomvie, "v%d.png", j);
        p->tabvie[j] = IMG_Load(nomvie);
    }
    p->dr = 0;
    p->num = 0;
    p->vie = 0; 

    p->saut = 0;
    p->v_x = 4;
    p->v_y = -6.5;
    p->v_grav = 0.3;
}
void afficherperso(personne *p, SDL_Surface *screen)
{  
    SDL_BlitSurface(p->tab[p->num], NULL, screen, &(p->posperso));
    SDL_BlitSurface(p->tabvie[p->vie], NULL,screen, &(p->posvie));
}

void deplacerperso(personne *p, Uint32 dt)
{
    if (p->dep == 1)
    {
        p->posperso.x += p->acc * dt  + p->vitesse;
    }
    else if (p->dep == 0)
    {
        p->posperso.x -= p->acc * dt  + p->vitesse;
    }
}

void animerperso(personne *p)
{
    if (p->dr == 0)
    {
        if (p->num >= 8)
            p->num = 0;
        else
            p->num++;
    }
    else
    {
        if (p->num == 19 || p->num < 10)
            p->num = 10;
        else
            p->num++;
    }
   
}

void saut(personne *p)
{
    
    if (p->saut == 1)
    {
        if (p->dr == 0)
        {
            p->posperso.x += p->v_x;
            p->posperso.y += p->v_y;
            p->v_y += p->v_grav;
        }
        else if (p->dr == 1)
        {
            p->posperso.x -= p->v_x;
            p->posperso.y += p->v_y;
            p->v_y += p->v_grav;
        }
    }
    if (p->posperso.y > 400)
    {
        p->v_y = -6.5;
        p->saut = 0;
    }
}
