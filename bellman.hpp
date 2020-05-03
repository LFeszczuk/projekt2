#pragma once

#include <chrono>
#include <string>
#include "list.hpp"
#include "matrix.hpp"

//dla listy
double bellmanFord(std::shared_ptr<ListGraph> t_graph, int t_startNode, bool t_printSolution);
// dla macierzy
double bellmanFord(std::shared_ptr<MatrixGraph> t_graph, int t_startNode, bool t_printSolution);