#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "image.h"
#include "text.h"
#include "Settings.h"

int main(int argc, char *argv[])
{
   int x=0,Q=0,C=0,S=0,P=0,now=0,h=0,v=128;
   char coortext[10],volume[4],num;
   SDL_Event event,open_settings;
   SDL_Surface* fenetre=NULL;
   image bg,play,quit,settings,credits,paper,plus,minus,circle,game;
   text t,vol,fullscreen,name;



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

    initBackground(&bg,"background.jpg");
    SDL_BlitSurface(bg.img,NULL,fenetre,&bg.pos1);
    menu_button(&play,"PLAY_DESELECTED.png",200,150,0,0);
    SDL_BlitSurface(play.img,NULL,fenetre,&play.pos1);
    menu_button(&settings,"SETTINGS_DESELECTED.png",200,350,0,0);
    SDL_BlitSurface(settings.img,NULL,fenetre,&settings.pos1);
    menu_button(&credits,"CREDITS_DESELECTED.png",200,550,0,0);
    SDL_BlitSurface(credits.img,NULL,fenetre,&credits.pos1);
    menu_button(&quit,"QUIT_DESELECTED.png",200,750,0,0);
    SDL_BlitSurface(quit.img,NULL,fenetre,&quit.pos1);


    add_pos(&paper,3,1155,350,45,35);
    add_pos(&paper,2,300,200,45,35);


    sprintf(volume,"%d",(int)(Mix_VolumeMusic(-1)/1.28));
    //init_text(&t,"text.ttf","0,0",30,1750,1000,255,255,255);
    init_text(&vol,"text.ttf",volume,30,1163,360,0,0,0);
    
    init_text(&fullscreen,"text.ttf","Appuyez sur F pour basculer en plein ecran",30,970,520,0,0,0);

    init_text(&name,"text.ttf","unfinished legacy",50,1500,10,255,50,50);
    SDL_BlitSurface(name.txt,NULL,fenetre,&name.postext);

    t.fonttext=TTF_OpenFont("text.ttf",50);
    t.fontcolor.r=255;
    t.fontcolor.g=255;
    t.fontcolor.b=255;

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
              if(h!=1)
              {
                 afficher_deselected(&quit,&bg,fenetre,&Q,"QUIT_DESELECTED.png");
                 afficher_deselected(&credits,&bg,fenetre,&C,"CREDITS_DESELECTED.png"); 
                 afficher_deselected(&settings,&bg,fenetre,&S,"SETTINGS_DESELECTED.png");
                 afficher_deselected(&play,&bg,fenetre,&P,"PLAY_DESELECTED.png");
              }
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
                   menu_button(&paper,"paper.png",900,200,0,0);
                   menu_button(&plus,"plus.png",1253,335,0,0);
                   menu_button(&minus,"minus.png",1050,360,0,0);
                   menu_button(&circle,"circle.png",1127,322,0,0);
                   afficher_settings(fenetre,&x,paper,circle,plus,minus,vol,fullscreen);
                   printf("%d",x);
                }else if(x==1)
                {
                   close_settings(plus,minus,paper,circle,bg,fenetre,&x);
                }

             }
             else if((event.button.button==SDL_BUTTON_LEFT) && (credits.pos1.x+438>event.motion.x && event.motion.x>credits.pos1.x) && (credits.pos1.y+140>event.motion.y && event.motion.y>credits.pos1.y))
             {
                Mix_PlayChannel(-1,son,0);

             }
             else if((event.button.button==SDL_BUTTON_LEFT) && (quit.pos1.x+438>event.motion.x && event.motion.x>quit.pos1.x) && (quit.pos1.y+140>event.motion.y && event.motion.y>quit.pos1.y))
             {
                break;
             }
             else if((x==1) && (event.button.button==SDL_BUTTON_LEFT) && (minus.pos1.x+50>event.motion.x && event.motion.x>minus.pos1.x) && (minus.pos1.y+50>event.motion.y && event.motion.y>minus.pos1.y))
             {
                diminuer_vol(&vol,volume,&v,&paper,fenetre);
             }
             else if((x==1) && (event.button.button==SDL_BUTTON_LEFT) && (plus.pos1.x+50>event.motion.x && event.motion.x>plus.pos1.x) && (plus.pos1.y+50>event.motion.y && event.motion.y>plus.pos1.y))
             {
                augmenter_vol(&vol,volume,&v,&paper,fenetre);
             }
         }

        else if((event.type==SDL_MOUSEMOTION) && (h!=1))
         { 
            sprintf(coortext,"%d,%d",event.motion.x,event.motion.y);
            /*SDL_BlitSurface(bg.img,&pospos,fenetre,&pospos);
            afficher_text(t,coortext,fenetre,fenetre->w-t.txt->w-10,fenetre->h-t.txt->h,t.txt->w+10,t.txt->h);*/
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