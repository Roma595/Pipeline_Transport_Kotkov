#include <fstream>
#include <string>
#include <iomanip>
#include "CompressorStation.h"
#include "Pattern.h"

CompressorStation::CompressorStation() {
	name = "None";
	number_of_workshop = 0;
	number_of_use_workshop = 0;
	effectiveness = 0;
}

CompressorStation::CompressorStation(std::string name, int number_of_workshop, int number_of_use_workshop,int effectiveness) {
	this->name = name;
	this->number_of_workshop = number_of_workshop;
	this->number_of_use_workshop = number_of_use_workshop;
	this->effectiveness = effectiveness;
}

void push_CS_in_file(CompressorStation CS) {
	std::fstream file;
	file.open("compressor_stations.txt");
	if (file.is_open()) {
		file << CS.name << std::endl << CS.number_of_workshop << std::endl << CS.number_of_use_workshop << std::endl << CS.effectiveness << std::endl;
		file << std::endl;
	}
	file.close();
}

void add_CompressorStation() {
	system("cls");
	std::cin.ignore(1000, '\n');

	CompressorStation CS;
	std::cout << "--------------------Adding CompressorStation--------------------" << "\n";

	std::cout << "Enter name: ";
	std::getline(std::cin, CS.name);

	std::cout << "Enter number of workshop: ";
	CS.number_of_workshop = validity_enter(0, 100000);

	std::cout << "Enter number of use workshop: ";
	CS.number_of_use_workshop = validity_enter(0, 100000);

	std::cout << "Enter effectiveness(1-10): ";
	CS.effectiveness = validity_enter(1, 10);

	push_CS_in_file(CS);
}

void view_all_stations() {
	std::cout << "\tCompressor stations"<< std::endl;
	CompressorStation CS;
	std::ifstream file;
	file.open("compressor_stations.txt");
	if (file.is_open()) {
		file.read((char*)&CS, sizeof(CS));
		std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(10) << CS.name << std::endl;
		std::cout << std::left << std::setw(30) << "Number of workshops:" << std::left << std::setw(10) << CS.number_of_workshop << std::left << std::endl;
		std::cout << std::left << std::setw(30) << "Number of use workshops:" << std::left << std::setw(10) << CS.number_of_use_workshop << std::endl;
		std::cout << std::left << std::setw(30) << "Effectiveness:" << std::left << std::setw(10) << CS.effectiveness << std::endl;

	}
	file.close();
	
}