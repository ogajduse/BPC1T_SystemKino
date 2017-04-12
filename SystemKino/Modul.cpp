#include "stdafx.h"
#include "Modul.h"
#include "deklarace.h"

void ulozSedadla(struct obsazeni uloz,int ID_projekce)
{
	char ch;
	char str[20];
	_snprintf_s(str, sizeof(str), "%s%d%s", "./Hlediste/", ID_projekce, ".txt");//utvoreni stringu slouzici jako cesta k souboru
	FILE * soubor;
	fopen_s(&soubor, str, "w");//otevreni souboru pro zapis sedadel
	for (int i = 0; i < rada; i++)//zapis sedadel do souboru
	{
		for (int j = 0; j < sedadlo; j++)
		{			
			if (uloz.hlediste[i][j])
				putc('o', soubor);
			else
				putc('v', soubor);
		}
		ch = putc(';', soubor);
	}
	fclose(soubor);//uzavreni souboru
}

struct obsazeni nactiHlediste(int ID_projekce)//nacte hlediste ze souboru, nacte do struktury a vrati strukturu 
{
	char str[20];
	_snprintf_s(str,sizeof(str), "%s%d%s","./Hlediste/",ID_projekce,".txt");
	struct obsazeni nacteno;
	nacteno.hlediste[0][10] = true;
	FILE *mapasedadel_o;
	int navrat_fce = fopen_s(&mapasedadel_o, str, "r");
	char c = getc(mapasedadel_o);
	int i = 0, j = 0;//promene pro urceni pozice v poli
	while (c != EOF)
	{
		//putchar(c); //vytsk na obrazovku
		if (c == 'v')
		{
			nacteno.hlediste[i][j++] = false;
		}
		else if (c == 'o')
		{
			nacteno.hlediste[i][j++] = true;
		}
		else
		{
			i++;
			j = 0;
		}

		c = getc(mapasedadel_o);//ziskani dalsiho znaku

	}
	fclose(mapasedadel_o); //zavreni
	return nacteno;
}

void vypisHlediste(struct obsazeni nacteni)
{
	//vypis toho, co se nacetlo ze souboru
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	//Ulozeni aktualnich atributu
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	
	for (int i = 0; i < rada; i++)//vypisovani volnych a obsazenych sedadel
	{//napsat, kde je platno
		SetConsoleTextAttribute(hConsole, saved_attributes);
		if (i == 0)
			printf("\tP  r  o  m  i  t  a  c  i   p  l  a  t  n  o\n");
		printf("%d\t", i + 1);
		for (int j = 0; j < sedadlo; j++)
		{
			if (nacteni.hlediste[i][j])
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				printf("%d ", j + 1);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				printf("%d ", j + 1);
			}
		}
		printf("\n\n");
	}
	SetConsoleTextAttribute(hConsole, saved_attributes);//puvodni atributy fontu v konzoli
}

struct obsazeni resetSedadel()//vrací vychozi nastaveni sedadel(strukturou)
{
	sedadla obsazeni_sedadel =	{	{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false },
									{ false,true,false,true,false,false,false,false,false,false,false,false,false,false,true,true,true,false },
									{ true,false,false,true,false,false,false,false,false,false,false,false,false,true,true,true,true,true },
									{ false,false,true,true,false,false,true,false,false,true,true,true,false,false,true,true,false,false },
									{ false,true,false,false,false,true,true,true,true,true,true,true,true,false,true,true,false,false },
									{ false,false,false,true,false,true,true,true,true,true,true,true,true,true,true,false,false,false },
									{ false,false,false,true,false,false,false,false,true,true,false,true,false,false,false,false,false,false },
									{ false,true,false,false,true,true,true,false,false,true,true,true,true,false,false,false,false,false },
									{ false,true,false,true,false,true,true,false,true,true,true,false,true,true,false,false,false,false },
									{ false,false,true,true,false,true,true,true,true,true,false,true,false,true,true,true,true,true } };	
	struct obsazeni a;
	for (int i = 0; i < rada; i++)//zapis sedadel do souboru
	{
		for (int j = 0; j < sedadlo; j++)
		{
			a.hlediste[i][j] = obsazeni_sedadel[i][j];
		}
	}
	
