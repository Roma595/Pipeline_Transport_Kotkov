#pragma once

#include <string>
#include <iostream>

struct CompressorStation {
	std::string name = "None";
	int number_of_workshop = 0;
	int number_of_use_workshop = 0;
	int effectiveness = 0;

};

void print(const CompressorStation& station, std::ostream& stream);
void pretty_print(const CompressorStation& station, std::ostream& stream);

bool input_station(CompressorStation& station, std::istream& stream);
CompressorStation input_station_interactive();

