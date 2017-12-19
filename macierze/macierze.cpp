// macierze.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"

using namespace std;
//Tworzy tablice kwadratowa wedle uznania m-> wielkosc, a-> wartosc
float **TworzTablice(int m,int a)
{
	float **tab = new float *[m];

	for (int i = 0; i < m; i++)
	{
		tab[i] = new float[m];
		for (int j = 0; j < m; j++)
		{
			tab[i][j] = (float)a;
		}
	}
	return tab;
}
class dekompozytowanaMacierz
{
public:
	dekompozytowanaMacierz(float **tab, int lenght);
	dekompozytowanaMacierz(int lenght);
	dekompozytowanaMacierz();
	dekompozytowanaMacierz(dekompozytowanaMacierz *zdeko);
	~dekompozytowanaMacierz();
	void PomnozStrassenem(dekompozytowanaMacierz *dekompA, dekompozytowanaMacierz *dekompB);
	void Wypisz();
	float **tabA;
	float **tabB;
	float **tabC;
	float **tabD;
	int half;

	void Wymnoz(dekompozytowanaMacierz *dekompA, dekompozytowanaMacierz *dekompB);
private:
	float **Mnoz(float **tab1, float **tab2, int m);
	float **Dodaj(float **tab1, float **tab2, int m);
	float **Odejmij(float **tab1, float **tab2, int m);
};
dekompozytowanaMacierz::dekompozytowanaMacierz(dekompozytowanaMacierz *zdeko)
{
	half = zdeko->half;
	tabA = new float *[half];
	tabB = new float *[half];
	tabC = new float *[half];
	tabD = new float *[half];
	/*
	for (int i = 0; i < half; i++)
	{
		tabA[i] = new float[half];
		tabB[i] = new float[half];
		tabC[i] = new float[half];
		tabD[i] = new float[half];
	}
	for (int i = 0; i = half; i++)
	{
		for (int j = 0; j = half; j++)
		{
			tabA[i][j] = zdeko->tabA[i][j];
			tabB[i][j] = zdeko->tabB[i][j];
			tabC[i][j] = zdeko->tabC[i][j];
			tabD[i][j] = zdeko->tabD[i][j];
		}
	}
	*/
}
dekompozytowanaMacierz::dekompozytowanaMacierz()
{

}
//podstawowy kontruktor dekomponuje macierz tab na 4 inne o wielkosci lenght
dekompozytowanaMacierz::dekompozytowanaMacierz(float **tab,int lenght)
{ 
	half = lenght / 2;
	tabA = new float *[half];
	tabB = new float *[half];
	tabC = new float *[half];
	tabD = new float *[half];
	for (int i = 0; i < half; i++)
	{
		tabA[i] = new float[half];
		tabB[i] = new float[half];
		tabC[i] = new float[half];
		tabD[i] = new float[half];
	}
	for (int i = 0; i < lenght; i++)
	{
		for (int j = 0; j < lenght; j++)
		{
			if (i < half)
			{
				if (j < half)
				{
					tabA[i][j] = tab[i][j];
				}
				else
				{
					tabB[i][j - half] = tab[i][j];
				}
			}
			else
			{
				if (j < half)
				{
					tabC[i - half][j] = tab[i][j];
				}
				else
				{
					tabD[i - half][j - half] = tab[i][j];
				}
			}
		}
	}
}
//tworzy dekomponowana macierz wypelniana 0 o wielkosci lenght
dekompozytowanaMacierz::dekompozytowanaMacierz(int lenght)
{
	half = lenght / 2;
	tabA = new float *[half];
	tabB = new float *[half];
	tabC = new float *[half];
	tabD = new float *[half];
	for (int i = 0; i < half; i++)
	{
		tabA[i] = new float[half];
		tabB[i] = new float[half];
		tabC[i] = new float[half];
		tabD[i] = new float[half];
	}
	for (int i = 0; i < half; i++)
	{
		for (int j = 0; j < half; j++)
		{
			tabA[i][j] = 0;
			tabB[i][j] = 0;
			tabC[i][j] = 0;
			tabD[i][j] = 0;
		}
	}

}
dekompozytowanaMacierz::~dekompozytowanaMacierz()
{
	delete tabA;
	delete tabB;
	delete tabC;
	delete tabD;

}

