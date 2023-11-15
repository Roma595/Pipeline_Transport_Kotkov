#include "Pipe.h"
#include "CompressorStation.h"
#include "Data.h"
#include "Utilities.h"

void Data::print(std::ostream& stream, bool pretty) {
	for (std::pair<int,Pipe> pair : _pipes) {
		stream << "PIPE" << std::endl;
		print_value(stream, pair.first, "ID: ", pretty);
		pair.second.print(stream, pretty);
		if (pretty) {
			stream << std::endl;
		}
	}

	for (std::pair<int,CompressorStation> pair : _stations) {
		stream << "STATION" << std::endl;
		print_value(stream, pair.first, "ID: ", pretty);
		pair.second.print(stream, pretty);
		if (pretty) {
			stream << std::endl;
		}
	}

	if (!pretty) {
		stream << "END" << std::endl;
	}
}

void Data::load_data(std::istream& stream) {
	for (std::string section = " "; section != "END"; stream >> section) {
		Data::ID id;
		if (stream.eof()) {
			std::cout << "Incorrect file format: no \"END\" section found" << std::endl;
		}
		if (section == " ") {
			continue;
		}
		if (section == "PIPE") {
			Pipe pipe;
			stream >> id;
			pipe.export_pipe(stream);
			_pipes.insert({ id,pipe });
			_nextPipeId = std::max(id + 1, _nextPipeId);
		}
		else if (section == "STATION") {
			CompressorStation station;
			stream >> id;
			station.export_station(stream);
			_stations.insert({ id,station });
			_nextStationId = std::max(id + 1, _nextStationId);
		}
		else {
			std::cout << "Incorrect file format: unknown section: " << section << std::endl;
		}
	}
}

Data::ID Data::add_pipe(const Pipe& pipe) {
	_pipes.insert({ _nextPipeId++, pipe });
	return _nextPipeId;
}


Data::ID Data::add_station(const CompressorStation& station) {
	_stations.insert({ _nextStationId++, station });
	return _nextStationId;
}

const std::unordered_map<Data::ID, Pipe>& Data::getPipes() const {
	return _pipes;
}
std::unordered_map<Data::ID, Pipe>& Data::getPipes() {
	return _pipes;
}

const std::unordered_map<Data::ID, CompressorStation>& Data::getStations() const {
	return _stations;
}
std::unordered_map<Data::ID, CompressorStation>& Data::getStations() {
	return _stations;
}
