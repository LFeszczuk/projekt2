#pragma once

#include "graph.hpp"

#include <cstdlib>
#include <memory>

class MatrixGraph : public Graph //dziedziczy po grafie
{

	std::unique_ptr<std::unique_ptr<int[]>[]> matrix;

public:
	void WypelnienieGrafu(const bool allowLoops) const override;
	const int CzytanieZPliku() override;

	//zwraca wartosc komorki
	const int &getWeight(int t_row, int t_column) const { return matrix[t_row][t_column]; }

	explicit MatrixGraph(int t_V, double t_density);
	MatrixGraph() : Graph(){};
};