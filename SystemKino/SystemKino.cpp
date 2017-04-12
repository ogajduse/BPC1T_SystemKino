// SystemKino.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "deklarace.h"
#include "Modul.h"

int main()
{
	printf("Vitejte v rezervacnim systemu multikina\n");
	int volba=-1;//pouzit enum?
	do
	{
		system("cls");
		printf("Stisknete:\n1: Koupe vstupenek\n2: Nahled na nabidku filmu\n3: Nahled na hlediste\n4: Vytvoreni nove projekce\n0: Konec programu\n\nVolba: ");
		fflush(stdin);		
		scanf_s("%d", &volba);	//nacte volbu
		system("cls");     //vymaze obrazovku
		switch (volba)
		{
		case 0:
			return 0;
			break;
		case 1:
			vytvorRezervaci();
			break;
		case 2:
			prectiVsechnyProjekce();
			getchar();
			getchar();
			break;
		case 3:
			nahledHlediste();
			
			break;
		case 4:
			vytvorProjekci();
			break;
		default:
			break;
		}
	} while (volba!=0);
    return 0;
}

