#include <SDL/SDL.h>
#include "menu_button.h"
#include <SDL/SDL_image.h>
#include <string.h>

void fire_animation(image fire,image bg,SDL_Surface *fenetre,image button)
{
    int i;
    char num;
    fire.pos1.x=button.pos1.x;
    fire.pos1.x=button.pos1.y;
     for(i=0;i<11;i++)
        {
           sprintf(num,"%d",i);
           fire.img=IMG_Load(strcat(num,".png"));
           SDL_BlitSurface(bg.img,&fire.pos2,fenetre,&fire.pos1);
           SDL_BlitSurface(fire.img,NULL,fenetre,&fire.pos1);
           SDL_UpdateRect(fenetre,)

        }
}