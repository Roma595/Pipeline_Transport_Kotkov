#include <string>

#include "Pipe.h"
#include "CompressorStation.h"
#include "Data.h"
#include "Utilities.h"

namespace {
	enum FileSection {
		PIPE,
		STATION,
		END,
		UNKNOWN
	};
}

std::string to_string(FileSection section) {
	switch (section) {
	case FileSection::PIPE:
		return "PIPE";
	case FileSection::STATION:
		return "STATION";
	case FileSection::END:
		return "END";
	case FileSection::UNKNOWN:
		return "UNKNOWN";
	}
}

std::ostream& operator << (std::ostream& out, FileSection section) {
	out << to_string(section);
	return out;
}

std::istream& operator >> (std::istream& in, FileSection& section) {
	std::string file_section;
	in >> file_section;
	if (file_section == "PIPE") {
		section = FileSection::PIPE;
		return in;
	}
	if (file_section == "STATION") {
		section = FileSection::STATION;
		return in;
	}
	if (file_section == "END") {
		section = FileSection::END;
		return in;
	}
	throw std::invalid_argument("File section should be \"PIPE\" or \"STATION\" or \"END\", but got "+file_section);
}

void print(const Data& data, std::ostream& stream, bool pretty) {
	if (!data.getPipes().empty()) {
		for (const auto& [id, pipe] : data.getPipes()) {
			stream << FileSection::PIPE << std::endl;
			print_value(stream, id, "ID: ", pretty);
			print(pipe, stream, pretty);
			if (pretty) {
				stream << std::endl;
			}
		}
	}
	if (!data.getStations().empty()) {
		for (const auto& [id, station] : data.getStations()) {
			stream << FileSection::STATION << std::endl;
			print_value(stream, id, "ID: ", pretty);
			print(station, stream, pretty);
			if (pretty) {
				stream << std::endl;
			}
		}
	}
	if (!pretty) {
		stream << FileSection::END << std::endl;
	}
}

Data input_data(std::istream& stream) {
	Data data;
	for (FileSection section = FileSection::UNKNOWN; section != FileSection::END; stream >> section)
	{
		if (stream.eof()) {
			throw std::runtime_error("Incorrect file format: no \"END\" section found");
		}
		if (section == FileSection::UNKNOWN) {
			continue;
		}
		if (section == FileSection::PIPE) {
			Data::ID id;
			input_raw<Data::ID>(stream, [&id](Data::ID value) {id = value; });
			data.add_pipe_by_id(id,input_pipe(stream));
		}
		else if (section == FileSection::STATION) {
			Data::ID id;
			stream >> id;
			data.add_station_by_id(id, input_station(stream));
		}
		else {
			throw std::runtime_error("Incorrect file format: unknown section: \"" + to_string(section) + "\"");
		}
	}
	return data;
}

const std::unordered_map<Data::ID, Pipe>& Data::getPipes() const {
	return pipes_;
}
const std::unordered_map<Data::ID, CompressorStation>& Data::getStations() const {
	return stations_;
}

Pipe& Data::getPipeById(ID id) {
	auto it = pipes_.find(id);
	if (it == pipes_.end()) {
		throw std::invalid_argument("Not found pipe by id");
	}
	return it->second;
}
const Pipe& Data::getPipeById(ID id) const {
	auto it = pipes_.find(id);
	if (it == pipes_.end()) {
		throw std::invalid_argument("Not found pipe by id");
	}
	return it->second;
}
CompressorStation& Data::getStationById(ID id) {
	auto it = stations_.find(id);
	if (it == stations_.end()) {
		throw std::invalid_argument("Not found pipe by id");
	}
	return it->second;
}
const CompressorStation& Data::getStationById(ID id) const {
	auto it = stations_.find(id);
	if (it == stations_.end()) {
		throw std::invalid_argument("Not found pipe by id");
	}
	return it->second;
}

Data::ID Data::add_pipe(const Pipe& pipe) {
	return add_pipe_by_id(nextPipeId_, pipe);
}
Data::ID Data::add_pipe_by_id(ID id, const Pipe& pipe) {
	if (pipes_.find(id) != pipes_.end()) {
		throw std::invalid_argument("There is already a pipe with id = " + id);
	}
	pipes_.insert({ id, pipe });
	nextPipeId_ = std::max(id + 1, nextPipeId_);
	return id;
}

Data::ID Data::add_station(const CompressorStation& station) {
	return add_station_by_id(nextStationId_, station);
}
Data::ID Data::add_station_by_id(ID id, const CompressorStation& station) {
	if (stations_.find(id) != stations_.end()) {
		throw std::invalid_argument("There is already station with id = " + id);
	}
	stations_.insert({ id, station });
	nextStationId_ = std::max(id + 1, nextStationId_);
	return id;
}

void Data::delete_pipe(ID id) {
	auto it = pipes_.find(id);
	if (it == pipes_.end()) {
		throw;
	}
	pipes_.erase(it);
}
void Data::delete_station(ID id) {
	auto it = stations_.find(id);
	if (it == stations_.end()) {
		throw;
	}
	stations_.erase(it);
}
