#include <iostream>
#include <string>
#include <iomanip>

#include "CompressorStation.h"
#include "Utilities.h"


void print(const CompressorStation& station, std::ostream& stream) {
	stream << station.name << std::endl
		<< station.number_of_workshop << std::endl
		<< station.number_of_use_workshop << std::endl
		<< station.effectiveness << std::endl;
}

void pretty_print(const CompressorStation& station, std::ostream& stream) {
	stream << std::left << std::setw(30) << "Name:" << std::left << std::setw(10) << station.name << std::endl;
	stream << std::left << std::setw(30) << "Number of workshops:" << std::left << std::setw(10) << station.number_of_workshop << std::left << std::endl;
	stream << std::left << std::setw(30) << "Number of use workshops:" << std::left << std::setw(10) << station.number_of_use_workshop << std::endl;
	stream << std::left << std::setw(30) << "Effectiveness:" << std::left << std::setw(10) << station.effectiveness << std::endl;
}

bool input_station(CompressorStation& station, std::istream& stream) {
	CompressorStation input;
	stream >> std::ws;
	std::getline(stream, input.name);
	if (!validity_enter(stream, input.number_of_workshop, 1, 100000)) {
		return false;
	}
	if (!validity_enter(stream, input.number_of_use_workshop, 0, input.number_of_workshop)) {
		return false;
	}
	if (!validity_enter(stream,input.effectiveness, 1, 10)) {
		return false;
	}
	station = input;
	return true;
}

CompressorStation input_station_interactive() {
	CompressorStation station;
	std::cout << "Enter name: ";								
	std::cin >> std::ws;
	std::getline(std::cin, station.name);

	std::cout << "Enter number of workshop: ";					
	station.number_of_workshop = validity_enter_interactive(1, 100000);

	std::cout << "Enter number of use workshop: ";				
	station.number_of_use_workshop = validity_enter_interactive(0, station.number_of_workshop);

	std::cout << "Enter effectiveness(1-10): ";					
	station.effectiveness = validity_enter_interactive(1, 10);

	return station;
}