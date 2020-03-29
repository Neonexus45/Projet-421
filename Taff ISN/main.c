#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
//ajout des 3 headers permettant les fonctions Jeu() et Menu() de s'effectuer ligne 31 et 32
#include "Constantes.h"
#include "Menu.h"
#include "Jeu.h"

//la fonction main ou le programme se déroulera
int main (int argc, char* argv[]) {
    //création de la surface window qui est definie comme fenetre par la commande SDL_Setvideomode avec pour dimensions la résolution fournie par le header 'Constantes.h'
    SDL_Surface* window = NULL;
    window = SDL_SetVideoMode(Longueur_ecran,Hauteur_ecran, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
//boucle pour reperer une éventuelle erreur due au chargement corrompu de la SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL ne peux pas charger car erreur suivante : %s\n", SDL_GetError() );
        return 1;
    }
    //meme boucle pour la SDL_ttf
    if(TTF_Init() == -1)
{
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
}
//execution du menu puis du jeu sur la surface window
    Menu(window);
    Jeu(window);
    //arret du programme
    TTF_Quit();
    SDL_Quit();
}
