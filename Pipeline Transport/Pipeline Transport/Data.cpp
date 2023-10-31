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