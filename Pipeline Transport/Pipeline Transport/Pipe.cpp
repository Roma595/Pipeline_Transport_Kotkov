#include <iostream>
#include <string>
#include <iomanip>

#include "Utilities.h"
#include "Pipe.h"

std::string pipe_status(Pipe pipe) {
	return pipe.in_repair ? "in repair" : "works";
}

void print(const Pipe& pipe, std::ostream& stream) {
	stream << pipe.name << std::endl
		<< pipe.length << std::endl
		<< pipe.diameter << std::endl
		<< pipe.in_repair << std::endl;
}

void pretty_print(const Pipe& pipe, std::ostream& stream) {
	stream << std::left << std::setw(30) << "Name:" << std::left << std::setw(10) << pipe.name << std::endl;
	stream << std::left << std::setw(30) << "Length:" << std::left << std::setw(10) << pipe.length << std::left << std::endl;
	stream << std::left << std::setw(30) << "Diameter:" << std::left << std::setw(10) << pipe.diameter << std::endl;
	stream << std::left << std::setw(30) << "Status:" << std::left << std::setw(10) << pipe_status(pipe) << std::endl;
}

bool input_pipe(Pipe& pipe, std::istream& stream) {		
	Pipe input;
	stream >> std::ws;
	std::getline(stream, input.name);
	if (!validity_enter(stream, input.length, 1.0, 100000.0)) {
		return false;
	}
	if (!validity_enter(stream, input.diameter, 1, 10000)) {
		return false;
	}
	int in_repair = 0;
	if (!validity_enter(stream, in_repair, 0, 1)) {
		return false;
	}
	input.in_repair = in_repair;
	pipe = input;
	return true;

}

Pipe input_pipe_interactive() {
	Pipe pipe;
	std::cout << "Enter name: ";							
	std::cin >> std::ws;
	std::getline(std::cin, pipe.name);

	std::cout << "Enter length(m): ";						
	pipe.length = validity_enter_interactive(1.0, 100000.0);

	std::cout << "Enter diameter: ";						
	pipe.diameter = validity_enter_interactive(1, 10000);

	std::cout << "Pipe in repair? (0 - No; 1 - Yes): ";			
	pipe.in_repair = validity_enter_interactive(0, 1);

	return pipe;
}