#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "background.h"
#include "personnage.h"


void initBack(background* b,int x,int y,char image[],char song[],char effet[])
{
    b->music=Mix_LoadMUS(song);

    b->effet=Mix_LoadWAV(effet);

    b->img=IMG_Load(image);
    if(b->img==NULL){return ;}

    b->img1=IMG_Load(image);
    if(b->img1==NULL){return ;}

    b->img2=IMG_Load(image);
    if(b->img==NULL){return ;}
    b->pos1.x=x;
    b->pos1.y=y;
    b->niveau=0;
    b->mode=0;
    b->scroll==0;
}

void init_mask(background* b,char name[],SDL_Surface* screen)
{
    b->mask=IMG_Load(name);
    SDL_BlitSurface(b->mask,NULL,screen,&b->pos1);
}

void add_background_pos(background *b,int pos,int x,int y,int w,int h)
{
    if(pos==2)
    {
        b->pos2.x=x;
        b->pos2.y=y;
        b->pos2.w=w;
        b->pos2.h=h;
    }
    if(pos==3)
    {
        b->pos3.x=x;
        b->pos3.y=y;
        b->pos3.w=w;
        b->pos3.h=h;
    }
}

void liberer_back(background b)
{
    SDL_FreeSurface(b.img1);
    SDL_FreeSurface(b.img2);
    SDL_FreeSurface(b.img);
    SDL_FreeSurface(b.mask);
    Mix_FreeChunk(b.effet);
    Mix_FreeMusic(b.music);
}

void libere_collision(collision o)
{
    SDL_FreeSurface(o.img);
}

void afficherBack(background b,SDL_Surface *screen,scrolling scroll)
{
    //Mix_PlayMusic(b.music,-1);
    SDL_BlitSurface(b.img,&scroll.camera,screen,&b.pos1);
    //SDL_Flip(screen);
}

void afficher_perso2(background b,SDL_Surface *screen,scrolling scroll1)
{
        SDL_BlitSurface(b.img,&scroll1.camera,screen,&b.pos3);

}

void init_animation(background* animated_object,char name[],int x,int y,int w,int h)
{
    animated_object->img=IMG_Load(name);
    animated_object->pos2.x=-w;
    animated_object->pos2.y=y;
    animated_object->pos2.w=w;
    animated_object->pos2.h=h;
}

void continuous_animation(background* bg,background* animated_object,char name[],int y,int w,int h,SDL_Surface* screen,int n)
{
    int now;
        now=SDL_GetTicks();

        if(now>animated_object->timer+(150*animated_object->niveau))
        {
            animated_object->pos2.x=(animated_object->pos2.x+w)%(w*n);
            SDL_BlitSurface(bg->img1,&animated_object->pos1,bg->img2,&animated_object->pos1);
            SDL_BlitSurface(animated_object->img,&animated_object->pos2,bg->img2,&animated_object->pos1);
            SDL_BlitSurface(bg->img2,&animated_object->pos1,bg->img,&animated_object->pos1);
            SDL_UpdateRect(screen,animated_object->pos1.x,animated_object->pos1.y,w,h);
            animated_object->niveau++;
        }

}

void object_animation(background* bg,background* animated_object,char name[],int y,int w,int h,SDL_Surface* screen,int n,int start)
{
   
    int now;
        now=SDL_GetTicks();

        if(now>animated_object->timer+(150*animated_object->niveau) && now<animated_object->timer+(150*n))
        {           
            animated_object->pos2.x+=w;
            SDL_BlitSurface(bg->img1,&animated_object->pos1,bg->img2,&animated_object->pos1);
            SDL_BlitSurface(animated_object->img,&animated_object->pos2,bg->img2,&animated_object->pos1);
            SDL_BlitSurface(bg->img2,&animated_object->pos1,bg->img,&animated_object->pos1);
            SDL_UpdateRect(screen,animated_object->pos1.x,animated_object->pos1.y,w,h);
            animated_object->niveau++;
        }
    

    if(animated_object->niveau==n)
    {
        animated_object->mode=1;
    }

}

