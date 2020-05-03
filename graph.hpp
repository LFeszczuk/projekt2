#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>

//Wszystkie opisy klas w plikach hpp
//Klasa tworzaca pojecie grafu
class Graph
{

protected:
	int iloscW, iloscK; //ilosc Wierzcholkow i krawedzi
	double iloscG;		//gestosc grafu

public:
	const int &getV() const { return iloscW; }						//zwraca ilosc wierzcholkow
	const int &getE() const { return iloscK; }						//zwraca ilosc krawedzi
	virtual void WypelnienieGrafu(const bool allowLoops) const = 0; //wypelnienie grafu
	virtual const int CzytanieZPliku() = 0;							//czytanie z pliku
	//konstruktor grafu
	virtual ~Graph(){};
	explicit Graph(int t_V, int t_E, double t_density) : iloscW(t_V), iloscK(t_E), iloscG(t_density) {}
	Graph(){};
};