#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

#include "..\include\SDL.h"		//Bibliotèque SDL (Affichage)

#include "..\Entete\Affichage.h"

SDL_Surface * Init_Fenetre(int largeur, int hauteur, int nb_bits, char * nom_fenetre)	//Init_Fenetre : Configure le mode video avec largeur, hauteur : dimensions de l'écran nb_bits : nombre de bits par pixel nom_fenetre
{
    SDL_Surface * screen = NULL;
	// Appel automatique de la fonction SDL_Quit() à la fin du programme pour décharger proprement SDL
    atexit(SDL_Quit);
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) return NULL;
    SDL_WM_SetCaption(nom_fenetre , NULL); // Initialise le nom de la fenêtre
    screen = SDL_SetVideoMode( largeur , hauteur , nb_bits , SDL_DOUBLEBUF|SDL_ANYFORMAT|SDL_HWSURFACE);
    return screen;
}


void Initialisation_Elements_Affichage (struct Element_Affiche Elements_numero[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *Ma_Surface=NULL;
	Remplir_Elements (&Elements_numero[0],"Fond",Ma_Surface=NULL,"Images/Menu/Fond_Menu.bmp",0,0);
	Remplir_Elements (&Elements_numero[1],"connecte_1",Ma_Surface=NULL,"Images/Menu/BConnecte.bmp",650,426);
	Remplir_Elements (&Elements_numero[2],"connecte_2",Ma_Surface=NULL,"Images/Menu/BConnecte.bmp",650,500);
	Remplir_Elements (&Elements_numero[3],"BFermer_Serveur",Ma_Surface=NULL,"Images/Menu/BFermer_Serveur.bmp",1190,650);
	Remplir_Elements (&Elements_numero[4],"BOuvrir_Serveur",Ma_Surface=NULL,"Images/Menu/BOuvrir_Serveur.bmp",1190,700);
	Remplir_Elements (&Elements_numero[5],"BOptions",Ma_Surface=NULL,"Images/Menu/BOptions.bmp",10,650);
	Remplir_Elements (&Elements_numero[6],"BQuitter",Ma_Surface=NULL,"Images/Menu/BQuitter.bmp",10,700);
	Remplir_Elements (&Elements_numero[7],"FOptions",Ma_Surface=NULL,"Images/Menu/FOptions.bmp",500,320);
	Remplir_Elements (&Elements_numero[8],"BRetour",Ma_Surface=NULL,"Images/Menu/BRetour.bmp",510,573);
	Remplir_Elements (&Elements_numero[9],"Text",Ma_Surface=NULL,"Images/Menu/texte.bmp",588,403);

}

void Remplir_Elements (struct Element_Affiche * Element_Affiche,char* Nom,SDL_Surface *Ma_Surface,char* Image,int X,int Y)
{
	Element_Affiche->Nom= Nom;
	Element_Affiche->Ma_Surface = Ma_Surface;
	Element_Affiche->Image= Image;
	Element_Affiche->X= X;
	Element_Affiche->Y= Y;
	Element_Affiche->Ma_Surface=SDL_LoadBMP(Image);
	SDL_SetColorKey(Element_Affiche->Ma_Surface, SDL_SRCCOLORKEY, SDL_MapRGB(Element_Affiche->Ma_Surface->format, 255, 255, 0));
}

void Parametrage_Image_Elements_Affichage (struct Element_Affiche Elements_numero[],int numero_case,char* Image)
{
	Elements_numero[numero_case].Ma_Surface=SDL_LoadBMP(Image);
	SDL_SetColorKey(Elements_numero[numero_case].Ma_Surface, SDL_SRCCOLORKEY, SDL_MapRGB(Elements_numero[numero_case].Ma_Surface->format, 255, 255, 0));

}

void Parametrage_Transparence_Elements_Affichage (struct Element_Affiche Elements_numero[],int numero_case,int Opacite)
{
	SDL_SetAlpha(Elements_numero[numero_case].Ma_Surface, SDL_SRCALPHA, Opacite);
}

void Affichage(struct Element_Affiche Elements_numero[],SDL_Surface *Ecran,int NB_Case,int Choix)
{
	int i;
	for(i=0;i<NB_Case;i++)
	{
	Blitter_Surface(Elements_numero[i].Ma_Surface, Ecran, Elements_numero[i].X, Elements_numero[i].Y);
	}
	
	if(Choix==1)
	{
		Blitter_Surface(Elements_numero[7].Ma_Surface, Ecran, Elements_numero[7].X, Elements_numero[7].Y);
		Blitter_Surface(Elements_numero[8].Ma_Surface, Ecran, Elements_numero[8].X, Elements_numero[8].Y);
		Blitter_Surface(Elements_numero[9].Ma_Surface, Ecran, Elements_numero[9].X, Elements_numero[9].Y);
	}

	SDL_Flip(Ecran);
	Sleep(10);
}


void Blitter_Surface(SDL_Surface * source, SDL_Surface * destination, int X_offset, int Y_offset) // Blitter_Surface : Applique la surface (image) source sur la surface (image) destination aux coordonnées (X_offset, Y_offset)
{
    SDL_Rect offset;
	offset.x = X_offset;
    offset.y = Y_offset;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void Clear_Element (struct Element_Affiche Elements_numero[],int NB_case)
{
	int i;
	for(i=0;i<NB_case;i++)
	{
		SDL_FreeSurface(Elements_numero[i].Ma_Surface);
	}
}