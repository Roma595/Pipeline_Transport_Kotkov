#pragma once

#include <iostream>
#include <unordered_map>

#include "CompressorStation.h"
#include "Pipe.h"

struct Edge {
	int start;
	int end;
	int weight;
	int capacity;
};

class Data {
public:
	using ID = unsigned int;

	void save(std::ostream& stream, bool pretty);
	void print(std::ostream& stream, bool pretty);
	void load_data(std::istream& stream);

	template<typename Type>
	const std::unordered_map<ID, Type>& getAll() const = delete;
	
	std::unordered_map<ID, Pipe>& getPipes();
	std::unordered_map<ID, CompressorStation>& getStations();

	std::unordered_map<int, Edge>& getEdges() {
		return _edges;
	}

	int getNextStationId() const;
	int getNextPipeId() const;
	ID add_pipe(const Pipe& pipe);
	ID add_station(const CompressorStation& station);

	void delete_pipe(ID id);
	void delete_station(ID id);

	std::vector<ID> get_free_pipes(std::vector<ID>& ids);

	void add_edge(int pipe_id, int station_source, int station_drain);

	void view_edges();
	void delete_edge(int id);

private:
	unsigned int _nextPipeId = 0;
	unsigned int _nextStationId = 0;
	std::unordered_map<ID,Pipe> _pipes;
	std::unordered_map<ID, CompressorStation> _stations;
	std::unordered_map<int, Edge> _edges;
};

template <>
const std::unordered_map<Data::ID, Pipe>& Data::getAll<Pipe>() const;

template <>
const std::unordered_map<Data::ID, CompressorStation>& Data::getAll<CompressorStation>() const;

