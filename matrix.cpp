#include "matrix.hpp"
#include "bellman.hpp"
static int s_infinity = 1000000;

//konstruktor
MatrixGraph::MatrixGraph(int t_V, double t_density)
	: Graph(t_V, static_cast<int>(t_density * t_V * (t_V - 1)), t_density),
	  matrix(std::make_unique<std::unique_ptr<int[]>[]>(t_V))
{

	for (int i = 0; i < iloscW; ++i)
	{

		matrix[i] = std::make_unique<int[]>(t_V);
		for (int j = 0; j < iloscW; ++j)
		{

			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = s_infinity;
		}
	}
}

void MatrixGraph::WypelnienieGrafu(const bool t_allowLoops) const
{

	if (iloscG == 1)
	{
		for (int i = 0; i < iloscW; ++i)
		{
			for (int j = 0; j < iloscW; ++j)
			{
				if (i != j)
				{
					int fweight = rand() % 20;
					while (fweight == 0)
					{

						fweight = rand() % 20;
					}
					matrix[i][j] = fweight;
				}
			}
		}
	}
	else
	{

		int fedge = iloscK;

		while (fedge)
		{

			int rowNode = rand() % iloscW;
			int columnNode = rand() % iloscW;

			if (matrix[rowNode][columnNode] == 0 || matrix[rowNode][columnNode] == s_infinity)
			{

				int fweight = rand() % 20;
				while (fweight == 0)
				{

					fweight = rand() % 20;
				}

				if (rowNode != columnNode)
				{

					matrix[rowNode][columnNode] = fweight;
					--fedge;
				}
				else if (t_allowLoops)
				{

					matrix[rowNode][columnNode] = fweight;
					--fedge;
				}
			}
		}
	}
}

const int MatrixGraph::CzytanieZPliku()
{

	std::ifstream file("plikwejsciowy.txt");
	if (!file.is_open())
	{
		throw "nie otwarto pliku";
		return 1;
	}

	int start, source, destination, weight;
	file >> iloscK >> iloscW >> start;
	matrix = std::make_unique<std::unique_ptr<int[]>[]>(iloscW);

	for (int i = 0; i < iloscW; ++i)
	{

		matrix[i] = std::move(std::make_unique<int[]>(iloscW));
		for (int j = 0; j < iloscW; ++j)
		{

			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = s_infinity;
		}
	}

	for (int iEdge = 0; iEdge < iloscK; ++iEdge)
	{
		file >> source >> destination >> weight;
		matrix[source][destination] = weight;
	}
	file.close();
	return start;
}