	return a;
}

int vytvorProjekci() //vytvori novy zaznam do souboru s projekcemi
{
	struct str_projekce nprojekce;
	int spravne;
	do
	{
		printf("ZADAVANI NOVE PROJEKCE\n\n");
		printf("Zadejte nazev filmu: ");
		getchar();
		fflush(stdin);
		gets_s(nprojekce.nazev_f);
		zadejDatum(nprojekce.datum.den,nprojekce.datum.mesic,nprojekce.datum.rok);
		zadejCas(nprojekce.cas.hodina,nprojekce.cas.minuta);
		zadejSal(nprojekce.p_sal);
		printf("\nZadejte delku trvani filmu [min]: ");
		fflush(stdin);
		scanf_s("%d", &nprojekce.trvani);//udelat misto tohoto radku fci?
		printf("\nZadejte zanr filmu: ");
		fflush(stdin);
		getchar();
		gets_s(nprojekce.zanr);
		zadejJazyk(nprojekce.jazyk);
		zadejCenu(nprojekce.cena.detsky,nprojekce.cena.dospely,1);//zadani ceny pro deti
		zadejCenu(nprojekce.cena.detsky, nprojekce.cena.dospely, 2);//zadani ceny pro dospele
		//kontrola zadanych dat
		printf("\nZadany nasledujici udaje:\n\nNazev filmu:\t%s\nZanr filmu:\t%s\nJazyk filmu:\t%d\nDelka:\t\t%d\nCas projekce:\t%d:%d\nDatum:\t\t%d. %d. %d\nSal:\t\t%d\nCena deti:\t%d\nCena dospeli:\t%d\n",nprojekce.nazev_f,nprojekce.zanr,nprojekce.jazyk,nprojekce.trvani,nprojekce.cas.hodina,nprojekce.cas.minuta,nprojekce.datum.den,nprojekce.datum.mesic,nprojekce.datum.rok,nprojekce.p_sal,nprojekce.cena.detsky,nprojekce.cena.dospely);
		do
		{
			printf("\nJsou tyto udaje zadany spravne?\nANO (1), NE (0) ");
			fflush(stdin);
			scanf_s("%d", &spravne);
		}while(spravne<0 || spravne>1);		
	}while(spravne==0);
	nprojekce.ID=posledni_ID();//zjistit posledni ID
	//ulozit zadane udaje do souboru
	FILE * soubor;
	fopen_s(&soubor, "./projekce.txt", "a");//otevreni souboru pro zapis
	//1§90§1§1§22§58§3§2§2016§40§80~Kuky se vraci$Pohadka
	fprintf(soubor,"%d§%d§%d§%d§%d§%d§%d§%d§%d§%d§%d~%s$%s\n",nprojekce.ID,nprojekce.trvani,nprojekce.jazyk,nprojekce.p_sal,nprojekce.cas.hodina,nprojekce.cas.minuta,nprojekce.datum.den,nprojekce.datum.mesic,nprojekce.datum.rok,nprojekce.cena.detsky,nprojekce.cena.dospely,nprojekce.nazev_f,nprojekce.zanr);
	fclose(soubor);
	ulozSedadla(resetSedadel(), nprojekce.ID);//ulozeni mapy sedadel pro danou projekci
	incrID();//inkrementace ID
	printf("\nZaznam uspesne vytvoren, stisknete enter");
	getchar();
	getchar();
	return 0;
}

int zadejCenu(int &detsky, int &dospely, int volba)//funkce vraci hodnotu odkazem, modifikuje hodnotu z funkce, kde byla zavolana
{
	if (volba == 1)
	{
	cena_dets:
		printf("\nZadejte cenu listku pro deti [CZK]: ");
		fflush(stdin);
		scanf_s("%d", &detsky);
		if (detsky>-1 && detsky<1000)
			return 0;
		else
		{
			printf("Spatne zadani, zadejte cenu v rozpeti 0 - 999.\n");
			goto cena_dets;
		}
	}
	if (volba==2)
	{
		cena_dos:
			printf("\nZadejte cenu listku pro dospele [CZK]: ");
			fflush(stdin);
			scanf_s("%d", &dospely);
			if (dospely>-1 && dospely<1000)
				return 0;
			else
			{
				printf("Spatne zadani, zadejte cenu v rozpeti 0 - 999.\n");
				goto cena_dos;
			}
	}
	return -1;
}

