#pragma once

#include <unordered_map>
#include <set>
#include "Data.h"


class Graph {

public:

	std::set<int> vertexs;
	std::unordered_map<int, Edge> edges;
	std::vector<std::vector<bool>> adj;
	size_t V = 0;

	Graph(std::unordered_map<int,Edge>& edges) : edges(edges){
		for (const auto& [id, edge] : edges) {
			vertexs.insert(edge.source);
			vertexs.insert(edge.drain);
		}
		V = vertexs.size();
		adj.resize(V, std::vector<bool>(V,false));

		for (auto& [id, edge] : edges) {
			int i = edge.source;
			int j = edge.drain;
			adj[i][j] = true;
		}
	}

	bool hasCycle(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& recStack) const {
		visited.insert(vertex);
		recStack.insert(vertex);

		for (const auto& [pipe_id, edge] : edges) {
			if (edge.source == vertex) {
				if (recStack.find(edge.drain) != recStack.end()) {
					return true;
				}
				if (visited.find(edge.drain) == visited.end() && hasCycle(edge.drain, visited, recStack)) {
					return true;
				}
			}
		}

		recStack.erase(vertex);
		return false;
	}

	bool isDAG() const {
		std::unordered_set<int> visited;
		std::unordered_set<int> recStack;

		for (const auto& [pipe_id, edge] : edges) {
			int vertex = edge.source;
			if (visited.find(vertex) == visited.end() && hasCycle(vertex, visited, recStack)) {
				return false;
			}
		}

		return true;
	}
	
	void dfs(int v, std::vector<bool>& visited, std::vector<int>& order) {
		visited[v] = true;

		for (int u = 0; u < adj[v].size();u++) {
			if (adj[v][u] && !visited[u]) {
				dfs(u, visited, order);
			}
		}

		order.push_back(v); 
	}

	std::vector<int> topologicalSort() {
		if (edges.empty()) {
			std::cout << "The graph is empty. You can't do topological sorting" << std::endl;
			return {};
		}
		if (!isDAG()) {
			std::cout << "The graph contains a cycle. You can't do topological sorting" << std::endl;
			return {};
		}

		int V = adj.size();
		std::vector<bool> visited(V, false);
		std::vector<int> order;

		for (int v = 0; v < V; ++v) {
			if (!visited[v]) {
				dfs(v, visited, order);
			}
		}

		std::reverse(order.begin(), order.end());

		return order;
	}
		
};