//inclusion des bibliotèque 
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include<winsock2.h>			//Bibliotèque resaux
#pragma comment(lib,"ws2_32.lib")


#include "..\include\SDL.h"		//Bibliotèque SDL (Affichage)
#include "..\include\SDL_ttf.h"	//Bibliotèque SDL (Affichage_texte)

#include "..\Entete\Base.h"		//Sous fonctions
#include "..\Entete\Affichage.h"
#include "..\Entete\jeu.h"



struct Reseau
{
	int Port;
	SOCKET sock_attente;
	SOCKET sock_Player1;
	SOCKET sock_Player2;
	SOCKADDR_IN csin;
};


#define _CRT_SECURE_NO_DEPRECATE

bool Affichage_Options(struct Reseau*, struct Element_Affiche[], SDL_Surface*,SDL_Event);


//Début programme principal//
int main(int argc, char *argv[])
{
	//////////////////////////////////////////////////////////////////////////
	//Initialisation information résaux
	WSADATA wsa; 
    WSAStartup(MAKEWORD(2,0),&wsa);
	struct Reseau reseau;
	reseau.Port=25565;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//Initialisation information sdl
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *Ecran=NULL;

	SDL_Event event;
	bool Close=false,Player1=false,Player2=false;

	//Init fenètre
	Ecran = Init_Fenetre(1400, 800, 32, "CardWars Serveur");


	struct Element_Affiche Liste_Elements[NB_Element_Affichable];
	Initialisation_Elements_Affichage (Liste_Elements);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//Init jeux
	bool Start=false;

	
	
	while(Close==false)
	{
		//Test Menu
		SDL_PollEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT://quitter le programme croix
			Close=true;
			break;
		case SDL_MOUSEMOTION://faire resortir le bontont si on passe sa souri dessus
			if(event.motion.x>9 && event.motion.x<211 && event.motion.y>649 && event.motion.y<691)
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,5,255);
			}
			else
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,5,200);
			}
			if(event.motion.x>9 && event.motion.x<211 && event.motion.y>699 && event.motion.y<741)
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,6,255);
			}
			else
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,6,200);
			}
			if(event.motion.x>1189 && event.motion.x<1391 && event.motion.y>649 && event.motion.y<691)
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,3,255);
			}
			else
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,3,200);
			}
			if(event.motion.x>1189 && event.motion.x<1391 && event.motion.y>699 && event.motion.y<741)
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,4,255);
			}
			else
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,4,200);
			}
			break;
		case SDL_MOUSEBUTTONUP://action à effectuer en fonction du bouton
			if(event.motion.x>1189 && event.motion.x<1391 && event.motion.y>649 && event.motion.y<691) //fermeture du réseau
			{
				printf("Closing...\n");
				Player1=false;
				Player2=false;
				WSACleanup();
			}
			if(event.motion.x>1189 && event.motion.x<1391 && event.motion.y>699 && event.motion.y<741)
			{
				Parametrage_Image_Elements_Affichage (Liste_Elements,4,"Images/Menu/BRecherche.bmp");
				Affichage (Liste_Elements,Ecran,NB_Element_Permanent,0);

				//procédure reseaux
				
				int len;
				int err=0;
				reseau.csin.sin_family=AF_INET;
				reseau.csin.sin_addr.s_addr=htonl(INADDR_ANY);
				reseau.csin.sin_port=htons(reseau.Port);
				reseau.sock_attente = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
				if (reseau.sock_attente == INVALID_SOCKET)
				return -1;
				if (bind(reseau.sock_attente,(SOCKADDR*)&reseau.csin,sizeof(reseau.csin)) == SOCKET_ERROR)
				return -2;
				printf("Listen...\n");
				if (listen(reseau.sock_attente, 1) == SOCKET_ERROR)
				return -3;
				len = sizeof(reseau.csin);
				printf("Attente client...\n");

				reseau.sock_Player1 = accept(reseau.sock_attente, (SOCKADDR *)&reseau.csin, &len);
				Player1=true;
				Parametrage_Image_Elements_Affichage (Liste_Elements,1,"Images/Menu/BConnecte.bmp");
				Affichage (Liste_Elements,Ecran,NB_Element_Permanent,0);
				
				reseau.sock_Player2 = accept(reseau.sock_attente, (SOCKADDR *)&reseau.csin, &len);
				Player2=true;
				Parametrage_Image_Elements_Affichage (Liste_Elements,1,"Images/Menu/BConnecte.bmp");
				Affichage (Liste_Elements,Ecran,NB_Element_Permanent,0);
				
				if (reseau.sock_Player1==INVALID_SOCKET)
				return -4;

				printf("Connection 2 ok\n");
				printf("GameStarted\n");

				Start=true;
				Parametrage_Image_Elements_Affichage (Liste_Elements,4,"Images/Menu/BOuvrir_Serveur.bmp");
				//fin de procédure de connexion demarage du jeux


			}

			if(event.motion.x>9 && event.motion.x<211 && event.motion.y>649 && event.motion.y<691)
			{
				event.motion.x=0;
				event.motion.y=0;
				Close=Affichage_Options(&reseau,Liste_Elements,Ecran,event);
			}
			if(event.motion.x>9 && event.motion.x<211 && event.motion.y>699 && event.motion.y<741)
			{
				Close=true;
			}
			break;
		}

		///preparation de l'affichage

		if(Player1==true)
				{Parametrage_Image_Elements_Affichage (Liste_Elements,1,"Images/Menu/BConnecte.bmp");}
		else	{Parametrage_Image_Elements_Affichage (Liste_Elements,1,"Images/Menu/BDeconnecte.bmp");}

		if(Player2==true)
				{Parametrage_Image_Elements_Affichage (Liste_Elements,2,"Images/Menu/BConnecte.bmp");}
		else	{Parametrage_Image_Elements_Affichage (Liste_Elements,2,"Images/Menu/BDeconnecte.bmp");}

		Affichage (Liste_Elements,Ecran,NB_Element_Permanent,0);
		
		if(Start==true)
		{
		int err;
		//char Donnee_T[6]="start";
		//err = send(reseau.sock_Player1,Donnee_T,sizeof(Donnee_T),0);
		err = send(reseau.sock_Player1,"start",6,0);
		Sleep(5000);
		err = send(reseau.sock_Player2,"start",6,0);
		Close=jeu(Liste_Elements,Ecran,reseau.sock_Player1,reseau.sock_Player2);
		Player2=Player1=false;
		}
	}
	

	//fermeture du réseau
	WSACleanup();
	Clear_Element (Liste_Elements,NB_Element_Affichable);
	TTF_Quit();
	SDL_Quit();

	return 0;
}









