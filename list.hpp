#pragma once

#include "graph.hpp"

//krawedz o wadze
struct Edge
{

	//waga zdrodlo i koniec krawedzi
	int source, dest, weight;
};

//graf zaimplementowany za pomoca listy
class ListGraph : public Graph
{

	Edge *edge;

public:
	void WypelnienieGrafu(const bool allowLoops) const override;
	const int CzytanieZPliku() override;

	const Edge *getStruct() const { return edge; }
	//Wpisuje wartosci do krawedzi
	void addEdge(int t_guardNumber, int t_number, int t_weight, int flag) const;
	bool detectIfExist(int t_guardNumber, int t_nodeNumber) const; //wykrywa czy istnieje polaczenie
	explicit ListGraph(int t_V, double t_density)
		: Graph(t_V, static_cast<int>(t_density * t_V * (t_V - 1)), t_density),
		  edge(new Edge[static_cast<int>(t_density * t_V * (t_V - 1))]) {}
	ListGraph() : Graph(){};
	~ListGraph() { delete[] edge; }
};
