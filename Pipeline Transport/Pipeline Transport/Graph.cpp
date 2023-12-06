#include <set>
#include <unordered_set>

#include "Data.h"
#include "Graph.h"

Graph::Graph(Data& data) : edges(data.getEdges()) {
	std::set<int> vert;
	for (const auto& [id, edge] : edges) {
		vert.insert(edge.start);
		vert.insert(edge.end);
	}
	for (int i : vert) {
		vertices.push_back(i);
	}
	V = vertices.size();
	adj.resize(V, std::vector<bool>(V, false));

	for (auto& [id, edge] : edges) {
		int i = getIndex(vertices, edge.start);
		int j = getIndex(vertices, edge.end);
		adj[i][j] = true;
	}
}

int Graph::getValue(std::vector<int> arr, int index) {
	return arr[index];
}

int Graph::getIndex(std::vector<int> arr, int value) {
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] == value) {
			return i;
		}
	}
}

bool Graph::hasCycle(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& recStack) const {
	visited.insert(vertex);

	for (const auto& [pipe_id, edge] : edges) {
		if (edge.start == vertex) {
			recStack.insert(vertex);
		}
		else if (edge.end == vertex) {
			if (recStack.find(edge.end) != recStack.end()) {
				recStack.erase(vertex);
				return true;
			}
		}
	}

	return false;
}

bool Graph::isDAG() const {
	std::unordered_set<int> visited;
	std::unordered_set<int> recStack;

	for (const auto& [pipe_id, edge] : edges) {
		int vertex = edge.start;
		if (visited.find(vertex) == visited.end() && hasCycle(vertex, visited, recStack)) {
			return false;
		}
	}

	return true;
}

void Graph::dfs(int v, std::vector<bool>& visited, std::vector<int>& order) {
	visited[v] = true;

	for (int u = 0; u < adj[v].size(); u++) {
		if (adj[v][u] && !visited[u]) {
			dfs(u, visited, order);
		}
	}

	order.push_back(getValue(vertices, v));
}

std::vector<int> Graph::topologicalSort() {
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