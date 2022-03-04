#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct 
{
    SDL_Rect pos1;
    SDL_Rect pos2;
    SDL_Rect pos3;
    SDL_Surface* img;
}image;

void menu_button(image* m,char name[],int x,int y);
void initBackground(image* background,char name[]);
void liberer(image A);
void afficher_selected(image *m,image *b,SDL_Surface *f,int *i,char selected[]);
void afficher_deselected(image *m,image *b,SDL_Surface *f,int *i,char deselected[]);
#endif
