#include <time.h>

#include "bellman.hpp"

//Argumenty funkcji:
// Pętle , tablica wierzcholkow , tablica gestosci
template <typename T>
std::ostream &tests(std::ostream &file, int (&vertTab)[5], double (&densTab)[4], int loops)
{

	for (double density : densTab)
	{
		for (int vertices : vertTab)
		{
			double sum = 0;
			for (int i = 0; i < loops; i++)
			{

				std::shared_ptr<T> graph = std::make_shared<T>(vertices, density); //tworzenie grafu
				int startNode = rand() % vertices;								   //startowy wezel

				graph->WypelnienieGrafu(true); //graf z mozliwoscia petl

				sum += bellmanFord(std::move(graph), startNode, false); // bellman ford zwraca czas wykonania możliwość wydruku w formie serii danych
				std::cout << (i * 100 / loops) + 1 << "%"
						  << "\r" << std::flush;
			}

			file << sum << std::endl
				 << vertices << " Wierzchołki jestescie skonczone!" << std::endl;
		}
		std::cout << "\n"
				  << density << " Gestosci jestescie skonczone!\n"
				  << std::endl;
	}
	file << "\n";
	return file;
}
template <typename T>
std::ostream &Czytanie()
{
	std::shared_ptr<T> graph;
	int startNode = graph->CzytanieZPliku();
	bellmanFord(std::move(graph), startNode, false);
}
int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	int vertTab[5] = {10, 50, 75, 100, 125};  //tablica wierzcholkow
	double densTab[4] = {0.25, 0.5, 0.75, 1}; //tablica gestosci
	int loops = 100;						  // liczba powtorzen

	std::ofstream file("Wyniki.txt");
	if (!file.is_open())
	{

		std::cerr << "plik sie nie otwiera" << std::flush;
		return 1;
	}
	int choice, start;
	std::string nameoffile;
	std::cout << "Wybierz opcje" << std::endl;
	std::cout << "1. Wykonywanie testu" << std::endl;
	std::cout << "2. wczytywanie z pliku" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
	{
		tests<ListGraph>(file, vertTab, densTab, loops); //wykonywanie dla listy
		std::cout << "Listy jestescie skonczone!" << std::endl;
		tests<MatrixGraph>(file, vertTab, densTab, loops); //wykonywanie dla Macierzy
		std::cout << "Macierze jestescie skonczone!" << std::endl;
		file.close();
	}
	case 2:
	{
		Czytanie<ListGraph>();
		Czytanie<MatrixGraph>();
		break;
	}
	default:
	{
		std::cout << "Brak takiej opcji" << std::endl;
		break;
	}
	}
	return 0;
}