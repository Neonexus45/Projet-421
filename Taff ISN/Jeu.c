//inclusion des fonctions pour les faire correspondrent
#include "Constantes.h"
#include "Jeu.h"

//fonction du jeu
int Jeu(SDL_Surface *window) {
//initialisation
 srand(time(NULL)); //Ini. de la fonction permettant d'avoir un chiffre au hasard entre une valeur donné et 0
 FILE *Resume = fopen("Resume.txt", "w"); // ouverture du .txt permettant aux joueurs de voir le résume de la partie et du gagnant
 SDL_Surface *background = NULL, *Boutton1 = NULL, *Txt1 = NULL, *Txtfacef1 = NULL, *Txtfacef2 = NULL, *Txtfacef3 = NULL, *Sprite1 = NULL, *Sprite2 = NULL, *Sprite3 = NULL, *Sprite4 = NULL, *Sprite5 = NULL, *Sprite6 = NULL, *face1 = NULL, *face2 = NULL, *face3 = NULL, *face4 = NULL, *face5 = NULL, *face6 = NULL, *Brelantxt = NULL, *pairestxt = NULL, *rientxt = NULL, *JACKPOTtxt = NULL, *Boutton2 = NULL, *Score1 = NULL, *Score2 = NULL, *c1 = NULL, *c2 = NULL, *c3 = NULL, *c4 = NULL, *c5 = NULL, *ctotal = NULL, *c6 = NULL, *c7 = NULL, *c8 = NULL, *c9 = NULL, *c10 = NULL, *ctotal2 = NULL, *P1win = NULL, *P2win = NULL, *Egalite = NULL, *Resultat = NULL, *reset = NULL, *Quitter = NULL;
 SDL_Rect position;
 SDL_Event event;
 //création des multiples variables qui nous serviront pour la suite
 int continuer = 1;
 int dface1;
 int dface2;
 int dface3;
 int C1 = 0;
 int CTotal = 0;
 int Ctotal2 = 0;
 char V1[50];
 int cpt = 0;
 TTF_Font *police = NULL;
 SDL_Color couleurPolice = {255, 255, 255};
 SDL_WM_SetIcon(SDL_LoadBMP("icone.bmp"), NULL);

 //placement des 3 surfaces de base
 Boutton1 = SDL_CreateRGBSurface(SDL_HWSURFACE, Longueur_ecran/4, Hauteur_ecran/10, 16, 0,0,0,0);
 Boutton2 = SDL_CreateRGBSurface(SDL_HWSURFACE, Longueur_ecran/8, Hauteur_ecran/5, 16, 0,0,0,0);
 background = SDL_LoadBMP("Tapis.bmp");
 //definition des Sprites d'animation des trois dés
 Sprite1 = SDL_LoadBMP("dice1.bmp");
 Sprite2 = SDL_LoadBMP("dice2.bmp");
 Sprite3 = SDL_LoadBMP("dice3.bmp");
 Sprite4 = SDL_LoadBMP("dice4.bmp");
 Sprite5 = SDL_LoadBMP("dice5.bmp");
 Sprite6 = SDL_LoadBMP("dice6.bmp");
 //definition des images finales des dés
 face1 = SDL_LoadBMP("1.bmp");
 face2 = SDL_LoadBMP("2.bmp");
 face3 = SDL_LoadBMP("3.bmp");
 face4 = SDL_LoadBMP("4.bmp");
 face5 = SDL_LoadBMP("5.bmp");
 face6 = SDL_LoadBMP("6.bmp");
 //definition de tout les textes grace a SDL.ttf
 police = TTF_OpenFont("Bebas-Regular.ttf", 50);
 Quitter = TTF_RenderText_Blended(police, "appuyez sur echap pour quitter, merci d'avoir joue !", couleurPolice);
 rientxt = TTF_RenderText_Blended(police, "Aucun combo... bouh !", couleurPolice);
 pairestxt = TTF_RenderText_Blended(police," une paire...Pas mal!", couleurPolice);
 Brelantxt = TTF_RenderText_Blended(police, "un Brelan...Excellent!", couleurPolice);
JACKPOTtxt = TTF_RenderText_Blended(police, "     Bingo ! un 421", couleurPolice);
P1win = TTF_RenderText_Blended(police, "Joueur 1 gagne la partie !", couleurPolice);
P2win = TTF_RenderText_Blended(police, "Joueur 2 gagne la partie !", couleurPolice);
Egalite = TTF_RenderText_Blended(police, "Egalite !", couleurPolice);
Resultat = TTF_RenderText_Blended(police, "Score P1 vs Score P2 ", couleurPolice);
police = TTF_OpenFont("Bebas-Regular.ttf", 20);
Score1 = TTF_RenderText_Blended(police, " Votre score", couleurPolice);
Score2 = TTF_RenderText_Blended(police, "Score versus", couleurPolice);
police = TTF_OpenFont("Bebas-Regular.ttf", 35);

//exclusion du fond gris des sprites pour les détourer dans l'animation
 SDL_SetColorKey(Sprite2, SDL_SRCCOLORKEY, SDL_MapRGB(Sprite2->format, 100,100,100));
 SDL_SetColorKey(Sprite3, SDL_SRCCOLORKEY, SDL_MapRGB(Sprite3->format, 100,100,100));
 SDL_SetColorKey(Sprite4, SDL_SRCCOLORKEY, SDL_MapRGB(Sprite4->format, 100,100,100));
 SDL_SetColorKey(Sprite5, SDL_SRCCOLORKEY, SDL_MapRGB(Sprite5->format, 100,100,100));

      position.x = 0;
      position.y = 0;
      SDL_BlitSurface(background,NULL,window,&position);

      //disposition de l'affichage au moment T ou le joueur doit lancer son premier dés
      position.x = Longueur_ecran/2-Longueur_ecran/8;
      position.y = Hauteur_ecran-Hauteur_ecran/4;
      SDL_FillRect(Boutton1, NULL, SDL_MapRGB(Boutton1->format, 40,40,40));
      SDL_SetAlpha(Boutton1, SDL_SRCALPHA, 210);
      SDL_BlitSurface(Boutton1,NULL,window,&position);
      police = TTF_OpenFont("Bebas-Regular.ttf", 50);
      position.x = Longueur_ecran/2-Longueur_ecran/8+Longueur_ecran/40;
      position.y = Hauteur_ecran-Hauteur_ecran/4+Hauteur_ecran/30-20;
      Txt1 = TTF_RenderText_Blended(police, "    Lancer", couleurPolice);

      SDL_BlitSurface(Txt1,NULL,window,&position);
      fprintf(Resume,"Récapitulatif de la partie :\n\n");
      SDL_Flip(window);


      //boucle qui comme dans Menu.c gére les evenements tels que la fermeture du programme et les impacts des clicks
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
                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                //event pour lequel le joueur click sur Lancer qui active l'animation des dés, leurs décompte et leur affichage dans le tableau des scores
                if((event.button.x >=Longueur_ecran/2-Longueur_ecran/8)
                &&(event.button.x <= Longueur_ecran/2-Longueur_ecran/8+Longueur_ecran/4)
                &&(event.button.y >= Hauteur_ecran-Hauteur_ecran/4)
                &&(event.button.y <= Hauteur_ecran-Hauteur_ecran/4+Hauteur_ecran/10)&&(cpt <10))
                {
                //animation du dés (impossible a faire en boucle en SDL , en tout cas a mon niveau
                C1 = 0;
                police = TTF_OpenFont("Bebas-Regular.ttf", 50);
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);
                position.x = Longueur_ecran/3-20;
                position.y = 0;
                SDL_BlitSurface(Sprite1,NULL,window,&position);
                position.x = Longueur_ecran/2-20;
                SDL_BlitSurface(Sprite1,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2-20;
                SDL_BlitSurface(Sprite1,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(100);
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);
                position.x = Longueur_ecran/3-20;
                position.y = 20;
                SDL_BlitSurface(Sprite2,NULL,window,&position);
                position.x = Longueur_ecran/2-20;
                SDL_BlitSurface(Sprite2,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2-20;
                SDL_BlitSurface(Sprite2,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(100);
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);
                position.x = Longueur_ecran/3-20;
                position.y = 60;
                SDL_BlitSurface(Sprite3,NULL,window,&position);
                position.x = Longueur_ecran/2-20;
                SDL_BlitSurface(Sprite3,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2-20;
                SDL_BlitSurface(Sprite3,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(100);
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);
                position.x = Longueur_ecran/3-20;
                position.y = 80;
                SDL_BlitSurface(Sprite4,NULL,window,&position);
                position.x = Longueur_ecran/2-20;
                SDL_BlitSurface(Sprite4,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2-20;
                SDL_BlitSurface(Sprite4,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(100);
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);
                position.x = Longueur_ecran/3-20;
                position.y = 100;
                SDL_BlitSurface(Sprite5,NULL,window,&position);
                position.x = Longueur_ecran/2-20;
                SDL_BlitSurface(Sprite5,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2-20;
                SDL_BlitSurface(Sprite5,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(100);
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);
                position.x = Longueur_ecran/3-20;
                position.y = 120;
                SDL_BlitSurface(Sprite6,NULL,window,&position);
                position.x = Longueur_ecran/2-20;
                SDL_BlitSurface(Sprite6,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2-20;
                SDL_BlitSurface(Sprite6,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(100);
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);
                position.x = Longueur_ecran/3-20;
                position.y = 140;
                SDL_BlitSurface(Sprite2,NULL,window,&position);
                position.x = Longueur_ecran/2-20;
                SDL_BlitSurface(Sprite2,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2-20;
                SDL_BlitSurface(Sprite2,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(100);
                position.x = 0;
                position.y = 0;
                SDL_BlitSurface(background,NULL,window,&position);

                //affichage du score
                SDL_FillRect(Boutton2, NULL, SDL_MapRGB(Boutton1->format, 40,40,40));
                SDL_SetAlpha(Boutton2, SDL_SRCALPHA, 210);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5;
                SDL_BlitSurface(Boutton2,NULL,window,&position);
                SDL_BlitSurface(Score1,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2+60;
                SDL_BlitSurface(Boutton2,NULL,window,&position);
                SDL_BlitSurface(Score2,NULL,window,&position);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+20;
                SDL_BlitSurface(c1,NULL,window,&position);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+40;
                SDL_BlitSurface(c2,NULL,window,&position);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+60;
                SDL_BlitSurface(c3,NULL,window,&position);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+80;
                SDL_BlitSurface(c4,NULL,window,&position);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+100;
                SDL_BlitSurface(c5,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+20;
                SDL_BlitSurface(c6,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+40;
                SDL_BlitSurface(c7,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+60;
                SDL_BlitSurface(c8,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+80;
                SDL_BlitSurface(c9,NULL,window,&position);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+100;
                SDL_BlitSurface(c10,NULL,window,&position);
                position.x = Longueur_ecran/2-Longueur_ecran/8;
                position.y = Hauteur_ecran-Hauteur_ecran/4;
                SDL_FillRect(Boutton1, NULL, SDL_MapRGB(Boutton1->format, 40,40,40));
                SDL_SetAlpha(Boutton1, SDL_SRCALPHA, 210);
                SDL_BlitSurface(Boutton1,NULL,window,&position);


                //reaparition du boutton lancer pour relancer les dés
                position.x = Longueur_ecran/2-Longueur_ecran/8+Longueur_ecran/40;
                position.y = Hauteur_ecran-Hauteur_ecran/4+Hauteur_ecran/30-20;
                Txt1 = TTF_RenderText_Blended(police, "  Suivant!", couleurPolice);
                SDL_BlitSurface(Txt1,NULL,window,&position);

                //determination de la valeur des trois dés, geré par la fonction rand qui s'assure du hasard de la chose
                dface1 = rand() % 6;
                dface1++;
                position.x = Longueur_ecran/3-20;
                position.y = 160;
                if (dface1 == 1) {  SDL_BlitSurface(face1,NULL,window,&position); Txtfacef1 = TTF_RenderText_Blended(police, "1", couleurPolice);dface1 = 1;}
                else if (dface1 == 2) {  SDL_BlitSurface(face2,NULL,window,&position); Txtfacef1 = TTF_RenderText_Blended(police, "2", couleurPolice);dface1 = 2;}
                else if (dface1 == 3) {  SDL_BlitSurface(face3,NULL,window,&position); Txtfacef1 = TTF_RenderText_Blended(police, "3", couleurPolice);dface1 = 3;}
                else if (dface1 == 4) {  SDL_BlitSurface(face4,NULL,window,&position); Txtfacef1 = TTF_RenderText_Blended(police, "4", couleurPolice);dface1 = 4;}
                else if (dface1 == 5) {  SDL_BlitSurface(face5,NULL,window,&position); Txtfacef1 = TTF_RenderText_Blended(police, "5", couleurPolice);dface1 = 5;}
                else if (dface1 == 6) {  SDL_BlitSurface(face6,NULL,window,&position); Txtfacef1 = TTF_RenderText_Blended(police, "6", couleurPolice);dface1 = 6;}
                SDL_Flip(window);
                SDL_Delay(250);
                dface2 = rand() % 6;
                dface2++;
                position.x = Longueur_ecran/2-20;
                if (dface2 == 1) {  SDL_BlitSurface(face1,NULL,window,&position); Txtfacef2 = TTF_RenderText_Blended(police, "1", couleurPolice);dface2 = 1;}
                else if (dface2 == 2) {  SDL_BlitSurface(face2,NULL,window,&position); Txtfacef2 = TTF_RenderText_Blended(police, "2", couleurPolice);dface2 = 2;}
                else if (dface2 == 3) {  SDL_BlitSurface(face3,NULL,window,&position); Txtfacef2 = TTF_RenderText_Blended(police, "3", couleurPolice);dface2 = 3;}
                else if (dface2 == 4) {  SDL_BlitSurface(face4,NULL,window,&position); Txtfacef2 = TTF_RenderText_Blended(police, "4", couleurPolice);dface2 = 4;}
                else if (dface2 == 5) {  SDL_BlitSurface(face5,NULL,window,&position); Txtfacef2 = TTF_RenderText_Blended(police, "5", couleurPolice);dface2 = 5;}
                else if (dface2 == 6) {  SDL_BlitSurface(face6,NULL,window,&position); Txtfacef2 = TTF_RenderText_Blended(police, "6", couleurPolice);dface2 = 6;}
                SDL_Flip(window);
                SDL_Delay(250);
                dface3 = rand() % 6;
                dface3++;
                position.x = (Longueur_ecran/3)*2-20;
                if (dface3 == 1) {  SDL_BlitSurface(face1,NULL,window,&position); Txtfacef3 = TTF_RenderText_Blended(police, "1", couleurPolice);dface3 = 1;}
                else if (dface3 == 2) {  SDL_BlitSurface(face2,NULL,window,&position); Txtfacef3 = TTF_RenderText_Blended(police, "2", couleurPolice);dface3 = 2;}
                else if (dface3 == 3) {  SDL_BlitSurface(face3,NULL,window,&position); Txtfacef3 = TTF_RenderText_Blended(police, "3", couleurPolice);dface3 = 3;}
                else if (dface3 == 4) {  SDL_BlitSurface(face4,NULL,window,&position); Txtfacef3 = TTF_RenderText_Blended(police, "4", couleurPolice);dface3 = 4;}
                else if (dface3 == 5) {  SDL_BlitSurface(face5,NULL,window,&position); Txtfacef3 = TTF_RenderText_Blended(police, "5", couleurPolice);dface3 = 5;}
                else if (dface3 == 6) {  SDL_BlitSurface(face6,NULL,window,&position); Txtfacef3 = TTF_RenderText_Blended(police, "6", couleurPolice);dface3 = 6;}
                SDL_Flip(window);

                //apparition des valeurs en chiffre romain des dés en dessous de leurs images
                SDL_Delay(250);
                position.x = Longueur_ecran/3-10;
                position.y = 250;
                SDL_BlitSurface(Txtfacef1,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(250);
                position.x = Longueur_ecran/2-10;
                position.y = 250;
                SDL_BlitSurface(Txtfacef2,NULL,window,&position);
                SDL_Flip(window);
                SDL_Delay(250);
                position.x = (Longueur_ecran/3)*2-10;
                position.y = 250;
                SDL_BlitSurface(Txtfacef3,NULL,window,&position);
                SDL_Flip(window);


                //if else determinant si les trois dés forment une paire, brelan ou 421,ou encore si rien n'arrive, avec un affichage écrit aprés determination du coup effectué en dessous des dés
                if ((dface1 == dface2) && (dface2 == dface3)&&(dface3 == dface1)) {
                position.x = Longueur_ecran/2-200;
                position.y = Hauteur_ecran/2;
                SDL_BlitSurface(Brelantxt,NULL,window,&position);
                C1 = C1+dface1+dface2+dface3;
                SDL_Flip(window);
                      }
                else if ((dface1 == dface2) || (dface2 == dface3) ||(dface3 == dface1)) {
                position.x = Longueur_ecran/2-200;
                position.y = Hauteur_ecran/2;
                SDL_BlitSurface(pairestxt,NULL,window,&position);
                C1 = C1+2;
                SDL_Flip(window);
                }
                else if (((dface1==4)||(dface2==4)||(dface3==4))&&((dface1==2)||(dface2==2)||(dface3==2))&&((dface1==1)||(dface2==1)||(dface3==1))){
                position.x = Longueur_ecran/2-200;
                position.y = Hauteur_ecran/2;
                SDL_BlitSurface(JACKPOTtxt,NULL,window,&position);
                C1 = C1+20;
                SDL_Flip(window);
                }


                else {
                position.x = Longueur_ecran/2-200;
                position.y = Hauteur_ecran/2;
                SDL_BlitSurface(rientxt,NULL,window,&position);
                SDL_Flip(window);

                }
                cpt++;


                //switch permettant qui permet au tableau des scores d'afficher la valeur tiré au X lancé (1-5 pour le P1 et 5-10 pour le P2) et de determiner le score total de chacun des deux joueurs
                switch(cpt) {
                case 1 :
                sprintf(V1,"  1:    %d", C1);
                fprintf(Resume,"premier tirage du P1 :   %d \n", C1);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+20;
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c1 = TTF_RenderText_Solid(police, V1, couleurPolice);
                SDL_BlitSurface(c1,NULL,window,&position);
                CTotal = CTotal+C1;
                SDL_Flip(window);
                break;

                 case 2 :
                sprintf(V1,"  2:   %d", C1);
                fprintf(Resume,"deuxieme tirage du P1 :  %d \n", C1);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+40;
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c2 = TTF_RenderText_Solid(police, V1, couleurPolice);
                SDL_BlitSurface(c2,NULL,window,&position);
                CTotal = CTotal+C1;
                SDL_Flip(window);
                break;

                 case 3 :
                sprintf(V1,"  3:   %d", C1);
                fprintf(Resume,"troisième tirage du P1 : %d \n", C1);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+60;
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c3 = TTF_RenderText_Solid(police, V1, couleurPolice);
                SDL_BlitSurface(c3,NULL,window,&position);
                CTotal = CTotal+C1;
                SDL_Flip(window);
                break;

                 case 4 :
                sprintf(V1,"  4:   %d", C1);
                fprintf(Resume,"quatrième tirage du P1 : %d \n", C1);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+80;
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c4 = TTF_RenderText_Solid(police, V1, couleurPolice);
                SDL_BlitSurface(c4,NULL,window,&position);
                CTotal = CTotal+C1;
                SDL_Flip(window);
                break;

                case 5 :
                sprintf(V1,"  5:   %d", C1);
                fprintf(Resume,"cinquiéme tirage du P1 : %d \n", C1);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+100;
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c5 = TTF_RenderText_Solid(police, V1, couleurPolice);
                SDL_BlitSurface(c5,NULL,window,&position);
                CTotal = CTotal+C1;
                SDL_Flip(window);
                fprintf(Resume,"|----------------------|\n");
                break;

                case 6 :
                sprintf(V1,"  1:     %d", C1);
                fprintf(Resume,"premier tirage du P2 :   %d \n", C1);
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c6 = TTF_RenderText_Solid(police, V1, couleurPolice);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+20;
                SDL_BlitSurface(c6,NULL,window,&position);
                Ctotal2 = Ctotal2+C1;
                SDL_Flip(window);
                break;
                case 7 :
                sprintf(V1,"   2:    %d", C1);
                fprintf(Resume,"deuxiéme tirage du P2 :  %d \n", C1);
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c7 = TTF_RenderText_Solid(police, V1, couleurPolice);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+40;
                SDL_BlitSurface(c7,NULL,window,&position);
                Ctotal2 = Ctotal2+C1;
                SDL_Flip(window);
                break;
                case 8 :
                sprintf(V1,"    3:   %d", C1);
                fprintf(Resume,"troisiéme tirage du P2 : %d \n", C1);
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c8 = TTF_RenderText_Solid(police, V1, couleurPolice);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+60;
                SDL_BlitSurface(c8,NULL,window,&position);
                Ctotal2 = Ctotal2+C1;
                SDL_Flip(window);
                break;
                case 9 :
                sprintf(V1,"    4:   %d", C1);
                fprintf(Resume,"quatriéme tirage du P2 : %d \n", C1);
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c9 = TTF_RenderText_Solid(police, V1, couleurPolice);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+80;
                SDL_BlitSurface(c9,NULL,window,&position);
                Ctotal2 = Ctotal2+C1;
                SDL_Flip(window);
                break;
                case 10 :
                sprintf(V1,"    5:   %d", C1);
                fprintf(Resume,"cinquiéme tirage du P2 : %d \n", C1);
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                c10 = TTF_RenderText_Solid(police, V1, couleurPolice);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+100;
                SDL_BlitSurface(c10,NULL,window,&position);
                Ctotal2 = Ctotal2+C1;
                SDL_Flip(window);
                break;
                }
                //affichage des scores finaux
                sprintf(V1,"  Total:   %d", CTotal);
                police = TTF_OpenFont("Bebas-Regular.ttf", 20);
                ctotal = TTF_RenderText_Solid(police, V1, couleurPolice);
                position.x = Longueur_ecran/10+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+120;
                SDL_BlitSurface(ctotal,NULL,window,&position);
                SDL_Flip(window);
                sprintf(V1,"    Total:   %d", Ctotal2);
                ctotal2 = TTF_RenderText_Solid(police, V1, couleurPolice);
                position.x = (Longueur_ecran/3)*2+50;
                position.y = Hauteur_ecran/2-Hauteur_ecran/5+120;
                SDL_BlitSurface(ctotal2,NULL,window,&position);
                SDL_Flip(window);
                }

                //quand les joueurs ont lancé leurs 10 coups, l'écran affichera donc les scores finaux , le gagnant et finira le jeu avec un txt résumant celle-ci dans le dossier.
                 if (cpt == 10) {
                if (CTotal>Ctotal2) {
                    police = TTF_OpenFont("Bebas-Regular.ttf", 50);
                    position.x = 0;
                    position.y = 0;
                    SDL_BlitSurface(background,NULL,window,&position);
                    position.x = Longueur_ecran/2-200;
                    position.y = Hauteur_ecran/2-150;
                    SDL_BlitSurface(Resultat,NULL,window,&position);
                    SDL_Delay(1000);
                    sprintf(V1,"    Total:   %d", CTotal);
                    SDL_Color couleurPolice = {255, 0, 0};
                    ctotal = TTF_RenderText_Solid(police, V1, couleurPolice);
                    position.x = Longueur_ecran/10;
                    position.y = Hauteur_ecran/2-150+100;
                    SDL_BlitSurface(ctotal,NULL,window,&position);
                    sprintf(V1,"    Total:   %d", Ctotal2);
                    ctotal2 = TTF_RenderText_Solid(police, V1, couleurPolice);
                    position.x = (Longueur_ecran/3)*2;
                    position.y = Hauteur_ecran/2-150+100;
                    SDL_BlitSurface(ctotal2,NULL,window,&position);
                    position.x = Longueur_ecran/2-220;
                    position.y = Hauteur_ecran/2+50;
                    SDL_BlitSurface(P1win,NULL,window,&position);
                    SDL_Flip(window);
                    fprintf(Resume,"|----------------------|\n", CTotal ,Ctotal2);
                    fprintf(Resume,"Total des deux scores :P1vsP2\n", C1);
                    fprintf(Resume,"%d vs %d\n\n\n\n\n", CTotal ,Ctotal2);
                    fprintf(Resume,"Gagnant : Joueur 1\n ");
                    fprintf(Resume,"%Merci d'avoir joué a mon jeu ^^", CTotal ,Ctotal2);
                    fclose(Resume);
                }
                else if (CTotal == Ctotal2)
                    {
                    police = TTF_OpenFont("Bebas-Regular.ttf", 50);
                    position.x = 0;
                    position.y = 0;
                    SDL_BlitSurface(background,NULL,window,&position);
                    position.x = Longueur_ecran/2-200;
                    position.y = Hauteur_ecran/2-150;
                    SDL_BlitSurface(Resultat,NULL,window,&position);
                    SDL_Delay(1000);
                    sprintf(V1,"    Total:   %d", CTotal);
                    SDL_Color couleurPolice = {255, 0, 0};
                    ctotal = TTF_RenderText_Solid(police, V1, couleurPolice);
                    position.x = Longueur_ecran/10;
                    position.y = Hauteur_ecran/2-150+100;
                    SDL_BlitSurface(ctotal,NULL,window,&position);
                    sprintf(V1,"    Total:   %d", Ctotal2);
                    ctotal2 = TTF_RenderText_Solid(police, V1, couleurPolice);
                    position.x = (Longueur_ecran/3)*2;
                    position.y = Hauteur_ecran/2-150+100;
                    SDL_BlitSurface(ctotal2,NULL,window,&position);
                    position.x = Longueur_ecran/2-50;
                    position.y = Hauteur_ecran/2+50;
                    SDL_BlitSurface(Egalite,NULL,window,&position);
                    SDL_Flip(window);
                    fprintf(Resume,"|----------------------|\n", CTotal ,Ctotal2);
                    fprintf(Resume,"Total des deux scores :P1vsP2\n", C1);
                    fprintf(Resume,"%d vs %d\n\n\n\n\n", CTotal ,Ctotal2);
                    fprintf(Resume,"Gagnant : Auncun! une égalité\n ");
                    fprintf(Resume,"%Merci d'avoir joué a mon jeu ^^", CTotal ,Ctotal2);
                    fclose(Resume);
                    }
                    else if(CTotal < Ctotal2)
                    {
                    police = TTF_OpenFont("Bebas-Regular.ttf", 50);
                    position.x = 0;
                    position.y = 0;
                    SDL_BlitSurface(background,NULL,window,&position);
                    position.x = Longueur_ecran/2-200;
                    position.y = Hauteur_ecran/2-150;
                    SDL_BlitSurface(Resultat,NULL,window,&position);
                    SDL_Flip(window);
                    SDL_Delay(1000);
                    sprintf(V1,"    Total:   %d", CTotal);
                    SDL_Color couleurPolice = {255, 0, 0};
                    ctotal = TTF_RenderText_Solid(police, V1, couleurPolice);
                    position.x = Longueur_ecran/10;
                    position.y = Hauteur_ecran/2-150+100;
                    SDL_BlitSurface(ctotal,NULL,window,&position);
                    sprintf(V1,"    Total:   %d", Ctotal2);
                    ctotal2 = TTF_RenderText_Solid(police, V1, couleurPolice);
                    position.x = (Longueur_ecran/3)*2;
                    position.y = Hauteur_ecran/2-150+100;
                    SDL_BlitSurface(ctotal2,NULL,window,&position);
                    position.x = Longueur_ecran/2-220;
                    position.y = Hauteur_ecran/2+50;
                    SDL_BlitSurface(P2win,NULL,window,&position);

                    SDL_Flip(window);
                    fprintf(Resume,"|----------------------|\n", CTotal ,Ctotal2);
                    fprintf(Resume,"Total des deux scores :P1vsP2\n", C1);
                    fprintf(Resume,"%d vs %d\n\n\n\n\n", CTotal ,Ctotal2);
                    fprintf(Resume,"Gagnant : Joueur 2\n ");
                    fprintf(Resume,"%Merci d'avoir joué a mon jeu ^^\n", CTotal ,Ctotal2);
                    fclose(Resume);

                    }
                    position.x = 50;
                    position.y = Hauteur_ecran-Hauteur_ecran/4+Hauteur_ecran/30-20;
                    SDL_BlitSurface(Quitter,NULL,window,&position);
                    SDL_Flip(window);
                }
break;
                }


                }
                }


      }










