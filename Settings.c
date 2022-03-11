#include <SDL/SDL.h>
#include "menu_button.h"
#include "Settings.h"
#include <SDL/SDL_image.h>
#include "text.h"
 

void diminuer_vol(text *t,char volume[],int *vol,image *paper,SDL_Surface *fenetre)
{

    (*vol)=(int)(Mix_VolumeMusic(-1)-1.28);
    sprintf(volume,"%d",(int)((*vol)/1.28));
    t->txt=TTF_RenderText_Blended(t->fonttext,volume,t->fontcolor);
    Mix_VolumeMusic((*vol));
    SDL_BlitSurface(paper->img,&paper->pos2,fenetre,&paper->pos3);
    SDL_BlitSurface(t->txt,NULL,fenetre,&t->postext);
    SDL_UpdateRect(fenetre,1155,350,45,35);
    SDL_Delay(150);
}

void augmenter_vol(text *t,char volume[],int *vol,image *paper,SDL_Surface *fenetre)
{

    (*vol)=(int)(Mix_VolumeMusic(-1)+1.28);
    sprintf(volume,"%d",(int)((*vol)/1.28));
    t->txt=TTF_RenderText_Blended(t->fonttext,volume,t->fontcolor);
    Mix_VolumeMusic((*vol));
    SDL_BlitSurface(paper->img,&paper->pos2,fenetre,&paper->pos3);
    SDL_BlitSurface(t->txt,NULL,fenetre,&t->postext);
    SDL_UpdateRect(fenetre,1155,350,45,35);
    SDL_Delay(150);
}

void afficher_settings(SDL_Surface* fenetre,int *x,image paper,image circle,image plus,image minus,text vol,text fullscreen)
{
    SDL_BlitSurface(paper.img,NULL,fenetre,&paper.pos1);
    SDL_BlitSurface(fullscreen.txt,NULL,fenetre,&fullscreen.postext);
    SDL_BlitSurface(vol.txt,NULL,fenetre,&vol.postext);
    SDL_BlitSurface(circle.img,NULL,fenetre,&circle.pos1);
    SDL_BlitSurface(plus.img,NULL,fenetre,&plus.pos1);
    SDL_BlitSurface(minus.img,NULL,fenetre,&minus.pos1);
    SDL_UpdateRect(fenetre,paper.pos1.x,paper.pos1.y,paper.pos1.w,paper.pos1.h);
    SDL_Delay(150);
    (*x)=1;
}

void close_settings(image plus,image minus,image paper,image circle,image bg,SDL_Surface* fenetre,int *x)
{
    SDL_BlitSurface(bg.img,&paper.pos1,fenetre,&paper.pos1);
    SDL_UpdateRect(fenetre,paper.pos1.x,paper.pos1.y,paper.pos1.w,paper.pos1.h);
    liberer(plus);
    liberer(minus);
    liberer(paper);
    liberer(circle);
    SDL_Delay(150);
    (*x)=0;
}