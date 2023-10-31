#pragma once
#include <optional>
#include <iostream>
#include <unordered_map>

#include "CompressorStation.h"
#include "Pipe.h"

class Data {
public:
	using ID = unsigned int;

	const std::unordered_map<ID, Pipe>& getPipes() const {
		return pipes_;
	}

	Pipe& getPipeById(ID id) {
		auto it = pipes_.find(id);
		if (it == pipes_.end()) {
			throw std::invalid_argument("Not found pipe by id");
		}
		return it->second;
	}

	const Pipe& getPipeById(ID id) const {
		auto it = pipes_.find(id);
		if (it == pipes_.end()) {
			throw std::invalid_argument("Not found pipe by id");
		}
		return it->second;
	}
	CompressorStation& getStationById(ID id) {
		auto it = stations_.find(id);
		if (it == stations_.end()) {
			throw std::invalid_argument("Not found pipe by id");
		}
		return it->second;
	}

	const CompressorStation& getStationById(ID id) const {
		auto it = stations_.find(id);
		if (it == stations_.end()) {
			throw std::invalid_argument("Not found pipe by id");
		}
		return it->second;
	}

	const std::unordered_map<ID, CompressorStation>& getStations() const{
		return stations_;
	}

	ID add_pipe(const Pipe& pipe) {
		return add_pipe_by_id(nextPipeId_, pipe);
	}

	ID add_station(const CompressorStation& station) {
		return add_station_by_id(nextStationId_, station);
	}

	ID add_pipe_by_id(ID id, const Pipe& pipe) {
		if (pipes_.find(id) != pipes_.end()) {
			throw std::invalid_argument("There is already a pipe with id = " + id);
		}
		pipes_.insert({ id, pipe });
		nextPipeId_ = std::max(id + 1, nextPipeId_);
		return id;
	}

	ID add_station_by_id(ID id, const CompressorStation& station) {
		if (stations_.find(id) != stations_.end()) {
			throw std::invalid_argument("There is already station with id = " + id);
		}
		stations_.insert({ id, station });
		nextStationId_ = std::max(id + 1, nextStationId_);
		return id;
	}

	void delete_pipe(ID id) {
		auto it = pipes_.find(id);
		if (it == pipes_.end()) {
			throw;
		}
		pipes_.erase(it);
	}
	void delete_station(ID id) {
		auto it = stations_.find(id);
		if (it == stations_.end()) {
			throw;
		}
		stations_.erase(it);
	}

private:
	ID nextPipeId_ = 0;
	ID nextStationId_ = 0;
	std::unordered_map<ID,Pipe> pipes_;
	std::unordered_map<ID, CompressorStation> stations_;
};

void print(const Data& data, std::ostream& stream, bool pretty);
Data input_data(std::istream& stream);