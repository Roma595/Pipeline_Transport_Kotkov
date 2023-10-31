#include <iostream>
#include <string>
#include <iomanip>

#include "CompressorStation.h"
#include "Utilities.h"

void print(const CompressorStation& station, std::ostream& stream, bool pretty) {
	print_value(stream, station.getName(), "Name:                         ", pretty);
	print_value(stream, station.getWorkshops(), "Number of workshops:          ", pretty);
	print_value(stream, station.getWorkshopsInUse(), "Number of use workshops:      ", pretty);
	print_value(stream, station.getEffectiveness(),	"Effectiveness:                ", pretty);
}

CompressorStation input_station(std::istream& in) {
	CompressorStation station;

	input_and_set<InputStringWithSpaces>(
		in,
		[&station](const std::string& value) { station.setName(value); },
		"Enter name: ");

	input_and_set<int>(
		in,
		[&station](int value) { station.setWorkshops(value); },
		"Enter workshops: ");

	input_and_set<int>(
		in,
		[&station](int value) { station.setWorkshopsInUse(value); },
		"Enter workshops in use: ");

	input_and_set<int>(
		in,
		[&station](int value) { station.setEffectiveness(value); },
		"Enter effectiveness: ");

	return station;
}