
#include "CompressorStation.h"
#include "Utilities.h"

void CompressorStation::print(std::ostream& stream, bool pretty) {
	print_value(stream, _name, "Name:                             ", pretty);
	print_value(stream, _workshops, "Number of workshops:              ", pretty);
	print_value(stream, _workshops_in_use, "Number of use workshops:          ", pretty);
	print_value(stream, _effectiveness,	"Effectiveness:                    ", pretty);
}

void CompressorStation::input_station() {
	std::cout << "Enter name: ";
	std::cin >> std::ws;
	std::getline(std::cin, _name);

	std::cout << "Enter number of workshops: ";
	_workshops = validity_enter_interactive<int>(1, 100000);

	std::cout << "Enter number of workshops in work: ";
	_workshops = validity_enter_interactive<int>(1, _workshops);

	std::cout << "Enter effectiveness: ";
	_effectiveness = validity_enter_interactive<int>(0, 10);
}

void CompressorStation::export_station(std::istream& in) {
	in.ignore(1000, '\n');
	std::getline(in, _name);
	in >> _workshops >> _workshops_in_use >> _effectiveness;
}

const std::string& CompressorStation::getName() const {
	return _name;
}
int CompressorStation::getWorkshops() const {
	return _workshops;
}
int CompressorStation::getWorkshopsInUse() const {
	return _workshops_in_use;
}
int CompressorStation::getEffectiveness() const {
	return _effectiveness;
}

void CompressorStation::setName(const std::string& name) {
	if (name.empty()) {
		std::cout << "Station name should not be empty" << std::endl;
	}
	_name = name;
}
void CompressorStation::setWorkshops(int workshops) {
	if (workshops < 1 || workshops < _workshops_in_use) {
		std::cout << "Number of workshops in station should be >= 1 and <= workshops in use" << std::endl;
	}
	_workshops = workshops;
}
void CompressorStation::setWorkshopsInUse(int workshops_in_use) {
	if (workshops_in_use < 0) {
		std::cout << "Number of workshops in use in station should not be negative" << std::endl;
	}
	if (workshops_in_use > _workshops) {
		std::cout << "Number of workshops in use in station should be < workshops" << std::endl;
	}
	_workshops_in_use = workshops_in_use;
}
void CompressorStation::setEffectiveness(int effectiveness) {
	if (effectiveness < 1 || effectiveness >10) {
		std::cout << "Effectiveness of station should be between 1 to 10" << std::endl;
	}
	_effectiveness = effectiveness;
}
