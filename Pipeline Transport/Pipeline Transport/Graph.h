#pragma once

#include <unordered_map>
#include <set>
#include <vector>
#include "Data.h"
#include "Utilities.h"

#include<queue>
#include<vector>


class Graph {

public:

    size_t V = 0;
    std::vector<std::vector<Edge>> adj_list;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> weights;
    std::vector<int> distances;

    Graph(Data& data);
    int getValue(std::vector<int> arr, int index);
    int getIndex(Data& data, int value);

    bool hasCycle(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& recStack) const;
    bool isDAG() const;
    void dfs(int v, std::vector<bool>& visited, std::vector<int>& order);
    std::vector<int> topologicalSort();

    bool bfs(std::vector<std::vector<int>>& rGraph, int s, int t, std::vector<int>& parent);

    int MaxFlow(Data& data, int s, int t);
   
    int shortest_path(Data& data, int start, int end);

    bool find_edge(int start, int end) {
        for (auto& [id, edge] : edges) {
            if (edge.start == start && edge.end == end) {
                return true;
            }
            if (edge.start == end && edge.end == start) {
                return true;
            }
        }
        return false;
    }


private:
	std::vector<int> vertices;
	std::unordered_map<int, Edge> edges;
	std::vector<std::vector<bool>> adj;

};