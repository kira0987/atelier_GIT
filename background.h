#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>



typedef struct
{
    SDL_Surface *img;
    SDL_Surface *img1;
    SDL_Surface *img2;
    SDL_Surface *mask;
    SDL_Rect pos1,pos2,pos3;
    Mix_Chunk *effet;
    Mix_Music *music;
    int niveau,volume,mode,scroll,timer;
    
}background;

typedef struct 
{
    int direction,up,down,time,init_time,pos_init;
    double acceleration,vitesse;
    SDL_Rect camera;
}scrolling;


typedef struct 
{
    SDL_Surface *img;
    SDL_Rect pos;
    Mix_Chunk *effet;
}collision;

#include "personnage.h"

void initBack(background* b,int x,int y,char image[],char song[],char effet[]);
void init_mask(background* b,char name[],SDL_Surface* screen);
void liberer_back(background b);
void libere_collision(collision o);
void add_background_pos(background *b,int pos,int x,int y,int w,int h);
void afficherBack(background b,SDL_Surface *screen,scrolling scroll);
void init_animation(background* animated_object,char name[],int x,int y,int w,int h);
void continuous_animation(background* bg,background* animated_object,char name[],int y,int w,int h,SDL_Surface* screen,int n);
void object_animation(background* bg,background* animated_object,char name[],int y,int w,int h,SDL_Surface* screen,int n,int start);
void init_obstacle(background *b,collision *obstacle,char name[],int x,int y);
void collisionPP(perso *p,collision obstacle,scrolling *scroll,background b);
void sprint(scrolling *scroll);
void slow(scrolling *scroll);
void auto_slow(scrolling *scroll);
void auto_scroll(background *b,scrolling *scroll,int *dt);
void init_scroll(scrolling *scroll,double vitesse,double acceleraion);
void bg_scrolling(background *b,scrolling *scroll,Uint8 *keystates);
void scrolling_perso(background b,scrolling *scroll,perso *p,Uint8 *keystates);
void merge(perso personnage,perso personnage1,scrolling *camera1,scrolling *camera2);
void afficher_perso2(background b,SDL_Surface *screen,scrolling scroll1);
void partage_ecran(scrolling *camera1,scrolling *camera2);
//void init_pixel(perso *p,SDL_Rect* pixels);
//SDL_Rect* allocate_pixels(void);
//void collision_color(perso *p,SDL_Surface *psurface,SDL_Rect* pixels);
//int color_check(perso *p,SDL_Surface *psurface,SDL_Rect* pixels);
//SDL_Color getpixel(SDL_Surface *psurface,SDL_Rect pos);



#endif