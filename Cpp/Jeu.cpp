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
#include "..\Entete\Cartes.h"
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

void INT_CHAR (char tabE[],int x,int * i)
	{
		char Tampon[5]="0000";
		int j,h;

		if(x<10 && x>-1)
		{
		sprintf(Tampon,"000%d",x);
		}
		else if(x<100 && x>9)
		{
		sprintf(Tampon,"00%d",x);
		}
		else if(x<1000 && x>99)
		{
		sprintf(Tampon,"0%d",x);
		}
		else if(x<10000 && x>999)
		{
		sprintf(Tampon,"%d",x);
		}

		for(j=*i,h=0;j<*i+4;j++,h++)
		{
		tabE[j]=Tampon[h];
		}
		*i=*i+4;
	}

void CHAR_INT (char tabR[],int* x,int i)
{
	char Tampon[5]="0000";
	long valeur;

	memcpy(&Tampon[0],&tabR[i],4*sizeof(char));
	
	valeur = strtol(Tampon, NULL, 10);
	*x= (int) valeur;
}

bool jeu(struct Element_Affiche Liste_Elements[],SDL_Surface* Ecran,SOCKET sock_Player1,SOCKET sock_Player2)
{
	//Buffer d'envoi reception
	char Buffer[1336];

	SDL_Event event;

	int first,end=0,err,i;
	bool Close=false,CloseAll=false;
	int * case_envois=&i;
	srand((time(NULL)));		//init random

	first=(rand()%1);
	//first=0;

	if(first==0)
	{
		err = send(sock_Player1,"0001",5,0);
		err = send(sock_Player2,"0002",5,0);

	}
	else if(first==1)
	{
		err = send(sock_Player2,"0001",5,0);
		err = send(sock_Player1,"0002",5,0);
	}

	while(Close==false)
	{
		if(first==0)
		{
			err = recv(sock_Player1,Buffer,sizeof(Buffer),0);
			Buffer[1335]='\0';
			err = send(sock_Player2,Buffer,sizeof(Buffer),0);
			CHAR_INT(Buffer,&end,360);
			if(end==1)
			{
				end=0;
				first=1;
				printf("J2\n");
			}
			if(strcmp(Buffer,"close")==0)
			{
				Close=true;
			}
		}
		else if(first==1)
		{
			err = recv(sock_Player2,Buffer,sizeof(Buffer),0);
			Buffer[1335]='\0';
			err = send(sock_Player1,Buffer,sizeof(Buffer),0);
			CHAR_INT(Buffer,&end,360);
			if(end==1)
			{
				end=0;
				first=0;
				printf("J1\n");
			}
			if(strcmp(Buffer,"close")==0)
			{
				Close=true;
			}
		}
		printf("\n%s\n",Buffer);
		for(i=0;i<1336;i++)
		{
			Buffer[i]='0';
		}

		
		SDL_PollEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT://quitter le programme croix
			CloseAll=Close=true;
			break;
		case SDL_MOUSEMOTION://faire resortir le bontont si on passe sa souri dessus
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

		case SDL_MOUSEBUTTONUP://action à effectuer en fonction du bouton
			if(event.motion.x>1189 && event.motion.x<1391 && event.motion.y>649 && event.motion.y<691) //fermeture du réseau
			{
				printf("Closing...\n");
				closesocket(sock_Player1);
				closesocket(sock_Player2);
				WSACleanup();
				Close=true;
			}
			if(event.motion.x>9 && event.motion.x<211 && event.motion.y>699 && event.motion.y<741)
			{
				CloseAll=Close=true;
			}
			break;


		Parametrage_Transparence_Elements_Affichage (Liste_Elements,5,100);
		Parametrage_Transparence_Elements_Affichage (Liste_Elements,4,100);

		Affichage (Liste_Elements,Ecran,NB_Element_Permanent,0);
		}
	
	}
	return CloseAll;
}
