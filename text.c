#include <SDL/SDL.h>
#include "text.h"
#include <SDL/SDL_ttf.h>


void init_text(text t,char font[],char txt[],int x,int y,int r,int g,int b)
{
    t.fontcolor.r=r;
    t.fontcolor.g=g;
    t.fontcolor.b=b;
    t.fonttext=TTF_OpenFont(font,t.police);
    t.txt=TTF_RenderText_Blended(t.fonttext,txt,t.fontcolor);
    t.postext.x=x;
    t.postext.y=y;
}