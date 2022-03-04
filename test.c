#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "menu_button.h"
#include "text.h"

int main(int argc, char *argv[])
{
   int x=0,Q=0,C=0,S=0,P=0,now=0,h=0;
   char coortext[10],volume[4],num;
   SDL_Event event,open_settings;
   SDL_Surface* fenetre=NULL;
   image bg,play,quit,settings,credits,m,plus,minus,circle,game;
   text t,vol,f,name;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

    TTF_Init();
    
    Mix_Music *musics;
    Mix_Chunk *son=NULL;
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
    musics=Mix_LoadMUS("wowclassic.mp3");
    Mix_PlayMusic(musics,-1);
    son=Mix_LoadWAV("click.wav");
    if(son==NULL)
    {
       printf("Failed to load : %s ",Mix_GetError());
    }
    fenetre=SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);


    SDL_Rect pospos;
    pospos.x=1750;
    pospos.y=1000;
    pospos.w=170;
    pospos.h=80;


    /*fire.pos2.w=fire.img->w+5;
    fire.pos3.h=fire.img->h+5;*/

    initBackground(&bg,"background.jpg");
    SDL_BlitSurface(bg.img,NULL,fenetre,&bg.pos1);
    menu_button(&play,"PLAY_DESELECTED.png",200,150);
    SDL_BlitSurface(play.img,NULL,fenetre,&play.pos1);
    menu_button(&settings,"SETTINGS_DESELECTED.png",200,350);
    SDL_BlitSurface(settings.img,NULL,fenetre,&settings.pos1);
    menu_button(&credits,"CREDITS_DESELECTED.png",200,550);
    SDL_BlitSurface(credits.img,NULL,fenetre,&credits.pos1);
    menu_button(&quit,"QUIT_DESELECTED.png",200,750);
    SDL_BlitSurface(quit.img,NULL,fenetre,&quit.pos1);
    
    vol.fontcolor.r=0;
    vol.fontcolor.g=0;
    vol.fontcolor.b=0;
    vol.fonttext=TTF_OpenFont("text.ttf",30);
    
    m.pos3.x=100;
    m.pos3.y=300;
    m.pos3.w=35;
    m.pos3.h=25;

    sprintf(volume,"%d",(int)(Mix_VolumeMusic(-1)/1.28));
                vol.txt=TTF_RenderText_Blended(vol.fonttext,volume,vol.fontcolor);
                vol.postext.x=1163;
                vol.postext.y=360;

    f.fontcolor=vol.fontcolor;
    f.fonttext=TTF_OpenFont("text.ttf",30);
    f.txt=TTF_RenderText_Blended(f.fonttext,"Appuyez sur F pour basculer en plein ecran",f.fontcolor);
                f.postext.x=970;
                f.postext.y=520;
                
                name.fontcolor.r=255;
                name.fontcolor.g=50;
                name.fontcolor.b=50;
    name.fonttext=TTF_OpenFont("text.ttf",50);
    name.txt=TTF_RenderText_Blended(name.fonttext,"unfinished legacy",name.fontcolor);
                name.postext.x=1500;
                name.postext.y=10;
                SDL_BlitSurface(name.txt,NULL,fenetre,&name.postext);

    t.fonttext=TTF_OpenFont("text.ttf",50);

   SDL_Flip(fenetre);

    while (1)
    {
        SDL_PollEvent(&event);
       
        if(event.type==SDL_QUIT)
        {break;}
        else if(event.type==SDL_KEYDOWN)
        {
           if (event.key.keysym.sym==SDLK_f)
           {
              SDL_WM_ToggleFullScreen(fenetre);
           }
           
        if(event.key.keysym.sym==SDLK_ESCAPE)
        {break;}
        }
        else if(event.type==SDL_MOUSEBUTTONDOWN)
         {
             if((event.button.button==SDL_BUTTON_LEFT) && (play.pos1.x+438>event.motion.x && event.motion.x>play.pos1.x) && (play.pos1.y+140>event.motion.y && event.motion.y>play.pos1.y))
             {
                Mix_PlayChannel(-1,son,0);
                game.img=IMG_Load("background.png");
                game.pos1.x=0;
                game.pos1.y=0;
                SDL_BlitSurface(game.img,NULL,fenetre,&game.pos1);
                SDL_Flip(fenetre);
                h=1;
             }else if((event.button.button==SDL_BUTTON_LEFT) && (settings.pos1.x+438>event.motion.x && event.motion.x>settings.pos1.x) && (settings.pos1.y+140>event.motion.y && event.motion.y>settings.pos1.y))
             {
                Mix_PlayChannel(-1,son,0);
                if(x==0)
                {
                   m.pos1.x=900;
                   m.pos1.y=200;
                   m.pos1.w=600;
                   m.pos1.h=580;
                   m.img=IMG_Load("paper.png");
                   plus.pos1.x=1253;
                   plus.pos1.y=335;
                   plus.img=IMG_Load("plus.png");
                   minus.pos1.x=1050;
                   minus.pos1.y=360;
                   minus.img=IMG_Load("minus.png");
                   circle.pos1.x=1130;
                   circle.pos1.y=325;
                   circle.img=IMG_Load("circle.png");
                   SDL_BlitSurface(m.img,NULL,fenetre,&m.pos1);
                   SDL_BlitSurface(f.txt,NULL,fenetre,&f.postext);
                   SDL_BlitSurface(vol.txt,NULL,fenetre,&vol.postext);
                   SDL_BlitSurface(circle.img,NULL,fenetre,&circle.pos1);
                   SDL_BlitSurface(plus.img,NULL,fenetre,&plus.pos1);
                   SDL_BlitSurface(minus.img,NULL,fenetre,&minus.pos1);
                   SDL_UpdateRect(fenetre,m.pos1.x,m.pos1.y,m.pos1.w,m.pos1.h);
                   SDL_Delay(500);
                     x=1;
                }else if(x==1)
                {
                   liberer(plus);
                   liberer(minus);
                   liberer(m);
                   SDL_BlitSurface(bg.img,&m.pos1,fenetre,&m.pos1);
                   SDL_UpdateRect(fenetre,m.pos1.x,m.pos1.y,m.pos1.w,m.pos1.h);
                   SDL_Delay(500);
                     x=0;
                }

             }else if((event.button.button==SDL_BUTTON_LEFT) && (credits.pos1.x+438>event.motion.x && event.motion.x>credits.pos1.x) && (credits.pos1.y+140>event.motion.y && event.motion.y>credits.pos1.y))
             {
                Mix_PlayChannel(-1,son,0);

             }else if((event.button.button==SDL_BUTTON_LEFT) && (quit.pos1.x+438>event.motion.x && event.motion.x>quit.pos1.x) && (quit.pos1.y+140>event.motion.y && event.motion.y>quit.pos1.y))
             {
                break;
             }else if((x==1) && (event.button.button==SDL_BUTTON_LEFT) && (minus.pos1.x+50>event.motion.x && event.motion.x>minus.pos1.x) && (minus.pos1.y+50>event.motion.y && event.motion.y>minus.pos1.y))
             {
                Mix_VolumeMusic(Mix_VolumeMusic(-1)-1.28);
                sprintf(volume,"%d",(int)(Mix_VolumeMusic(-1)/1.28));
                vol.txt=TTF_RenderText_Blended(vol.fonttext,volume,vol.fontcolor);
                vol.postext.x=1163;
                vol.postext.y=360;
                SDL_BlitSurface(m.img,NULL,fenetre,&m.pos1);
                SDL_BlitSurface(f.txt,NULL,fenetre,&f.postext);
                   SDL_BlitSurface(circle.img,NULL,fenetre,&circle.pos1);
                   SDL_BlitSurface(plus.img,NULL,fenetre,&plus.pos1);
                   SDL_BlitSurface(minus.img,NULL,fenetre,&minus.pos1);
                SDL_BlitSurface(m.img,&m.pos3,fenetre,&m.pos3);
                SDL_BlitSurface(vol.txt,NULL,fenetre,&vol.postext);
                SDL_UpdateRect(fenetre,m.pos1.x,m.pos1.y,m.pos1.w,m.pos1.h);
                SDL_Delay(300);
             }else if((x==1) && (event.button.button==SDL_BUTTON_LEFT) && (plus.pos1.x+50>event.motion.x && event.motion.x>plus.pos1.x) && (plus.pos1.y+50>event.motion.y && event.motion.y>plus.pos1.y))
             {
                Mix_VolumeMusic(Mix_VolumeMusic(-1)+1.28);
                sprintf(volume,"%d",(int)(Mix_VolumeMusic(-1)/1.28));
                vol.txt=TTF_RenderText_Blended(vol.fonttext,volume,vol.fontcolor);
                vol.postext.x=1163;
                vol.postext.y=360;
                SDL_BlitSurface(m.img,NULL,fenetre,&m.pos1);
                SDL_BlitSurface(f.txt,NULL,fenetre,&f.postext);
                   SDL_BlitSurface(circle.img,NULL,fenetre,&circle.pos1);
                   SDL_BlitSurface(plus.img,NULL,fenetre,&plus.pos1);
                   SDL_BlitSurface(minus.img,NULL,fenetre,&minus.pos1);
                SDL_BlitSurface(m.img,&m.pos3,fenetre,&m.pos3);
                SDL_BlitSurface(vol.txt,NULL,fenetre,&vol.postext);
                SDL_UpdateRect(fenetre,m.pos1.x,m.pos1.y,m.pos1.w,m.pos1.h);
                SDL_Delay(300);
             }
         }

        else if((event.type==SDL_MOUSEMOTION) && (h!=1))
         { 
            sprintf(coortext,"%d,%d",event.motion.x,event.motion.y);
            t.txt=TTF_RenderText_Solid(t.fonttext,coortext,t.fontcolor);
            t.postext.x=fenetre->w-t.txt->w-10;
            t.postext.y=fenetre->h-t.txt->h;
            t.postext.w=t.txt->w+10;
            t.postext.h=t.txt->h;
            SDL_BlitSurface(bg.img,&pospos,fenetre,&pospos);
            SDL_BlitSurface(t.txt,NULL,fenetre,&t.postext);
            SDL_UpdateRect(fenetre,pospos.x,pospos.y,pospos.w,pospos.h);
            if((quit.pos1.x+438>event.motion.x && event.motion.x>quit.pos1.x) && (quit.pos1.y+140>event.motion.y && event.motion.y>quit.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&quit,&bg,fenetre,&Q,"QUIT_SELECTED.png");
            }else if(Q==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&quit,&bg,fenetre,&Q,"QUIT_DESELECTED.png");
            }else if((credits.pos1.x+438>event.motion.x && event.motion.x>credits.pos1.x) && (credits.pos1.y+140>event.motion.y && event.motion.y>credits.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&credits,&bg,fenetre,&C,"CREDITS_SELECTED.png");
            }else if(C==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&credits,&bg,fenetre,&C,"CREDITS_DESELECTED.png");    
            }else if((settings.pos1.x+438>event.motion.x && event.motion.x>settings.pos1.x) && (settings.pos1.y+140>event.motion.y && event.motion.y>settings.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&settings,&bg,fenetre,&S,"SETTINGS_SELECTED.png");  
            }else if(S==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&settings,&bg,fenetre,&S,"SETTINGS_DESELECTED.png");  
            }else if((play.pos1.x+438>event.motion.x && event.motion.x>play.pos1.x) && (play.pos1.y+140>event.motion.y && event.motion.y>play.pos1.y))
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_selected(&play,&bg,fenetre,&P,"PLAY_SELECTED.png");
            }else if(P==1)
            {
               SDL_BlitSurface(bg.img,&bg.pos2,fenetre,&bg.pos3);
               afficher_deselected(&play,&bg,fenetre,&P,"PLAY_DESELECTED.png");
            }
         }
    }
    Mix_FreeChunk(son);
    Mix_FreeMusic(musics);
    liberer(bg);
    liberer(play);
    liberer(settings);
    liberer(credits);
    liberer(quit);
    SDL_FreeSurface(fenetre);
    TTF_Quit;
    SDL_Quit;
    return 0;
}