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

const std::string& CompressorStation::getName() const {
	return name_;
}
int CompressorStation::getWorkshops() const {
	return workshops_;
}
int CompressorStation::getWorkshopsInUse() const {
	return workshops_in_use_;
}
int CompressorStation::getEffectiveness() const {
	return effectiveness_;
}

void CompressorStation::setName(const std::string& name) {
	if (name.empty()) {
		throw std::invalid_argument("Station name should not be empty");
	}
	name_ = name;
}
void CompressorStation::setWorkshops(int workshops) {
	if (workshops < 1) {
		throw std::invalid_argument("Number of workshops in station should be >= 1");
	}
	workshops_ = workshops;
}
void CompressorStation::setWorkshopsInUse(int workshops_in_use) {
	if (workshops_in_use < 0) {
		throw std::invalid_argument("Number of workshops in use in station should not be negative");
	}
	if (workshops_in_use > workshops_) {
		throw std::invalid_argument("Number of workshops in use in station should be < workshops");
	}
	workshops_in_use_ = workshops_in_use;
}
void CompressorStation::setEffectiveness(int effectiveness) {
	if (effectiveness < 1 || effectiveness >10) {
		throw std::invalid_argument("Effectiveness of station should be between 1 to 10");
	}
	effectiveness_ = effectiveness;
}