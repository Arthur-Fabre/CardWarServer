#include <stdio.h>

#include "..\Entete\Cartes.h"

void Remplir_Carte(struct Cartes Carte_numero[])
{
	//Init_Cartes (&Carte_numero[n] (0-39),"Nom_de_la_carte",[Numero_Carte](1-40),[Point_Mana],[Point_Vie],[Point_Attaque],[Numero_Sort],[Numero_Passif],[Mort toujours à false],[Image_carte]"Images/Cartes/exemple.bmp");
	/*Liste Sorts:
					Attaque		|		Passif
				1)				|	2)
				3)				|	4)
				5)				|	6)
	*/
	
	//Mana 0
	Init_Cartes (&Carte_numero[0],"Nom_de_la_carte",1,1,10,1,5,2,false,"Images/Cartes/exemple.bmp");
	//Mana 1

	//Mana 2

	//Mana 3

	//Mana 4

	//Mana 5

	//Mana 6

	//Mana 7

	//Mana 8

	//Mana 9

	//Mana 10

}

void Init_Cartes (struct Cartes * Carte,char* Nom,int Numero_Carte,int Mana,int Vie,int Attaque,int Sort_de_la_Carte,int Passif_de_la_Carte,bool Mort,char* Image_de_la_Carte)
{
	Carte->Nom=Nom;
	Carte->Numero_Carte=Numero_Carte;
	Carte->Mana=Mana;
	Carte->Vie=Vie;
	Carte->Attaque=Attaque;
	Carte->Sort_de_la_Carte=Sort_de_la_Carte;
	Carte->Passif_de_la_Carte=Passif_de_la_Carte;
	Carte->Mort=Mort;
	Carte->Image_de_la_Carte=Image_de_la_Carte;

}