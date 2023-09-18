#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <vector>

#include "Pattern.h"
#include "Pipe.h"

Pipe::Pipe() {
	name = "None";
	length = 0;
	diameter = 0;
	in_repair = false;
}

Pipe::Pipe(std::string name_pipe, double length_pipe, int diameter_pipe, bool in_repair_pipe) {
	this->name = name_pipe;
	this->length = length_pipe;
	this->diameter = diameter_pipe;
	this->in_repair = in_repair_pipe;
}

void push_pipe_in_file(std::vector <Pipe>& pipes) {
	std::fstream file;
	file.open("pipes.txt");
	if (file.is_open()) {
		for (auto pipe : pipes) {
			file << pipe.name << std::endl << pipe.length << std::endl << pipe.diameter << std::endl << pipe.in_repair << std::endl;	
		}
	}
	file.close();
	pipes.clear();
}

Pipe add_Pipe() {
	system("cls");
	std::cin.ignore(1000, '\n');

	Pipe pipe;
	std::cout << "--------------------Adding Pipe--------------------" << std::endl;

	std::cout << "Enter name: ";
	std::getline(std::cin, pipe.name);

	std::cout << "Enter length(m): ";
	pipe.length = validity_enter(0.0,100000.0);

	std::cout << "Enter diameter: ";
	pipe.diameter = validity_enter(0,10000);

	std::cout << "Pipe in repair? (0 - No; 1 - Yes): ";
	pipe.in_repair = validity_enter(0, 1);

	return pipe;
}

Pipe read_pipe_from_file() {
	Pipe pipe;
	std::ifstream file;
	file.open("pipes.txt");
	if (file.is_open()) {
		file >> pipe.name >> pipe.length >> pipe.diameter >> pipe.in_repair;
	}
	file.close();
	return pipe;
}

void view_all_pipes(std::vector <Pipe> pipes) {
	std::cout << "\tPipes" << std::endl;
	for (auto pipe : pipes) {
		std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(10) << pipe.name << std::endl;
		std::cout << std::left << std::setw(30) << "Length:" << std::left << std::setw(10) << pipe.length << std::left << std::endl;
		std::cout << std::left << std::setw(30) << "Diameter:" << std::left << std::setw(10) << pipe.diameter << std::endl;
		std::cout << std::left << std::setw(30) << "In repair? (0 - No; 1 - Yes):" << std::left << std::setw(10) << pipe.in_repair << std::endl;
		std::cout << "----------------------------\n";
	}
	
}