void init_scroll(scrolling *scroll,double vitesse,double acceleraion)
{
    scroll->acceleration=acceleraion;
    scroll->vitesse=vitesse;
    scroll->up=0;
    scroll->init_time=0;
    scroll->time=0;
    scroll->camera.x=0;
    scroll->camera.y=300;
    scroll->camera.w=1920;
    scroll->camera.h=1080;
}

void sprint(scrolling *scroll)
{
    if(scroll->acceleration<0.039)
        {
            scroll->time=SDL_GetTicks()-scroll->init_time;
            scroll->acceleration+=0.003;
        }
        
}

void slow(scrolling *scroll)
{
    if(scroll->acceleration>0)
        {
            scroll->acceleration-=0.01;
        }
    if(scroll->acceleration<0)
    {
        scroll->acceleration=0;
    }
}

void auto_slow(scrolling *scroll)
{
    if(scroll->acceleration>0)
        {
            scroll->acceleration-=0.001;
        }
    if(scroll->acceleration<0)
    {
        scroll->acceleration=0;
    }
}

void bg_scrolling(background *b,scrolling *scroll,Uint8 *keystates)
{
            scroll->camera.x-=((scroll->direction)*(scroll->vitesse+(scroll->time*scroll->acceleration)));

    if(!keystates[SDLK_LSHIFT])
    {
        
        b->scroll=0;
    }
}

void scrolling_perso(background b,scrolling *scroll,perso *p,Uint8 *keystates)
{
    if(p->pos1.x>(b.pos1.x+(scroll->camera.w/2)) && p->pos1.x<(b.img->w-(scroll->camera.w/2)))
    {
        scroll->camera.x=p->pos1.x-(scroll->camera.w/2);
    }
    if(p->pos1.y>(b.pos1.y+(scroll->camera.h/2)) && p->pos1.y<(b.img->h-(scroll->camera.h/2)))
    {
        scroll->camera.y=p->pos1.y-(scroll->camera.h/2);
    }
}

void init_obstacle(background *b,collision *obstacle,char name[],int x,int y)
{
    obstacle->img=IMG_Load(name);
    obstacle->pos.x=x;
    obstacle->pos.y=y;
    obstacle->pos.w=obstacle->img->w;
    obstacle->pos.w=obstacle->img->h;
    SDL_BlitSurface(obstacle->img,NULL,b->img,&obstacle->pos);
}

void collisionPP(perso *p,collision obstacle,scrolling *scroll,background b)
{
    if(p->pos1.y+p->pos1.h>obstacle.pos.y && p->pos1.y<obstacle.pos.y+obstacle.img->h)
    {
        if((p->pos1.x+p->pos1.w>obstacle.pos.x) && (p->pos1.x<obstacle.pos.x))
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            p->pos1.x=obstacle.pos.x-p->pos1.w;

        }else if((p->pos1.x<obstacle.pos.x+obstacle.img->w) && (p->pos1.x+p->pos1.w>obstacle.pos.x+obstacle.img->w))
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            p->pos1.x=obstacle.pos.x+obstacle.img->w;
        }
    }

    if(p->pos1.x+p->pos1.w>obstacle.pos.x && p->pos1.x<obstacle.pos.x+obstacle.img->w)
    {
        if(p->pos1.y+p->pos1.h>obstacle.pos.y && p->pos1.y<obstacle.pos.y)
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            p->pos1.y=obstacle.pos.y-(p->pos1.h);
        }else if(p->pos1.y<obstacle.pos.y+obstacle.img->h && p->pos1.y>obstacle.pos.y)
        {
            SDL_BlitSurface(b.img2,&p->pos1,b.img,&p->pos1);
            p->pos1.y=obstacle.pos.y+obstacle.img->h;
        }
    }

}