/////////////////////////////////////////////////////////////////////Fonction secondaire////////////////////////////////////////////////////////////////////////////////////////////


bool Affichage_Options(struct Reseau* reseau,struct Element_Affiche Liste_Elements[],SDL_Surface* Ecran,SDL_Event event)
{
	bool Options=true,Close=false,Fin=false,FinP=false;
	char SPort[7]="25565", SPortVide[7]="      ";
	int i;
	long valeur;
	///////////////////////////////////////////////////////////
	//Initialisation information TTF
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Color TColor = {255, 106, 0};
	TTF_Font *police = TTF_OpenFont("COPRGTB.ttf", 18);
	sprintf(SPort,"%d",reseau->Port);
	Liste_Elements[9].Ma_Surface=TTF_RenderText_Solid(police,SPort,TColor);



	while(Options==true)
	{
		SDL_PollEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT://quitter le programme croix
			Options=false;
			Close=true;
			break;
		case SDL_MOUSEMOTION://faire resortir le bontont si on passe sa souri dessus
			if(event.motion.x>509 && event.motion.x<711 && event.motion.y>572 && event.motion.y<614)
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,8,255);
			}
			else
			{
				Parametrage_Transparence_Elements_Affichage (Liste_Elements,8,200);
			}
			break;
		case SDL_MOUSEBUTTONUP://action à effectuer en fonction du bouton
			if(event.motion.x>509 && event.motion.x<711 && event.motion.y>572 && event.motion.y<614) 
			{
				Options=false;
			}
			else if(event.motion.x>587 && event.motion.x<703 && event.motion.y>403 && event.motion.y<422) 
			{
				memcpy(&SPort[0],&SPortVide[0],6*sizeof(char));
				Liste_Elements[9].Ma_Surface=TTF_RenderText_Solid(police,SPort,TColor);
				Affichage (Liste_Elements,Ecran,NB_Element_Permanent,1);
				for(i=0;FinP==false && i<6;i++)
				{
					Fin=false;
					while(Fin==false)
					{
						SDL_PollEvent(&event);
						switch(event.type)
						{
						case SDL_KEYDOWN:
							switch(event.key.keysym.sym)
							{
							case SDLK_0:
								SPort[i]='0';
								Fin=true;
								break;
							case SDLK_1:
								SPort[i]='1';
								Fin=true;
								break;
							case SDLK_2:
								SPort[i]='2';
								Fin=true;
								break;
							case SDLK_3:
								SPort[i]='3';
								Fin=true;
								break;
							case SDLK_4:
								SPort[i]='4';
								Fin=true;
								break;
							case SDLK_5:
								SPort[i]='5';
								Fin=true;
								break;
							case SDLK_6:
								SPort[i]='6';
								Fin=true;
								break;
							case SDLK_7:
								SPort[i]='7';
								Fin=true;
								break;
							case SDLK_8:
								SPort[i]='8';
								Fin=true;
								break;
							case SDLK_9:
								SPort[i]='9';
								Fin=true;
								break;
							case SDLK_RETURN:
								SPort[i]='\0';
								Fin=true;
								FinP=true;
								break;
							}
							break;
						}
					Sleep(100);
					}
				if(FinP==false && i<5)
				{
					SPort[i+1]='_';
				}
				Liste_Elements[9].Ma_Surface=TTF_RenderText_Solid(police,SPort,TColor);
				Affichage (Liste_Elements,Ecran,NB_Element_Permanent,1);
				} //fin for
				printf("%s\n",SPort);
				valeur = strtol(SPort, NULL, 10);
				reseau->Port= (int) valeur;
				printf("%d\n",reseau->Port);
			}
			break;
		}
		Affichage (Liste_Elements,Ecran,NB_Element_Permanent,1);
	}
	return Close;
}


//////////////////////////reseau////////////////////////////////////////////

