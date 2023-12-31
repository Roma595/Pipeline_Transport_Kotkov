#include "Utilities.h"
#include "Pipe.h"


void Pipe::print(std::ostream& stream, bool pretty) {
	print_value(stream, _name, "Name:                             ", pretty);
	print_value(stream, _length, "Length:                           ", pretty);
	print_value(stream, _diameter, "Diameter:                         ", pretty);
	print_value(stream, _status, "Status(1 - work, 0 - in repair):  ", pretty);
}

void Pipe::input_pipe() {
	std::cout << "Enter name: ";
	std::cin >> std::ws;
	std::getline(std::cin, _name);

	std::cout << "Enter length: ";
	_length = validity_enter_interactive<double>(1.0, 100000.0);

	std::cout << "Enter diameter: ";
	int d = 0;
	std::cin >> d;
	while (d != 500 && d != 700 && d != 1000 && d != 1400) {
		std::cin.ignore(1000, '\n');
		std::cout << "Pipe diameter should be 500, 700, 1000 or 1400" << std::endl;
		std::cin >> d;
	}
	setDiameter(d);

	std::cout << "Enter status (1 - work, 0 - in repair): ";
	_status = validity_enter_interactive<bool>(0, 1);
}

void Pipe::input_pipe_without_diameter(int diameter) {
	std::cout << "Enter name: ";
	std::cin >> std::ws;
	std::getline(std::cin, _name);

	std::cout << "Enter length: ";
	_length = validity_enter_interactive<double>(1.0, 100000.0);

	_diameter = diameter;

	std::cout << "Enter status (1 - work, 0 - in repair): ";
	_status = validity_enter_interactive<bool>(0, 1);
}

void Pipe::export_pipe(std::istream& in) {
	in.ignore(1000, '\n');
	std::getline(in, _name);
	in >> _length >> _diameter >> _status;
}

const std::string& Pipe::getName() const {
	return _name;
}
double Pipe::getLength() const {
	return _length;
}
int Pipe::getDiameter() const {
	return _diameter;
}
bool Pipe::getStatus() const {
	return _status;
}

void Pipe::setName(const std::string& name) {
	if (name.empty()) {
		std::cout << "Pipe name should not be empty" << std::endl;
		return;
	}
	_name = name;
}
void Pipe::setLength(double length) {
	if (length < 1.0) {
		std::cout << "Pipe length should be >= 1" << std::endl;
	}
	_length = length;
}
void Pipe::setDiameter(int diameter) {
	if (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
		std::cout << "Pipe diameter should be 500, 700, 1000 or 1400" << std::endl;
		return;
	}
	_diameter = diameter;
}
void Pipe::setStatus(bool status) {
	if (status < 0 || status >1) {
		std::cout << "Status should be (1 - work or 0 - in repair)" << std::endl;
	}
	_status = status;
}