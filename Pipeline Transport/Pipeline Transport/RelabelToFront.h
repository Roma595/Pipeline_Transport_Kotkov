#pragma once
#include <vector>
#include "Graph.h"
#include <list>
#include <unordered_map>
#include <optional>

class AdjacencyListGraph {
public:

	using Vertex = size_t;
	using Edge = size_t;

	struct VertexData {
	};

	struct EdgeData {
		Vertex start, end;
	};

	std::vector <VertexData> vertex_data;
	std::vector <EdgeData> edge_data;

	std::vector<std::vector<Edge>> graph;

	AdjacencyListGraph(const Graph& Add_graph) {
		const auto& adjacency_matrix = Add_graph.capacity;
		graph.resize(adjacency_matrix.size());
		for (size_t i = 0; i < adjacency_matrix.size(); i++) {
			vertex_data.emplace_back();
			for (size_t j = 0; j < adjacency_matrix.size(); j++) {
				if (adjacency_matrix[i][j] != 0) {
					edge_data.emplace_back(i, j);
					graph[i].emplace_back(edge_data.size() - 1);
					graph[j].emplace_back(edge_data.size() - 1);
				}
			}
		}
	}
};

class RelabelToFront {

public:
	using Vertex = AdjacencyListGraph::Vertex;
	using Edge = AdjacencyListGraph::Edge;

	AdjacencyListGraph graph;

	Vertex source;
	Vertex drain;

	struct VertexData {
		size_t current = 0;
		int excess_flow = 0;
		int height = 0;
		std::unordered_map<Vertex, Edge> edges;
	};

	struct EdgeData {
		int flow = 0;
		int capacity = 0;
	};

	std::list<Vertex> L;
	std::list<Vertex>::iterator current_element;
	std::vector<EdgeData> edge_data;
	std::vector<VertexData> vertex_data;


	RelabelToFront(const Graph& G, Vertex source, Vertex drain) : graph(G) {
		vertex_data.resize(graph.vertex_data.size());
		edge_data.resize(graph.edge_data.size());
		this->source = source;
		this->drain = drain;
		vertex_data[source].height = vertex_data.size();
		for (Edge edge = 0; edge < edge_data.size(); edge++) {
			const auto& e = graph.edge_data[edge];
			edge_data[edge].capacity = G.capacity[e.start][e.end];
			if (e.start == source) {
				edge_data[edge].flow = edge_data[edge].capacity;
				vertex_data[e.end].excess_flow += edge_data[edge].capacity;
			}
		}
		for (Vertex v = 0; v < vertex_data.size(); v++) {
			if (v != source && v != drain) {
				L.push_back(v);
			}
			for (Edge e : graph.graph[v]) {
				if (graph.edge_data[e].start != v) {
					continue;
				}
				vertex_data[v].edges[graph.edge_data[e].end] = e;
			}
		}
		current_element = L.begin();
	}

	bool can_push(Vertex u, Vertex v) {
		if (vertex_data[u].excess_flow <= 0) {
			return false;
		}

		if (!is_successor(u, v)) {
			return false;
		}

		if (vertex_data[u].height <= vertex_data[v].height) {
			return false;
		}
		return true;
	}

	std::optional<Edge> find_edge(Vertex u, Vertex v) {
		auto it = vertex_data[u].edges.find(v);
		if (it == vertex_data[u].edges.end()) {
			return std::nullopt;
		}
		return it->second;
	}

	void push(Vertex u, Vertex v) {
		std::optional<Edge> e = find_edge(u, v);
		std::optional<Edge> e1 = find_edge(v, u);
		if (e.has_value()) {
			int dF = std::min(vertex_data[u].excess_flow, edge_data[e.value()].capacity - edge_data[e.value()].flow);
			edge_data[e.value()].flow += dF;
			vertex_data[v].excess_flow += dF;
			vertex_data[u].excess_flow -= dF;
		}
		if (e1.has_value()) {
			int dF = std::min(vertex_data[u].excess_flow, edge_data[e1.value()].flow);
			edge_data[e1.value()].flow -= dF;
			vertex_data[v].excess_flow += dF;
			vertex_data[u].excess_flow -= dF;
		}
	}

	bool can_relabel(Vertex u) {
		if (vertex_data[u].excess_flow <= 0) {
			return false;
		}
		for (Edge e : graph.graph[u]) {
			Vertex v = (graph.edge_data[e].start == u) ? graph.edge_data[e].end : graph.edge_data[e].start;
			if (!is_successor(u, v)) {
				continue;
			}
			if (vertex_data[u].height > vertex_data[v].height) {
				return false;
			}
		}
		return true;
	}

	void relabel(Vertex u) {
		int min_height = vertex_data[u].height;

		for (Edge e : graph.graph[u]) {
			Vertex v = (graph.edge_data[e].start == u) ? graph.edge_data[e].end : graph.edge_data[e].start;
			if (!is_successor(u, v)) {
				continue;
			}
			min_height = std::min(min_height, vertex_data[v].height);
		}
		vertex_data[u].height = min_height + 1;
	}

	bool is_successor(Vertex u, Vertex v) {
		std::optional<Edge> e = find_edge(u, v);
		std::optional<Edge> e1 = find_edge(v, u);

		if (e.has_value() && edge_data[*e].capacity != edge_data[*e].flow) {
			return true;
		}
		else if (e1.has_value() && edge_data[*e1].flow > 0) {
			return true;;
		}
		return false;
	}

	bool is_acceptable(Vertex u, Vertex v) {
		if (!is_successor(u, v)) {
			return false;
		}
		if (vertex_data[u].height != (vertex_data[v].height + 1)) {
			return false;
		}
		return true;
	}

	void discharge(Vertex u) {
		auto& data = vertex_data[u];
		while (data.excess_flow > 0) {
			if (data.current >= graph.graph[u].size()) {
				if (!can_relabel(u)) {
					return;
				}
				relabel(u);
				data.current = 0;
				continue;
			}
			Edge e = graph.graph[u][data.current];
			Vertex v = graph.edge_data[e].end;
			if (v == u) {
				v = graph.edge_data[e].start;
			}
			if (is_acceptable(u, v)) {
				push(u, v);
				continue;
			}
			data.current += 1;
		}
	}

	int max_flow() {
		if (vertex_data.size() == 2) {
			return vertex_data[drain].excess_flow;
		}
		while (current_element != L.end()) {
			Vertex u = *current_element;
			int previous_height = vertex_data[u].height;

			discharge(u);
			if (vertex_data[u].height != previous_height) {
				L.erase(current_element);
				L.push_front(u);
				current_element = L.begin();
			}
			++current_element;
		}
		return vertex_data[drain].excess_flow;
	}
};