#pragma once

#include <iostream>
#include <unordered_map>

#include "CompressorStation.h"
#include "Pipe.h"

class Data {
public:
	using ID = unsigned int;

	void print(std::ostream& stream, bool pretty);
	void load_data(std::istream& stream);

	const std::unordered_map<ID, Pipe>& getPipes() const;
	const std::unordered_map<ID, CompressorStation>& getStations() const;

	template<typename Type>
	const std::unordered_map<ID, Type>& getAll() const = delete;
	
	std::unordered_map<ID, Pipe>& getPipes();
	std::unordered_map<ID, CompressorStation>& getStations();

	ID add_pipe(const Pipe& pipe);
	ID add_station(const CompressorStation& station);

private:
	unsigned int _nextPipeId = 0;
	unsigned int _nextStationId = 0;
	std::unordered_map<ID,Pipe> _pipes;
	std::unordered_map<ID, CompressorStation> _stations;
};

template <>
const std::unordered_map<Data::ID, Pipe>& Data::getAll<Pipe>() const;

template <>
const std::unordered_map<Data::ID, CompressorStation>& Data::getAll<CompressorStation>() const;



