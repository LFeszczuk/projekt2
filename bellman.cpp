#include "bellman.hpp"

static int s_infinity = 1000000;
static int s_neg_infinity = -1000000;

// Funkcja wypisująca do pliku wynik  w postaci serii danych
void Solution(std::string t_pathArr[], int t_dist[], int t_n, int t_startNode)
{

	std::ofstream file("wyniki.txt");

	std::cout << std::string(20, '-') << "\n   FinalSolution\n\n";
	std::cout << "The starting node was -> " << t_startNode << "\n\n";

	file << std::string(20, '-') << "\n   FinalSolution\n\n";
	file << "The starting node was -> " << t_startNode << "\n\n";

	for (int i = 0; i < t_n; ++i)
	{

		if (t_dist[i] == s_neg_infinity)
		{

			file << i << "->"
				 << "-inf\n";
			continue;
		}
		else if (t_dist[i] == s_infinity)
		{
			std::cout << i << "->"
					  << "inf\n";
			file << i << "->"
				 << "inf\n";
			continue;
		}

		else
		{
			std::cout << i << "->" << t_dist[i];
			file << i << "->" << t_dist[i];
		}

		if (i < 10)
		{
			std::cout << "   ";
			file << "   ";
		}
		else if (i < 100)
		{
			std::cout << "  ";
			file << "  ";
		}
		else
		{
			std::cout << " ";
			file << " ";
		}

		if ((t_dist[i] >= 100 && t_dist[i] < 1000) || (-100 > t_dist[i] && t_dist[i] <= -10))
		{

			std::cout << " The shortest path: " << t_pathArr[i] << i;
			file << " The shortest path: " << t_pathArr[i] << i;
		}
		else if (0 <= t_dist[i] && t_dist[i] < 10)
		{

			std::cout << "   The shortest path: " << t_pathArr[i] << i;
			file << "   The shortest path: " << t_pathArr[i] << i;
		}
		else if ((t_dist[i] >= 10 && t_dist[i] < 100) || (-10 < t_dist[i] && t_dist[i] < 0))
		{

			std::cout << "  The shortest path: " << t_pathArr[i] << i;
			file << "  The shortest path: " << t_pathArr[i] << i;
		}
		else
		{

			std::cout << "The shortest path: " << t_pathArr[i] << i;
			file << "The shortest path: " << t_pathArr[i] << i;
		}
		std::cout << std::endl;
		file << std::endl;
	}
	std::cout << std::endl;
	file.close();
}

//bellmanFord dla listy
double bellmanFord(std::shared_ptr<ListGraph> t_graph, int t_startNode, bool t_printSolution)
{

	std::string *storePath = new std::string[t_graph->getV()];

	auto t_start = std::chrono::high_resolution_clock::now();

	int *storeDistance = new int[t_graph->getV()];

	for (int iCell = 0; iCell < t_graph->getV(); ++iCell)
	{

		storeDistance[iCell] = s_infinity;
	}

	storeDistance[t_startNode] = 0;

	for (int i = 1; i < t_graph->getV(); ++i)
	{
		for (int j = 0; j < t_graph->getE(); ++j)
		{

			int u = t_graph->getStruct()[j].source;
			int v = t_graph->getStruct()[j].dest;
			int weight = t_graph->getStruct()[j].weight;

			if (storeDistance[u] + weight < storeDistance[v])
			{
				storeDistance[v] = storeDistance[u] + weight;

				if (t_printSolution)
				{

					storePath[v].clear();
					storePath[v].append(storePath[u] + std::to_string(u) + "->");
				}
			}
		}
	}

	for (int i = 1; i < t_graph->getV(); ++i)
	{
		for (int j = 0; j < t_graph->getE(); ++j)
		{

			int u = t_graph->getStruct()[j].source;
			int v = t_graph->getStruct()[j].dest;
			int weight = t_graph->getStruct()[j].weight;
			if (storeDistance[u] + weight < storeDistance[v])
			{

				if (storeDistance[u] > s_infinity / 2)
					storeDistance[u] = s_infinity;
				else
					storeDistance[v] = s_neg_infinity;
			}
			else if (storeDistance[u] > s_infinity / 2)
				storeDistance[u] = s_infinity;
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now(); //  Koniec CZASU

	// Możliwość wypisania w formie serii danych
	if (t_printSolution)
		Solution(std::move(storePath), std::move(storeDistance), t_graph->getV(), t_startNode);
	delete[] storeDistance;
	delete[] storePath;
	return std::chrono::duration<double, std::milli>(t_end - t_start).count(); // Zwracanie czasu
}

//bellmanFord dla macierzy
double bellmanFord(std::shared_ptr<MatrixGraph> t_graph, int t_startNode, bool t_printSolution)
{

	std::string *storePath = new std::string[t_graph->getV()];

	auto t_start = std::chrono::high_resolution_clock::now();

	int *storeDistance = new int[t_graph->getV()];

	for (int iCell = 0; iCell < t_graph->getV(); ++iCell)
	{

		storeDistance[iCell] = s_infinity;
	}

	storeDistance[t_startNode] = 0;

	for (int i = 1; i < t_graph->getV(); ++i)
	{
		for (int j = 0; j < t_graph->getV(); ++j)
		{
			for (int w = 0; w < t_graph->getV(); ++w)
			{

				int u = j;
				int v = w;
				int weight = t_graph->getWeight(j, w);
				if (storeDistance[u] + weight < storeDistance[v])
				{

					storeDistance[v] = storeDistance[u] + weight;
					if (t_printSolution)
					{

						storePath[v].clear();
						storePath[v].append(storePath[u] + std::to_string(u) + "->");
					}
				}
			}
		}
	}
	for (int i = 1; i < t_graph->getV(); ++i)
	{
		for (int j = 0; j < t_graph->getV(); ++j)
		{
			for (int w = 0; w < t_graph->getV(); ++w)
			{

				int u = j;
				int v = w;
				int weight = t_graph->getWeight(j, w);
				if (storeDistance[u] + weight < storeDistance[v])
				{

					if (storeDistance[u] > s_infinity / 2)
						storeDistance[u] = s_infinity;
					else if (weight == s_infinity)
						continue;
					else
						storeDistance[v] = s_neg_infinity;
				}
				else if (storeDistance[u] > s_infinity / 2)
					storeDistance[u] = s_infinity;
			}
		}
	}
	auto t_end = std::chrono::high_resolution_clock::now();

	if (t_printSolution)
		Solution(std::move(storePath), std::move(storeDistance), t_graph->getV(), t_startNode);
	delete[] storeDistance;
	delete[] storePath;
	return std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