void dekompozytowanaMacierz::Wypisz()
{
	cout << "Macierz A: \n" << endl;
	for (int i = 0; i < half; i++)
	{
		for (int j = 0; j < half; j++)
		{
			cout << tabA[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Macierz B: \n" << endl;
	for (int i = 0; i < half; i++)
	{
		for (int j = 0; j < half; j++)
		{
			cout << tabB[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Macierz C: \n" << endl;
	for (int i = 0; i < half; i++)
	{
		for (int j = 0; j < half; j++)
		{
			cout << tabC[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Macierz D: \n" << endl;
	for (int i = 0; i < half; i++)
	{
		for (int j = 0; j < half; j++)
		{
			cout << tabD[i][j] << " ";
		}
		cout << endl;
	}
}
//mnozy dekomponowane macierze z tego pierwszego wzoru
void dekompozytowanaMacierz::Wymnoz(dekompozytowanaMacierz *dekompA, dekompozytowanaMacierz *dekompB)
{
	cout << "Mnoze tablice A" << endl;
	tabA = Dodaj(Mnoz(dekompA->tabA, dekompB->tabA, half), Mnoz(dekompA->tabB, dekompB->tabC, half), half);
	cout << "Mnoze tablice B" << endl;
	tabB = Dodaj(Mnoz(dekompA->tabA,dekompB->tabC,half), Mnoz(dekompA->tabB,dekompB->tabD,half), half);
	cout << "Mnoze tablice C" << endl;
	tabC = Dodaj(Mnoz(dekompA->tabC,dekompB->tabA,half), Mnoz(dekompA->tabD,dekompB->tabC,half), half);
	cout << "Mnoze tablice D" << endl;
	tabD = Dodaj(Mnoz(dekompA->tabC,dekompB->tabB,half), Mnoz(dekompA->tabD,dekompB->tabD,half), half);
}
//tradycyjnie mnozy macieze m -> wielkosc macierzy
float **dekompozytowanaMacierz::Mnoz(float **tab1, float **tab2, int m)
{
	float **tab= TworzTablice(m,0);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < m; k++)
			{
				tab[i][j] += tab1[i][k] * tab2[j][k];
			}
		}
	}
	return tab;
}
//poprostu je dodaje m-> wielkosc
float **dekompozytowanaMacierz::Dodaj(float **tab1, float **tab2, int m)
{
	float **tab = TworzTablice(m,0);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			tab[i][j] = tab1[i][j] + tab2[i][j];
		}
	}
	return tab;
}
//no i odejmuje macierze m->wielkosc
float **dekompozytowanaMacierz::Odejmij(float **tab1, float **tab2, int m)
{
	float **tab = TworzTablice(m, 0);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			tab[i][j] = tab1[i][j] - tab2[i][j];
		}
	}
	return tab;
}
//mnozenie wedlug algorytmu strassena
void dekompozytowanaMacierz::PomnozStrassenem(dekompozytowanaMacierz *dekompA, dekompozytowanaMacierz *dekompB)
{
	float **M1;
	float **M2;
	float **M3;
	float **M4;
	float **M5;
	float **M6;
	float **M7;
	cout << "M1" << endl;
	M1 = Mnoz(Dodaj(dekompA->tabA, dekompA->tabD, half), Dodaj(dekompB->tabA, dekompB->tabD, half), half);
	cout << "M2" << endl;
	M2 = Mnoz(Dodaj(dekompA->tabC,dekompA->tabD,half), dekompB->tabA, half);
	cout << "M3" << endl;
	M3 = Mnoz(dekompA->tabA, Odejmij(dekompB->tabB, dekompB->tabD, half),half);
	cout << "M4" << endl;
	M4 = Mnoz(dekompA->tabD, Odejmij(dekompB->tabC, dekompB->tabA, half), half);
	cout << "M5" << endl;
	M5 = Mnoz(Dodaj(dekompA->tabA, dekompA->tabB, half), dekompB->tabD, half);
	cout << "M6" << endl;
	M6 = Mnoz(Odejmij(dekompA->tabC, dekompA->tabA, half), Dodaj(dekompB->tabA, dekompB->tabB, half), half);
	cout << "M7" << endl;
	M7 = Mnoz(Odejmij(dekompA->tabB, dekompA->tabD, half), Dodaj(dekompB->tabC, dekompB->tabD, half), half);
	cout << "ROBIE MACIERZ C" << endl;
	tabA = Dodaj(Odejmij(Dodaj(M1, M4, half), M5, half), M7, half);
	tabB = Dodaj(M3, M5, half);
	tabC = Dodaj(M2, M4, half);
	tabD = Dodaj(Dodaj(Odejmij(M1, M2, half), M3, half), M6, half);
}
int main()
{   
	auto start = chrono::system_clock::now();
	cout << "Tworze macierz do mnozenia" << endl;
	int m = 4096;
	float **tab2 = TworzTablice(m, 1);
	float **tab = TworzTablice(m,1);
	cout << "Tworze obiekty dekompozytowanaMacierz" << endl;
	dekompozytowanaMacierz *deko1;
	deko1= new dekompozytowanaMacierz(tab, m);
	dekompozytowanaMacierz *deko2;
	deko2=new dekompozytowanaMacierz(tab2, m);
	dekompozytowanaMacierz *deko3;
	deko3=new dekompozytowanaMacierz(m);
	/*
	dekompozytowanaMacierz *tabZdeko11;
	dekompozytowanaMacierz *tabZdeko12;
	dekompozytowanaMacierz *tabZdeko13;
	dekompozytowanaMacierz *tabZdeko14;

	dekompozytowanaMacierz *tabZdeko21;
	dekompozytowanaMacierz *tabZdeko22;
	dekompozytowanaMacierz *tabZdeko23;
	dekompozytowanaMacierz *tabZdeko24;

	dekompozytowanaMacierz *tabZdeko31;
	dekompozytowanaMacierz *tabZdeko32;
	dekompozytowanaMacierz *tabZdeko33;
	dekompozytowanaMacierz *tabZdeko34;

	
	tabZdeko11 = new dekompozytowanaMacierz(deko1->tabA, deko1->half);
	tabZdeko12 = new dekompozytowanaMacierz(deko1->tabB, deko1->half);
	tabZdeko13 = new dekompozytowanaMacierz(deko1->tabC, deko1->half);
	tabZdeko14 = new dekompozytowanaMacierz(deko1->tabD, deko1->half);

	tabZdeko21 = new dekompozytowanaMacierz(deko2->tabA, deko2->half);
	tabZdeko22 = new dekompozytowanaMacierz(deko2->tabB, deko2->half);
	tabZdeko23 = new dekompozytowanaMacierz(deko2->tabC, deko2->half);
	tabZdeko24 = new dekompozytowanaMacierz(deko2->tabD, deko2->half);

	tabZdeko31 = new dekompozytowanaMacierz(deko3->tabA, deko3->half);
	tabZdeko32 = new dekompozytowanaMacierz(deko3->tabB, deko3->half);
	tabZdeko33 = new dekompozytowanaMacierz(deko3->tabC, deko3->half);
	tabZdeko34 = new dekompozytowanaMacierz(deko3->tabD, deko3->half);
	*/

	cout << "Mnoze macierze " << endl;
	auto watch = chrono::system_clock::now();
	deko3->PomnozStrassenem(deko1, deko2);

	/*
	tabZdeko31->PomnozStrassenem(tabZdeko11, tabZdeko21);
	tabZdeko32->PomnozStrassenem(tabZdeko12, tabZdeko22);
	tabZdeko33->PomnozStrassenem(tabZdeko13, tabZdeko23);
	tabZdeko34->PomnozStrassenem(tabZdeko14, tabZdeko24);
	*/
	auto stop = chrono::system_clock::now();
	chrono::duration<double> czas = stop - start;
	chrono::duration<double> czasMnozenia = stop - watch;
	cout << "Mnozenie zajelo: " << czasMnozenia.count() << "s " << endl;
	cout << "Calosc zajela: " << czas.count() << "s " << endl;
	fstream plik;
	plik.open("wynik.txt", ios::app);
	plik << czasMnozenia.count();
	plik << " s\n";
	plik.close();

	//deko3->Wypisz();
	/*
	tabZdeko34->Wypisz();
	tabZdeko34->Wypisz();
	tabZdeko34->Wypisz();
	tabZdeko34->Wypisz();
	*/
	system("pause");

	delete deko1;
	delete deko2;
	delete deko3;

	/*	
	delete tabZdeko11;
	delete tabZdeko12;
	delete tabZdeko13;
	delete tabZdeko14;

	delete tabZdeko21;
	delete tabZdeko22;
	delete tabZdeko23;
	delete tabZdeko24;

	delete tabZdeko31;
	delete tabZdeko32;
	delete tabZdeko33;
	delete tabZdeko34;
	*/
}

