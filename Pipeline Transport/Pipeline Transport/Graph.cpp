#include <set>
#include <unordered_set>

#include "Data.h"
#include "Graph.h"
#include "Utilities.h"

Graph::Graph(Data& data) : edges(data.getEdges()) {
	std::set<int> vert;
	for (const auto& [id, edge] : edges) {
		vert.insert(edge.start);
		vert.insert(edge.end);
	}
	for (int i : vert) {
		vertices.push_back(i);
	}
	V = data.getStations().size();
	adj.resize(V, std::vector<bool>(V, false));
	adj_list.resize(V);
	weights.resize(V, std::vector<int>(V, INT_MAX));
	capacity.resize(V, std::vector<int>(V, 0));
	distances.resize(V);

	for (auto& [id, edge] : edges) {
		int i = getIndex(data, edge.start);
		int j = getIndex(data, edge.end);
		adj[i][j] = true;
		edge.weight = data.getPipes().at(id).getWeigth();
		edge.capacity = data.getPipes().at(id).getCapacity();
		adj_list[i].push_back(edge);
		//weights[i][j] = data.getPipes().at(id).getWeigth(); 
		capacity[i][j] = data.getPipes().at(id).getCapacity();
	}
}

int Graph::getValue(std::vector<int> arr, int index) {
	return arr[index];
}

int Graph::getIndex(Data& data, int value) {
	std::vector<int> array;
	for (auto& [id, edge] : data.getStations()) {
		array.push_back(id);
	}
	for (int i = 0; i < array.size(); i++) {
		if (array[i] == value) {
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

bool Graph::bfs(std::vector<std::vector<int>>& rGraph, int s, int t, std::vector<int>& parent) {
	std::vector<bool> visited(V, false);
	std::queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (!visited[v] && rGraph[u][v] > 0) {
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return visited[t];
}

int Graph::MaxFlow(Data& data, int s, int t) {
	std::vector<std::vector<int>> rGraph = capacity;
	std::vector<int> parent(V);
	int maxFlow = 0;

	s = getIndex(data, s);
	t = getIndex(data, t);

	while (bfs(rGraph, s, t, parent)) {
		int pathFlow = INT_MAX;

		for (int v = t; v != s; v = parent[v]) {
			int u = parent[v];
			pathFlow = std::min(pathFlow, rGraph[u][v]);
		}

		for (int v = t; v != s; v = parent[v]) {
			int u = parent[v];
			rGraph[u][v] -= pathFlow;
			rGraph[v][u] += pathFlow;
		}

		maxFlow += pathFlow;
	}

	return maxFlow;
}
int Graph::shortest_path(Data& data, int start, int end) {

	int s = getIndex(data, start);
	int n = adj_list.size();
	distances.assign(data.getStations().size(), INT_MAX);
	distances[s] = 0;

	std::vector<int> path;
	path.push_back(start);

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
			if (w != 0 && distances[u] + w < distances[v]) {
				path.push_back(v);
				distances[v] = distances[u] + w;
				pq.push({ distances[v], v });
			}
		}
	}
	std::vector<int> array;
	for (auto& [id, edge] : data.getStations()) {
		array.push_back(id);
	}
	for (int i = 0; i < path.size(); i++) {
		path[i] = getValue(array, path[i]);
	}
	std::reverse(path.begin(), path.end());

	std::vector<int> final_path;
	
	int index = getIndex(data, end);
	for (int i = 0; i < distances.size(); i++) {
		if (i == index) {
			
			final_path.push_back(path[0]);

			for (int i = 1; i < path.size(); i++) {
				if (find_edge(path[i], 1)) {
					final_path.push_back(path[i]);
					final_path.push_back(start);
					break;
				}
				else {
					final_path.push_back(path[i]);
				}
			}

			std::reverse(final_path.begin(), final_path.end());
			for (int i : final_path) {
				std::cout << " " << i;
			}
			std::cout << std::endl;
			return distances[i];
		}
	}

	


}