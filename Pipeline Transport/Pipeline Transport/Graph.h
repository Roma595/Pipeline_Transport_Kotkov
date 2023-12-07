#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include "Data.h"


class Graph {

public:

	Graph(Data& data);
	int getValue(std::vector<int> arr, int index);
	int getIndex(std::vector<int> arr, int value);

	bool hasCycle(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& recStack) const;
	bool isDAG() const;
	void dfs(int v, std::vector<bool>& visited, std::vector<int>& order);
	std::vector<int> topologicalSort();

private:
	std::vector<int> vertices;
	std::unordered_map<int, Edge> edges;
	std::vector<std::vector<bool>> adj;
	size_t V = 0;
		
};