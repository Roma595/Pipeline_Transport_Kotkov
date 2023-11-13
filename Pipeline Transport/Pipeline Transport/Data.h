#pragma once
#include <optional>
#include <iostream>
#include <unordered_map>

#include "CompressorStation.h"
#include "Pipe.h"

class Data {
public:
	using ID = unsigned int;

	void print(std::ostream& stream, bool pretty);
	void load_data(std::istream& stream);

	const std::unordered_map<Data::ID, Pipe>& getPipes() const;
	const std::unordered_map<Data::ID, CompressorStation>& getStations() const;

	std::unordered_map<Data::ID, Pipe>& getPipes();
	std::unordered_map<Data::ID, CompressorStation>& getStations();

	ID add_pipe(const Pipe& pipe);
	ID add_station(const CompressorStation& station);

private:
	unsigned int _nextPipeId = 0;
	unsigned int _nextStationId = 0;
	std::unordered_map<ID,Pipe> _pipes;
	std::unordered_map<ID, CompressorStation> _stations;
};


