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
	std::unordered_map<ID, Pipe>& getPipes() {
		return pipes_;
	}
	const std::unordered_map<ID, CompressorStation>& getStations() const{
		return stations_;
	}
	std::unordered_map<ID, CompressorStation>& getStations() {
		return stations_;
	}
	
private:
	std::unordered_map<ID,Pipe> pipes_;
	std::unordered_map<ID, CompressorStation> stations_;
};

void print(const Data& data, std::ostream& stream, bool pretty);
Data input_data(std::istream& stream);