int zadejDatum(int &den, int &mesic, int &rok)//funkce vraci hodnotu odkazem, modifikuje hodnotu z funkce, kde byla zavolana
{
	datum:
	printf("\nZadejte datum ve foramtu DD/MM/RRRR: ");
	fflush(stdin);
	scanf_s("%d/%d/%d", &den,&mesic,&rok);
	if ((den > 0 && den < 32) && (mesic>0 && mesic<13) && (rok>2015))
		return 0;
	else
	{
		printf("Spatne zadani, zadejte datum znovu.\n");
		goto datum;
	}
}

int zadejCas(int &hodina, int &minuta)//funkce vraci hodnotu odkazem, modifikuje hodnotu z funkce, kde byla zavolana
{
	n_cas:
	printf("\nZadejte cas ve foramtu HH/MM: ");
	fflush(stdin);
	scanf_s("%d/%d", &hodina,&minuta);
	if ((hodina>-1 && hodina<24) && (minuta>-1 && minuta<60))
		return 0;
	else
	{
		printf("Spatne zadani, zadejte cas znovu.\n");
		goto n_cas;
	}
}

int zadejSal(int &prom_sal)//fce vyzve uzivatele k zadani promitaciho salu
{//funkce vraci hodnotu odkazem, modifikuje hodnotu z funkce, kde byla zavolana
	zad_sal:
	printf("\nVyberte promitaci sal, ve kterem se bude promitat\nVolba\t promitaci sal\n1\tA1\n2\tA2\n3\tB1\n4\tB2\n\nVolba: ");
	//enum numbPromitaciSal {A1,A2,B1,B2};
	int celk_pocet_salu = 4;//pocet salu v kine celkove
	int n_sal=-1;//promenna pro cislo salu
	fflush(stdin);
	scanf_s("%d",&n_sal);
	if (n_sal>0 && n_sal<=celk_pocet_salu)//test, zda je zadany sal v kine>0 a <= nez celkovy pocet
	{
		prom_sal=n_sal;
		return 0;
	}
	else
	{
		printf("Spatne zadani, stisknete enter a opakujte volbu");
		fflush(stdin);
		getchar();
		goto zad_sal;
	}
}

int zadejJazyk(int &jaz)//fce vyzve uzivatele k zadani jazyku filmu,vraci cislo jazyku
{//funkce vraci hodnotu odkazem, modifikuje hodnotu z funkce, kde byla zavolana
	zad_jaz:
	printf("\nVyberte jazyk, ve kterem se bude promitat\nVolba\t jazyk\n1\tCZ\n2\tEN\n3\tDE\n4\tFR\n\nVolba: ");
	//enum?
	int celk_pocet_jazyku = 4;//pocet moznych jazyku
	int n_jaz=-1;//promenna pro jazyk
	fflush(stdin);
	scanf_s("%d",&n_jaz);
	if (n_jaz>0 && n_jaz<=celk_pocet_jazyku)//test, zda je zadany sal v kine>0 a <= nez celkovy pocet
	{
		jaz=n_jaz;
		return 0;
	}
	else
	{
		printf("Spatne zadani, stisknete enter a opakujte volbu");
		fflush(stdin);
		getchar();
		goto zad_jaz;
	}
}

int posledni_ID()//Zjisti pocet zaznamu, resp. pocet ID
{
	int i;
	FILE * zaznamy;
	fopen_s(&zaznamy, "pocet_projekci.txt", "r");
	fscanf_s (zaznamy, "%d", &i);
	fclose(zaznamy);
	return i;
}

int incrID()
{
	int i = posledni_ID();
	i++;
	FILE * zaznamy_w;
	fopen_s(&zaznamy_w, "pocet_projekci.txt", "w");
	fprintf_s (zaznamy_w, "%d", i);
	fclose(zaznamy_w);
	return i;
}

