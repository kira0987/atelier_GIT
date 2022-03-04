#ifndef TEXT_H
#define TEXT_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
    TTF_Font *fonttext;
    SDL_Color fontcolor;
    SDL_Surface *txt;
    SDL_Rect postext;
    int police;
} text;

void init_text(text t,char font[],char txt[],int x,int y,int r,int g,int b);
#endif