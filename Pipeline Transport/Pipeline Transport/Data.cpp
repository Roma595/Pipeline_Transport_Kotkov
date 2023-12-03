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


std::unordered_map<Data::ID, Pipe>& Data::getPipes() {
	return _pipes;
}

std::unordered_map<Data::ID, CompressorStation>& Data::getStations() {
	return _stations;
}

template <>
const std::unordered_map<Data::ID, Pipe>& Data::getAll<Pipe>() const {
	return _pipes;
}

template <>
const std::unordered_map<Data::ID, CompressorStation>& Data::getAll<CompressorStation>() const {
	return _stations;
}

void Data::delete_pipe(ID id) {
	auto it = _pipes.find(id);
	if (it == _pipes.end()) {
		std::cout << "Error";
	}
	_pipes.erase(it);
}
void Data::delete_station(ID id) {
	auto it = _stations.find(id);
	if (it == _stations.end()) {
		std::cout << "Error";
	}
	_stations.erase(it);
}

std::vector<Data::ID> Data::get_free_pipes(std::vector<ID>& ids) {
	std::vector<ID> free_pipes;
	for (ID id : ids) {
		if (!_edges.contains(id)) {
			free_pipes.push_back(id);
		}
	}
	return free_pipes;
}

void Data::add_edge(int pipe_id, int station_source, int station_drain) {
	if (_stations.contains(station_source) && _stations.contains(station_drain)) {
		Edge edge{ station_source,station_drain };
		_edges.insert({ pipe_id, edge });
	}
	else {
		std::cout << "there are no stations with these IDs" << std::endl;
	}
}

void Data::delete_edge(int id) {
	if (_edges.contains(id)) {
		_edges.erase(id);
		std::cout << "Edge with id = " << id << " was deleted" << std::endl;
		return;
	}
	std::cout << "No edges with id = " << id << std::endl;
}

void Data::view_edges() {
	if (!_edges.empty()) {
		for (auto& [pipe_id, edge] : _edges) {
			std::cout << "Edge with ID: " << pipe_id << " | source - " << edge.source << " | drain - " << edge.drain << std::endl;
		}
	}
	else {
		std::cout << "There are no edges" << std::endl;
	}
}

int Data::getNextStationId() const {
	return _nextStationId;
}
int Data::getNextPipeId() const {
	return _nextPipeId;
}
