#include "list.hpp"

void ListGraph::addEdge(int t_guardNumber, int t_number, int t_weight, int t_flag) const
{

	edge[t_flag].dest = t_number;
	edge[t_flag].source = t_guardNumber;
	edge[t_flag].weight = t_weight;
}

bool ListGraph::detectIfExist(int t_guardNumber, int t_nodeNumber) const
{

	for (int i = 0; i < iloscK; ++i)
	{ //petla po krawedziach

		if (edge[i].dest == t_nodeNumber && edge[i].source == t_guardNumber)
			return true;
	}
	return false;
}

void ListGraph::WypelnienieGrafu(const bool t_allowLoops) const
{
	//dla grafu pelnego
	if (iloscG == 1)
	{

		int fflag = 0;
		for (int i = 0; i < iloscW; ++i)
		{ //dla kazdego poczatku
			for (int j = 0; j < iloscW; ++j)
			{ //i dla kazdego konca

				if (i != j)
				{ //unikanie tworzenia petli

					int fweight = rand() % 20;
					while (fweight == 0)
					{ //waga rozna od 0

						fweight = rand() % 20;
					}
					addEdge(i, j, fweight, fflag++);
				}
			}
		}
	}
	else
	{ //pozostale gestosci

		int fedge = 0;
		while (fedge < iloscK)
		{

			int guardNode = rand() % iloscW;
			int nodeNode = rand() % iloscW;
			if (!detectIfExist(guardNode, nodeNode))
			{

				int fweight = rand() % 20;
				while (fweight == 0)
				{

					fweight = rand() % 20;
				}

				if (guardNode != nodeNode)
					addEdge(guardNode, nodeNode, fweight, fedge++);
				else if (t_allowLoops)
					addEdge(guardNode, nodeNode, fweight, fedge++);
			}
		}
	}
}

const int ListGraph::CzytanieZPliku()
{

	std::ifstream file("Wejsc.txt");
	if (!file.is_open())
	{
		throw "plik nie otwarty";
		return 1;
	}

	int start, source, destination, weight;
	file >> iloscK >> iloscW >> start;
	edge = new Edge[iloscK];

	for (int iEdge = 0; iEdge < iloscK; ++iEdge)
	{

		file >> source >> destination >> weight;
		addEdge(source, destination, weight, iEdge);
	}
	file.close();
	return start; //zwraca wezel poczotkowy
}
