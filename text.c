#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "text.h"
#include "menu_button.h"


void afficher_text(text t,char txt[],SDL_Surface* fenetre,int x,int y,int w,int h)
{
    t.txt=TTF_RenderText_Blended(t.fonttext,txt,t.fontcolor);
    t.postext.x=x;
    t.postext.y=y;
    t.postext.w=t.txt->w;
    t.postext.h=t.txt->h;
    if(w!=0 && h!=0)
    {
        t.postext.w=w;
        t.postext.h=h;
    }
    SDL_BlitSurface(t.txt,NULL,fenetre,&t.postext);
    SDL_UpdateRect(fenetre,t.postext.x,t.postext.y,t.postext.w,t.postext.h);
}

void init_text(text *t,char font[],char txt[],int police,int x,int y,int r,int g,int b)
{
    t->fontcolor.r=r;
    t->fontcolor.g=g;
    t->fontcolor.b=b;
    t->police=police;
    t->fonttext=TTF_OpenFont(font,t->police);
    t->txt=TTF_RenderText_Blended(t->fonttext,txt,t->fontcolor);
    t->postext.x=x;
    t->postext.y=y;
}

