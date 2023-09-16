#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdio>

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

void push_pipe_in_file(Pipe pipe) {
	std::fstream file;
	file.open("pipes.txt", std::ios::app);
	if (file.is_open()) {
		file << pipe.name << std::endl << pipe.length << std::endl << pipe.diameter << std::endl << pipe.in_repair << std::endl;
	}
	file.close();
}

void add_Pipe() {

	Pipe pipe;
	std::cout << "--------------------Adding Pipe--------------------" << "\n";

	std::cout << "Enter name: ";
	std::getline(std::cin,pipe.name);

	std::cout << "Enter length: ";
	pipe.length = validity_enter(0.0,100000.0);

	std::cout << "Enter diameter: ";
	pipe.diameter = validity_enter(0,10000);

	std::cout << "Pipe in repair? (0 - No; 1 - Yes): ";
	pipe.in_repair = validity_enter(0, 1);

	push_pipe_in_file(pipe);

}

void save_Pipes(std::vector<Pipe> pipes) {
	std::fstream file;
	file.open("pipes.txt");
	if (file.is_open()) {
		for (const Pipe& pipe : pipes) {
			file << pipe.name << " " << pipe.length << std::endl;
		}
	}
	file.close();

	std::cout << "Pipes saved"<<"\n";
}

void read_Pipes() {
	std::vector<Pipe> new_pipes;
	std::ifstream file("pipes.txt");
	if (file.is_open()) {
		std::string name;
		double length;

		while (file >> name >> length) {
			new_pipes.push_back(Pipe{ name,0,0,false });
		}
	}
	file.close();

	for (const Pipe& pipe : new_pipes) {
		std::cout << "Name pipe " << pipe.name<<"\n";
	}
}
