#include "enigme_image.h"


void init_enigme(enigme *e)
{
    e->img=IMG_Load("BARRELS.png");
    e->img1=IMG_Load("BARRELS.png");
    e->pos_img.x=0;
    e->pos_img.y=0;
}

void init_monkey(monkey *m)
{
    m->img=IMG_Load("monkeys.png");
    m->sound=Mix_LoadWAV("toy.wav");
    m->pos_img.x=0;
    m->pos_img.y=0;
    m->pos_img.w=373;
    m->pos_img.h=285;
    m->pos_sprite.x=-373;
    m->pos_sprite.y=0;
    m->pos_sprite.w=373;
    m->pos_sprite.h=285;
    m->status=0;
    m->niveau=1;
    m->enig_lvl=0;
    m->monkey_number=0;
}


void afficher_enigme(enigme e,SDL_Surface* screen)
{
    SDL_BlitSurface(e.img,NULL,screen,&e.pos_img);
    SDL_Flip(screen);
}




void monkey_pop(enigme e,monkey* m,SDL_Surface* screen)
{
    int now=SDL_GetTicks();
    if(now>m->enig_start)
    {
        //printf("(enig_start=%d)--",m->enig_start);
        if(m->status==0)
        {
            m->status=1;
        }
        if((m->status==1 || m->status==-1))
            {
                if(m->monkey_number==1)
                    monkey_animation(e,m,screen,250,275);

                if(m->monkey_number==2)
                    monkey_animation(e,m,screen,850,175);
                
                if(m->monkey_number==3)
                    monkey_animation(e,m,screen,1475,275);
                
                if(m->monkey_number==4)
                    monkey_animation(e,m,screen,1100,550);

                if(m->monkey_number==5)
                    monkey_animation(e,m,screen,475,550);

                if(m->monkey_number==6)
                    monkey_animation(e,m,screen,600,600);

            }
    }
    
}
void monkey_animation(enigme e,monkey* m,SDL_Surface* screen,int x,int y)
{
    int now=SDL_GetTicks();

            m->pos_img.x=x;
            m->pos_img.y=y;
                if(now>m->timer+(50*m->niveau))
                {
                    m->pos_sprite.x=(m->pos_sprite.x+(m->status*m->pos_sprite.w))%(m->pos_sprite.w*6);
                    m->niveau++;
                    SDL_BlitSurface(e.img1,&m->pos_img,screen,&m->pos_img);
                    SDL_BlitSurface(m->img,&m->pos_sprite,screen,&m->pos_img);    
                    SDL_UpdateRect(screen,m->pos_img.x,m->pos_img.y,m->pos_sprite.w,m->pos_sprite.h);

                    if(m->niveau%6==0 && m->status==1)
                    {
                        m->status=(-1)*m->status;
                    }
                    else if(m->niveau%6==0 && m->status==-1)
                        {
                            SDL_BlitSurface(e.img1,&m->pos_img,screen,&m->pos_img);
                            SDL_Flip(screen);
                            m->status=0;
                            m->enig_lvl=0;
                        } 
                }    
}
void liberer_enigme(enigme e,monkey m)
{
    SDL_FreeSurface(e.img1);
    SDL_FreeSurface(e.img);
    SDL_FreeSurface(m.img);
}