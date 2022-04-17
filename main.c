#include "perso.h"

int main()
{
   
    SDL_Event event;
    int running = 1;
    Uint32 dt;
    personne p;
    Uint32 t_prev;
    
    int i;
    SDL_Surface *screen=NULL,*background=NULL;
    SDL_Rect pos_background;
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF|SDL_RESIZABLE);
    SDL_WM_SetCaption("HERO", NULL);
    background= IMG_Load("background.png");
    pos_background.x=0;
    pos_background.y=0;
initperso(&p,screen);
    
    while (running)
    {
        t_prev = SDL_GetTicks();
        afficherperso(&p, screen);
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            running = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                p.dep = 1;
            p.dr = 0;
            deplacerperso(&p, dt);
            animerperso(&p);

                break;
            case SDLK_LEFT:
                p.dep = 0;
            p.dr = 1;
            deplacerperso(&p, dt);
            animerperso(&p);

                break;

            case SDLK_SPACE:
                p.acc += 0.04;
                break;
            case SDLK_s:
                p.acc -= 0.01;
                break;
            case SDLK_g:
                p.acc = 0;
                break;
            case SDLK_UP:
                p.saut = 1;
                break;
            case SDLK_y:
                p.vie = 0;
                break;
            case SDLK_p:
                p.vie = 1;
                break;
            case SDLK_o:
                p.vie = 2;
                break;
            case SDLK_i:
                p.vie = 3;
                break;
            case SDLK_a:
                p.posperso.y = 300;
                break;
            }

            break;
        }
        
        saut(&p);
       
        SDL_Flip(screen);
        dt = SDL_GetTicks() - t_prev;
        SDL_BlitSurface(background, NULL, screen,&pos_background);
    }
for(i = 0; i < 20; i++)
{
SDL_FreeSurface(p.tab[i]);
}
    return 0;
}