int prectiVsechnyProjekce()
{
	struct str_projekce rprojekce;
	rprojekce.ID = -1;
	FILE * soubor;
	fopen_s(&soubor, "./projekce.txt", "r");//otevreni souboru pro cteni
	for (int i = 1; i < posledni_ID(); i++) 
	{
		fscanf_s(soubor, "%d§%d§%d§%d§%d§%d§%d§%d§%d§%d§%d~", &rprojekce.ID, &rprojekce.trvani, &rprojekce.jazyk, &rprojekce.p_sal, &rprojekce.cas.hodina, &rprojekce.cas.minuta, &rprojekce.datum.den, &rprojekce.datum.mesic, &rprojekce.datum.rok, &rprojekce.cena.detsky, &rprojekce.cena.dospely);
		char c;
		int posun = 0;
		c = fgetc(soubor);
		while (c != '$')
		{
			rprojekce.nazev_f[posun++] = c;
			c = fgetc(soubor);
		}
		c = fgetc(soubor);
		rprojekce.nazev_f[posun] = '\0';//ukonceni retezce
		posun = 0;//reset posunu v poli pro dalsi cyklus
		while (c != '\n')
		{
			rprojekce.zanr[posun++] = c;
			c = fgetc(soubor);
		}
		rprojekce.zanr[posun] = '\0';//ukonceni retezce
		printf("\n\nID filmu:\t%d\nNazev filmu:\t%s\nZanr filmu:\t%s\nJazyk filmu:\t%d\nDelka:\t\t%d\nCas projekce:\t%d:%d\nDatum:\t\t%d. %d. %d\nSal:\t\t%d\nCena deti:\t%d\nCena dospeli:\t%d\n", rprojekce.ID,rprojekce.nazev_f, rprojekce.zanr, rprojekce.jazyk, rprojekce.trvani, rprojekce.cas.hodina, rprojekce.cas.minuta, rprojekce.datum.den, rprojekce.datum.mesic, rprojekce.datum.rok, rprojekce.p_sal, rprojekce.cena.detsky, rprojekce.cena.dospely);
	}
	fclose(soubor);
	return 0;
}

struct str_projekce vratProjekci(int zad_ID)//parser z textoveho souboru precte projekce a vrati jedinecnou projekci
{
	struct str_projekce rprojekce;
	rprojekce.ID = -1;
	FILE * soubor;
	fopen_s(&soubor, "./projekce.txt", "r");//otevreni souboru pro cteni
	char c;
	for (int i = 1; i < INT_MAX;i++)
	{
		fscanf_s(soubor, "%d§%d§%d§%d§%d§%d§%d§%d§%d§%d§%d~", &rprojekce.ID, &rprojekce.trvani, &rprojekce.jazyk, &rprojekce.p_sal, &rprojekce.cas.hodina, &rprojekce.cas.minuta, &rprojekce.datum.den, &rprojekce.datum.mesic, &rprojekce.datum.rok, &rprojekce.cena.detsky, &rprojekce.cena.dospely);
		if (rprojekce.ID!=zad_ID)
		{
			do
			{
				c = fgetc(soubor);
			} while (c != '\n');
			continue;//dalsi iterace
		}		
		int posun = 0;
		c = fgetc(soubor);
		while (c != '$')
		{
			rprojekce.nazev_f[posun++] = c;
			c = fgetc(soubor);
		}
		c = fgetc(soubor);
		rprojekce.nazev_f[posun] = '\0';//ukonceni retezce
		posun = 0;//reset posunu v poli pro dalsi cyklus
		while (c != '\n')
		{
			rprojekce.zanr[posun++] = c;
			c = fgetc(soubor);
		}
		rprojekce.zanr[posun] = '\0';//ukonceni retezce
		break;//ukonceni cyklu
	}
	fclose(soubor);
	return rprojekce;
}

