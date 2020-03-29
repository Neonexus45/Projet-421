//inclusion des autres headers pour les faires correspondrent
#include "Menu.h"
#include "Constantes.h"
#include "Jeu.h"
//Fonction affichant le menu
int Menu(SDL_Surface *window)
{


    int h2 = Hauteur_ecran/2;
    int w2 = Longueur_ecran/4;
    SDL_Event event;
    SDL_Surface *background = NULL, *menu1 = NULL, *menu2 = NULL, *Titre =NULL, *Jouer =NULL, *Regle =NULL, *Quitter =NULL, *TxtRegles = NULL, *TxtRegles1 = NULL, *TxtRegles2 = NULL, *TxtRegles3 = NULL, *TxtRegles4 = NULL, *TxtRegles5 = NULL;
    SDL_Rect position;
    int continuer = 1;
    TTF_Font *police = NULL;
    SDL_Color couleurPolice = {0, 0, 0};


    SDL_WM_SetIcon(SDL_LoadBMP("icone.bmp"), NULL);


    menu1 = SDL_CreateRGBSurface(SDL_HWSURFACE, w2 , h2, 16, 0,0,0,0);
    menu2 = SDL_CreateRGBSurface(SDL_HWSURFACE, Longueur_ecran/1.75 ,Hauteur_ecran/2, 16, 0,0,0,0);
    background = SDL_LoadBMP("start_menu.bmp");
    Titre = SDL_LoadBMP("Titre.bmp");

    SDL_WM_SetCaption("GAMING SIMULATOR 2K19", NULL);


//écriture des differents inscription qu'il y aura a fil du jeu
    police = TTF_OpenFont("Casino.ttf", 50);
    Jouer = TTF_RenderText_Blended(police, "-Jouer", couleurPolice);
    Regle = TTF_RenderText_Blended(police, "-Regles", couleurPolice);
    police = TTF_OpenFont("Casino.ttf", 18);
    SDL_Color couleurPolice2 = {255,255,255};
    TxtRegles = TTF_RenderText_Blended(police, "Le joueur lancera une serie de trois des 4 fois.", couleurPolice2);
    TxtRegles1 = TTF_RenderText_Blended(police, "L'objectif est de realiser le meilleur score possible sachant que:", couleurPolice2);
    TxtRegles2 = TTF_RenderText_Blended(police, "   Realiser deux chiffre identiques (paires) rapporte 2 POINTS", couleurPolice2);
    TxtRegles3 = TTF_RenderText_Blended(police, "   Realiser trois chiffres identiques rapporte la somme des des", couleurPolice2);
    TxtRegles4 = TTF_RenderText_Blended(police, "   Realiser un 5,2,1 rapporte 20 POINTS.\n\n", couleurPolice2);
    TxtRegles5 = TTF_RenderText_Blended(police, "(un fichier resumant la partie sera inclus dans le .txt)", couleurPolice2);

      //positionement de base des surfaces pré-event
      position.x = 0;
      position.y = 0;
      SDL_BlitSurface(background,NULL,window,&position);

      position.x = Longueur_ecran/20;
      position.y = (Hauteur_ecran/2)-(h2/5);
      SDL_FillRect(menu1, NULL, SDL_MapRGB(menu1->format, 40,40,40));
      SDL_SetAlpha(menu1, SDL_SRCALPHA, 210);
      SDL_BlitSurface(menu1,NULL,window, &position);

      position.x = Longueur_ecran/20;
      position.y = Hauteur_ecran/10;
      SDL_SetColorKey(Titre, SDL_SRCCOLORKEY,SDL_MapRGB(Titre->format, 0,0,0));
      SDL_BlitSurface(Titre,NULL,window,&position);

      position.x = Longueur_ecran/20+w2/10;
      position.y = (Hauteur_ecran/2);
      SDL_BlitSurface(Jouer,NULL,window,&position);

      position.x = Longueur_ecran/20+w2/10;
      position.y = (Hauteur_ecran/2)+Hauteur_ecran/10;
      SDL_BlitSurface(Regle,NULL,window,&position);

      SDL_Flip(window);

      //boucle event, cette boucle est la source de toute interaction avec l'écran, ici, nous avons définie une fonction pour quitter le jeu avec la touche echap ou avec la croix rouge, puis un boucle interne de detection de click a un endroit précis pour pouvoir naviguer dans l'UI du menu....
      while (continuer)
      {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            default:
                break;
                }
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                //ce if défini l'encadrement necessaire lors du click pour que le menu garde l'UI précedent tout en affichant les régles.
                if ((event.button.x >=Longueur_ecran/20+w2/10)
                &&(event.button.x <= Longueur_ecran/20+w2/1.2)
                &&(event.button.y >= (Hauteur_ecran/2)+Hauteur_ecran/10)
                &&(event.button.y <= (Hauteur_ecran/2)+Hauteur_ecran/10+60))
                {
                //lors du click, replacement des surfaces d'affichage pour permettre a l'UI d'afficher les regles dans une surface donnée , ici menu2
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);

                position.x = Longueur_ecran/20;
                position.y = (Hauteur_ecran/2)-(h2/5);
                SDL_FillRect(menu1, NULL, SDL_MapRGB(menu1->format, 40,40,40));
                SDL_SetAlpha(menu1, SDL_SRCALPHA, 210);
                SDL_BlitSurface(menu1,NULL,window, &position);

                position.x = Longueur_ecran/20+w2/10;
                position.y = (Hauteur_ecran/2);
                SDL_BlitSurface(Jouer,NULL,window,&position);

                position.x = Longueur_ecran/20+w2/10;
                position.y = (Hauteur_ecran/2)+Hauteur_ecran/5;
                SDL_BlitSurface(Quitter,NULL,window,&position);

                SDL_Color couleurPolice = {255, 0, 0};
                police = TTF_OpenFont("Casino.ttf", 50);
                Regle = TTF_RenderText_Blended(police, "-Regles", couleurPolice);
                position.x = Longueur_ecran/20+w2/10;
                position.y = (Hauteur_ecran/2)+Hauteur_ecran/10;
                SDL_BlitSurface(Regle,NULL,window,&position);
                position.x = Longueur_ecran/2;
                position.y = (Hauteur_ecran/2)+Hauteur_ecran/10-Hauteur_ecran/3;
                police = TTF_OpenFont("Casino.ttf", 75);
                Regle = TTF_RenderText_Blended(police, "-Regles", couleurPolice);
                SDL_BlitSurface(Regle,NULL,window,&position);

                position.x = Longueur_ecran/5+w2/2;
                position.y =(Hauteur_ecran/2)-(h2/5);
                SDL_FillRect(menu2, NULL, SDL_MapRGB(menu2->format, 40,40,40));
                SDL_SetAlpha(menu2, SDL_SRCALPHA, 210);
                SDL_BlitSurface(menu2,NULL,window, &position);


                //écriture des regles avec un intervale correspondant a leur police, ici 50 de hauteur, pour donner l'impression d'un interligne 1
                position.x = Longueur_ecran/5+w2/2;
                position.y = (Hauteur_ecran/2)-(h2/5)+50;
                SDL_BlitSurface(TxtRegles,NULL,window,&position);
                position.x = Longueur_ecran/5+w2/2;
                position.y = (Hauteur_ecran/2)-(h2/5)+100;
                SDL_BlitSurface(TxtRegles1,NULL,window,&position);
                position.x = Longueur_ecran/5+w2/2;
                position.y = (Hauteur_ecran/2)-(h2/5)+150;
                SDL_BlitSurface(TxtRegles2,NULL,window,&position);
                position.x = Longueur_ecran/5+w2/2;
                position.y = (Hauteur_ecran/2)-(h2/5)+200;
                SDL_BlitSurface(TxtRegles3,NULL,window,&position);
                position.x = Longueur_ecran/5+w2/2;
                position.y = (Hauteur_ecran/2)-(h2/5)+250;
                SDL_BlitSurface(TxtRegles4,NULL,window,&position);
                position.x = Longueur_ecran/5+w2/2;
                position.y = (Hauteur_ecran/2)-(h2/5)+300;
                SDL_BlitSurface(TxtRegles5,NULL,window,&position);

                SDL_Flip(window);
      }
      //deuxieme evenement ou si le joueur click sur jouer, la fonction Menu s'arrete et donne place a la fonction Jeu
      else if ((event.button.x >=Longueur_ecran/20+w2/10)
                &&(event.button.x <= Longueur_ecran/20+w2/1.2)
                &&(event.button.y >= (Hauteur_ecran/2)
                &&(event.button.y <= (Hauteur_ecran/2)+Hauteur_ecran/5+60)))
               {
           continuer = 0;

               }
      break;
}
        default:
        break;
        }
      }
}