/*SDL_Rect* allocate_pixels(void)
{
    SDL_Rect *pixels;
    
    pixels=(SDL_Rect*)malloc(8*sizeof(SDL_Rect));

    return(pixels);
}

void init_pixel(perso *p,SDL_Rect* pixels)
{

    pixels[0]=p->pos1;

    pixels[1].x=p->pos1.x+(p->pos1.w/2);
    pixels[1].y=p->pos1.y;

    pixels[2].x=p->pos1.x+p->pos1.w;
    pixels[2].y=p->pos1.y;

    pixels[3].x=p->pos1.x+p->pos1.w;
    pixels[3].y=p->pos1.y+(p->pos1.h/2);

    pixels[4].x=p->pos1.x+p->pos1.w;
    pixels[4].y=p->pos1.y+p->pos1.h;

    pixels[5].x=p->pos1.x+(p->pos1.w/2);
    pixels[5].y=p->pos1.y+p->pos1.h;

    pixels[6].x=p->pos1.x;
    pixels[6].y=p->pos1.y+p->pos1.h;

    pixels[7].x=p->pos1.x;
    pixels[7].y=p->pos1.y+(p->pos1.h/2);

}

void collision_color(perso *p,SDL_Surface *psurface,SDL_Rect* pixels)
{
    int i=color_check(p,psurface,pixels);
    switch(i)
    {
        case 0:
        printf("-0-");
            p->pos1.x+=2;
            p->pos1.y+=2;
            break;
        case 1:
        printf("-1-");
            p->pos1.y+=2;
            break;
        case 2:
        printf("-2-");
            p->pos1.x-=2;
            p->pos1.y+=2;
            break;
        case 3:
        printf("-3-");
            p->pos1.x-=2;
            break;
        case 4:
        printf("-4-");
            p->pos1.x-=2;
            p->pos1.y-=2;
            break;
        case 5:
        printf("-5-");
            p->pos1.y-=2;
            break;
        case 6:
        printf("-6-");
            p->pos1.x+=2;
            p->pos1.y-=2;
            break;
        case 7:
        printf("-7-");
            p->pos1.x-=2;
            break;
    }
}

int color_check(perso *p,SDL_Surface *psurface,SDL_Rect* pixels)
{
    
    SDL_Rect pixel;
    SDL_Color col;
    
    while(p->collision<7)
    {     
        init_pixel(p,pixels);
        p->collision++;
        printf("%d ---- ",p->collision);
        pixel=pixels[p->collision];
        printf("(x=%d,y=%d)--",pixel.x,pixel.y);
        
        col=getpixel(psurface,pixel);
        printf("r=%d + g=%d + b=%d----",col.r,col.g,col.b);

        if(col.r==0 && col.g==0 && col.b==0)
        {
            return p->collision;
        }
    }
}

SDL_Color getpixel(SDL_Surface *psurface,SDL_Rect pos)
{
    SDL_Color color;
    Uint32 col=0;

    char* pPosition=(char*)psurface->pixels;
    pPosition+=(psurface->pitch*pos.y);
    pPosition+=(psurface->format->BytesPerPixel*pos.x);
    memcpy(&col,pPosition,psurface->format->BytesPerPixel);
    SDL_GetRGB(col,psurface->format,&color.r,&color.g,&color.b);
    return(color);
}*/


 void partage_ecran(scrolling *camera1,scrolling *camera2)
 {
     camera1->camera.w=camera1->camera.w/2;
     camera2->camera.w=camera1->camera.w;
     camera2->camera.y=camera1->camera.y;
     camera2->camera.h=camera1->camera.h;
 }

 void merge(perso personnage,perso personnage1,scrolling *camera1,scrolling *camera2)
 {
     if(personnage1.pos1.x-personnage.pos1.x<=1920 && personnage1.pos1.x-personnage.pos1.x>=-1920)
     {
         camera1->camera.w=camera1->camera.w*2;
     }else
     {
         partage_ecran(camera1,camera2);
     }
 }