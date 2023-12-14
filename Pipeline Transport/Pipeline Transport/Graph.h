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
   
    int shortest_path(Data& data, int start, int end) {

        int s = getIndex(data, start);
        int n = adj_list.size();
        distances.assign(data.getStations().size(), INT_MAX);
        distances[s] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
       
        pq.push({ 0, s });

        while (!pq.empty()) {
            int u = pq.top().second;
            //int u = getIndex(data, ue);
            int d = pq.top().first;
            pq.pop();

            if (d > distances[u]) continue;

            for (Edge& e : adj_list[u]) {
                int ve = e.end;
                int v = getIndex(data, ve);
                int w = e.weight;
                if (w!=0 && distances[u] + w < distances[v]) {
                    distances[v] = distances[u] + w;
                    pq.push({ distances[v], v });
                }
            }
        }
        int index = getIndex(data, end);
        for (int i = 0; i < distances.size(); i++) {
            if (i == index) {
                return distances[i];
            }
        }
    }


private:
	std::vector<int> vertices;
	std::unordered_map<int, Edge> edges;
	std::vector<std::vector<bool>> adj;

};