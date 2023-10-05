#include <string>

#include "Data.h"
#include "Utilities.h"


void print(const Data& data, std::ostream& stream) {
	if (data.pipe.has_value()) {
		stream << "PIPE" << std::endl;
		print(data.pipe.value(), stream);
	}
	if (data.station.has_value()) {
		stream << "STATION" << std::endl;
		print(data.station.value(), stream);
	}
	stream << "END" << std::endl;
}

void pretty_print(const Data& data, std::ostream& stream) {
	if (!data.pipe.has_value() && !data.station.has_value()) {
		stream << "There are no pipes and stations." << std::endl;
	}
	if (data.pipe.has_value()) {
		stream << "\tPipes:" << std::endl;
		pretty_print(data.pipe.value(), stream);
		stream << std::endl;
	}
	if (data.station.has_value()) {
		stream << "\tStations:" << std::endl;
		pretty_print(data.station.value(), stream);
		stream << std::endl;
	}

}

bool input_data(Data& data, std::istream& stream) {
	Data input;
	for (std::string file_section = ""; file_section != "END"; file_section = read_line(stream))
	{
		if (stream.eof()) {
			return false;
		}
		if (file_section == "") {
			continue;
		}
		if (file_section == "PIPE") {
			input.pipe = Pipe();
			if (!input_pipe(input.pipe.value(), stream)) {
				return false;
			}
		}
		else if (file_section == "STATION") {
			input.station = CompressorStation();
			if (!input_station(input.station.value(), stream)) {
				return false;
			}
		}
		else {
			return false;
		}
	}
	data = input;
	return true;
}