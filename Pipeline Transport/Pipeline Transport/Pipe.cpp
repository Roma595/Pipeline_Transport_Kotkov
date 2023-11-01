#include <iostream>
#include <string>
#include <iomanip>

#include "Utilities.h"
#include "Pipe.h"


std::ostream& operator << (std::ostream& out, Pipe::Status status) {
	switch (status) {
	case Pipe::Status::WORKING:
		out << "working";
		break;
	case Pipe::Status::IN_REPAIR:
		out << "in_repair";
		break;
	}
	return out;
}

std::istream& operator >> (std::istream& in, Pipe::Status& status) {
	std::string pipe_status;
	in >> pipe_status;
	if (pipe_status == "working") {
		status = Pipe::Status::WORKING;
		return in;
	}
	if (pipe_status == "in_repair") {
		status = Pipe::Status::IN_REPAIR;
		return in;
	}
	throw std::invalid_argument("Pipe status should be \"working\" or \"in_repair\"");
}

void print(const Pipe& pipe, std::ostream& stream, bool pretty) {
	print_value(stream, pipe.getName(), "Name:                         ", pretty);
	print_value(stream, pipe.getLength(), "Length:                       ", pretty);
	print_value(stream, pipe.getDiameter(), "Diameter:                     ", pretty);
	print_value(stream, pipe.getStatus(), "Status:                       ", pretty);
}

Pipe input_pipe(std::istream& in) {
	Pipe pipe;

	input_and_set<InputStringWithSpaces>(
		in,
		[&pipe](const std::string& value) { pipe.setName(value); },
		"Enter name: ");
	
	input_and_set<double>(
		in,
		[&pipe](double value) { pipe.setLength(value); },
		"Enter length: ");

	input_and_set<int>(
		in,
		[&pipe](int value) { pipe.setDiameter(value); },
		"Enter diameter: ");

	input_and_set<Pipe::Status>(
		in,
		[&pipe](Pipe::Status value) { pipe.setStatus(value); },
		"Enter pipe status(\"working\" or \"in_repair\"): ");
	
	return pipe;
}

const std::string& Pipe::getName() const {
	return name_;
}
double Pipe::getLength() const {
	return length_;
}
int Pipe::getDiameter() const {
	return diameter_;
}
Pipe::Status Pipe::getStatus() const {
	return status_;
}

void Pipe::setName(const std::string& name) {
	if (name.empty()) {
		throw std::invalid_argument("Pipe name should not be empty");
	}
	name_ = name;
}
void Pipe::setLength(double length) {
	if (length < 1.0) {
		throw std::invalid_argument("Pipe length should be >= 1");
	}
	length_ = length;
}
void Pipe::setDiameter(int diameter) {
	if (diameter < 1) {
		throw std::invalid_argument("Pipe diameter should be >= 1");
	}
	diameter_ = diameter;
}
void Pipe::setStatus(Status status) {
	status_ = status;
}