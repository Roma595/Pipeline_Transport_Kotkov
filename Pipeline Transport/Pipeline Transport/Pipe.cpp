#include <iostream>
#include <string>

#include "Utilities.h"
#include "Pipe.h"


void Pipe::print(std::ostream& stream, bool pretty) {
	print_value(stream, _name, "Name:                         ", pretty);
	print_value(stream, _length, "Length:                       ", pretty);
	print_value(stream, _diameter, "Diameter:                     ", pretty);
	print_value(stream, _status, "Status:                       ", pretty);
}

void Pipe::input_pipe() {
	std::cout << "Enter name: ";
	std::cin >> std::ws;
	std::getline(std::cin, _name);

	std::cout << "Enter length: ";
	_length = validity_enter_interactive<double>(1.0, 100000.0);

	std::cout << "Enter diameter: ";
	_diameter = validity_enter_interactive<int>(1, 100000);

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
	_name = name;
}
void Pipe::setLength(double length) {
	_length = length;
}
void Pipe::setDiameter(int diameter) {
	_diameter = diameter;
}
void Pipe::setStatus(bool status) {
	_status = status;
}