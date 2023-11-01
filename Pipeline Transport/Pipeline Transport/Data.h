#pragma once
#include <optional>
#include <iostream>
#include <unordered_map>

#include "CompressorStation.h"
#include "Pipe.h"

class Data {
public:
	using ID = unsigned int;

	const std::unordered_map<ID, Pipe>& getPipes() const;
	const std::unordered_map<ID, CompressorStation>& getStations() const;

	Pipe& getPipeById(ID id);
	const Pipe& getPipeById(ID id) const;
	CompressorStation& getStationById(ID id);
	const CompressorStation& getStationById(ID id) const;

	ID add_pipe(const Pipe& pipe);
	ID add_pipe_by_id(ID id, const Pipe& pipe);
	ID add_station(const CompressorStation& station);
	ID add_station_by_id(ID id, const CompressorStation& station);

	void delete_pipe(ID id);
	void delete_station(ID id);

private:
	ID nextPipeId_ = 0;
	ID nextStationId_ = 0;
	std::unordered_map<ID,Pipe> pipes_;
	std::unordered_map<ID, CompressorStation> stations_;
};

void print(const Data& data, std::ostream& stream, bool pretty);
Data input_data(std::istream& stream);