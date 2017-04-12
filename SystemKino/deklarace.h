#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define	rada	10//pocet rad
#define sedadlo 18	//pocet sedadel

typedef	bool sedadla [rada][sedadlo];

//struct str_projekce
//{
//	int ID,trvani,jazyk, p_sal;
//	unsigned short int p_sal;//cislo promitaciho salu
//	char nazev_f[60],zanr[20];
//	struct time
//	{
//		int minuta, hodina;
//	}cas;
//	struct date
//	{
//		int den;
//		int mesic;
//		int rok;		
//	}datum;
//};