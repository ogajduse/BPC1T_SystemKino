#include "deklarace.h"
struct obsazeni
{
	sedadla hlediste;
};
struct str_projekce
{
	int ID, trvani, jazyk, p_sal;//cislo promitaciho salu
	char nazev_f[60], zanr[20];
	struct time
	{
		int minuta, hodina;
	}cas;
	struct date
	{
		int den, mesic, rok;
	}datum;
	struct price
	{
		int detsky,dospely;
	}cena;
};


void ulozSedadla(struct obsazeni uloz, int ID_projekce);
struct obsazeni resetSedadel();
struct obsazeni nactiHlediste(int ID_projekce);
void vypisHlediste(struct obsazeni nacteni);
int vytvorProjekci();
int zadejCenu(int &detsky, int &dospely, int volba);
int zadejDatum(int &den, int &mesic, int &rok);
int zadejCas(int &hodina, int &minuta);
int zadejSal( int &prom_sal);
int zadejJazyk(int &jaz);
int posledni_ID();
int incrID();
int prectiVsechnyProjekce();
struct str_projekce vratProjekci(int ID);
void nahledHlediste();
int vytvorRezervaci();