void nahledHlediste()
{
	int volba = 0;
	do
	{
		system("cls");
		printf("Chcete zobrazit nabidku filmu nebo rovnou zadate ID?\n1: Zobrazit nabidku\n2: Zadat ID\n0: Zpet do hlavni nabidky\n\t\tVolba: ");
		getchar();
		scanf_s("%d",&volba);
	} while (volba!=1 && volba!=2 && volba!=0); 
	if (volba == 0)
		return;
	if (volba==1)
	{
		system("cls");
		prectiVsechnyProjekce();
		printf("\n\nStisknete ENTER");
		getchar();
		getchar();
	}	
	do
	{
		system("cls");
		printf("Zadejte ID filmu: ");
		getchar();
		fflush(stdin);
		scanf_s("%d", &volba);
	} while (volba < 1 || volba > (posledni_ID()-1));
	system("cls");
	struct str_projekce a = vratProjekci(volba);
	printf("%s\n", a.nazev_f);
	vypisHlediste(nactiHlediste(volba));
	printf("\n\nStisknete ENTER");
	getchar();
	getchar();
}

int vytvorRezervaci()
{
	//printf("");
	int ID, typ, rad,sed,dalsiObjednavka=0,soucet=0,pocet=0;
	bool dobre = true,nacist=true;
	printf("KOUPIT VSTUPENKY\n\n");
	printf("Zadejte ID filmu, na nejz chcete koupit vstupenky\nID: ");
	do
	{
		if (!dobre)
			printf("\nSpatne zadadni, opakujte zadani.\nID: ");
		getchar();
		fflush(stdin);
		scanf_s("%d", &ID);
		dobre=false;
	} while (ID < 1 || ID >(posledni_ID() - 1));
	struct str_projekce projekce = vratProjekci(ID);
	struct obsazeni mapa = nactiHlediste(ID);
	do
	{
		printf("\nObjednavate vstupenky na film  %s\n\nDospely nebo dite?\n1: Dospely\n2: Dite\n\nVolba: ", projekce.nazev_f);
		dobre = true;
		do
		{
			if (!dobre)
				printf("\nSpatne zadadni, opakujte zadani.\nVolba: ");
			getchar();
			fflush(stdin);
			scanf_s("%d", &typ);
			dobre = false;
		} while (typ != 1 && typ != 2);
		do
		{
			printf("Vyberte sedadlo:\n");
			if (nacist)	//pokud je vybrane misto v sale obsazene, nasledujici prikaz se neprovede
				vypisHlediste(nactiHlediste(ID));	//vypis mapy sedadel
			printf("\n\nRada:");
			dobre = true;
			do
			{
				if (!dobre)
					printf("\nSpatne zadadni, opakujte zadani.\nRada: ");
				getchar();
				fflush(stdin);
				scanf_s("%d", &rad);
				dobre = false;
			} while (rad < 1 || rad > rada);
			printf("\n\nSedadlo:");
			dobre = true;
			do
			{
				if (!dobre)
					printf("\nSpatne zadadni, opakujte zadani.\nSedadlo: ");
				getchar();
				fflush(stdin);
				scanf_s("%d", &sed);
				dobre = false;
			} while (sed < 1 || sed > sedadlo);
			if (mapa.hlediste[rad - 1][sed - 1] == false)//test na volne sedadlo
			{
				printf("Toto misto je jiz obsazene, vyberte jine.\n\n");
				dobre = false; nacist = false;
				continue;
			}
			dobre = true;
		} while (dobre == false);
		mapa.hlediste[rad - 1][sed - 1] = false;
		ulozSedadla(mapa, ID);
		if (typ == 1)
			soucet += projekce.cena.dospely;
		if (typ == 2)
			soucet += projekce.cena.detsky;
		pocet++;
		printf("\nChcete na film %s koupit dalsi vstupenku?\n1: Ano\n0: Ne\n\nVolba: ",projekce.nazev_f);
		dobre = true;
		nacist = true;
		do
		{
			if (!dobre)
				printf("\nSpatne zadadni, opakujte zadani.\nVolba: ");
			getchar();
			fflush(stdin);
			scanf_s("%d", &dalsiObjednavka);
			dobre = false;
		} while (dalsiObjednavka != 1 && dalsiObjednavka != 0);
	} while (dalsiObjednavka == 1);
	printf("\n\nSoucet cen %d objednanych vstupenek: %d [CZK]\n\n",pocet,soucet);
	getchar();
	getchar();
	return 0;
}