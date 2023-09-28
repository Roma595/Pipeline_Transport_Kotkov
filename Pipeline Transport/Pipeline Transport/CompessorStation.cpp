#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "CompressorStation.h"
#include "Pattern.h"

// ��������� ����������� ��������� CompressorStation
CompressorStation::CompressorStation() {
	name = "None";
	number_of_workshop = 0;
	number_of_use_workshop = 0;
	effectiveness = 0;
}

// ����������� ��������� CompressorStation
CompressorStation::CompressorStation(std::string name, int number_of_workshop, int number_of_use_workshop,int effectiveness) {
	this->name = name;
	this->number_of_workshop = number_of_workshop;
	this->number_of_use_workshop = number_of_use_workshop;
	this->effectiveness = effectiveness;
}

// ������� ���������� ���������� ��� ����� ������� CompressorStation ����� �������
CompressorStation add_CompressorStation() {
	std::cin.ignore(1000, '\n');

	CompressorStation station;
	std::cout << "--------------------Adding CompressorStation--------------------" << "\n";

	std::cout << "Enter name: ";								//���� �������� �������
	std::getline(std::cin, station.name);

	std::cout << "Enter number of workshop: ";					//���� ���������� ����� �������
	station.number_of_workshop = validity_enter(1, 100000);

	std::cout << "Enter number of use workshop: ";				//���� ���������� ���������� ����� �������
	station.number_of_use_workshop = validity_enter(0, station.number_of_workshop);

	std::cout << "Enter effectiveness(1-10): ";					//���� ������������� �������
	station.effectiveness = validity_enter(1, 10);

	std::cout << "\nThe station is successfully added;" << std::endl;

	return station;
}

// ������� ���������� ������� CompressorStation � ����
void push_CS_in_file(CompressorStation station) {
	if (station.name != "None" && station.number_of_workshop != 0) {	// �������� ������� ������� � ���������
		std::fstream file;
		file.open("compressor_stations.txt");
		if (file.is_open()) {
																		// ������ ������� � ����
			file << station.name << std::endl << station.number_of_workshop << std::endl << station.number_of_use_workshop << std::endl << station.effectiveness << std::endl;
		}
		file.close();
		std::cout << "The station was successfully saved;" << std::endl;
	}
	else {
		std::cout << "Error, no stations to save;" << std::endl;
	}
	
}

// ������� ��� ������ ������� CompressorStation � �������
void view_all_stations(CompressorStation station) {
	std::cout << "\tCompressor stations"<< std::endl;
	if (station.name != "None" && station.number_of_workshop != 0) {	//�������� ������� ������� � ���������
		std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(10) << station.name << std::endl;
		std::cout << std::left << std::setw(30) << "Number of workshops:" << std::left << std::setw(10) << station.number_of_workshop << std::left << std::endl;
		std::cout << std::left << std::setw(30) << "Number of use workshops:" << std::left << std::setw(10) << station.number_of_use_workshop << std::endl;
		std::cout << std::left << std::setw(30) << "Effectiveness:" << std::left << std::setw(10) << station.effectiveness << std::endl;
		std::cout << "\n----------------------------\n\n";
	}
	else {
		std::cout << "There is no stations;" << std::endl;
	}
	
}

//������� ��� ���������� ������� CompressorStation �� �����
void load_all_stations(CompressorStation& station) {
	std::ifstream file;
	file.open("compressor_stations.txt");
	if (file.is_open()) {
		if (file.peek() == EOF) {																			//�������� ������� ������� � �����
			std::cout << "Error, there is no stations in file;" << std::endl;
		}
		else {
			std::string str;

			std::getline(file, station.name);																//���������� ����� �� �����
																								
			file >> station.number_of_workshop >> station.number_of_use_workshop >> station.effectiveness;	//���������� ���-�� �����, ���-�� �����.
																											//�����, ������������� �� �����
			
			file.close();
			std::cout << "The station was successfully loaded;" << std::endl;
		}
		
	}
	else {
		std::cout << "Error;" << std::endl;
	}
}

// ������� ��� ��������� ���-�� ���������� ����� ������� CompressorStation 
void edit_station(CompressorStation& station) {
	if (station.name != "None" && station.number_of_workshop != 0) {	// �������� ������� ������� � ���������
		int option;
		std::cout << "The number of workshops in work is " << station.number_of_use_workshop << std::endl;
		std::cout << "If you want to start the workshop press 1, stop - 0" << std::endl;

		option = validity_enter(0, 1);
		//���������� ���-�� ���������� �������
		if (station.number_of_use_workshop > 0 && option == 0) {
			station.number_of_use_workshop--;
		}
		//���������� ���-�� ���������� �������
		else if (station.number_of_use_workshop < station.number_of_workshop && option == 1) {
			station.number_of_use_workshop++;
		}
		else {
			std::cout << "Error, you cannot start/stop one more workshop" << std::endl;
		}

		std::cout << "Now the number of workshops in work is " << station.number_of_use_workshop << std::endl;
	}

	else {
		std::cout << "Erorr, there is no stations to edit;" << std::endl;
	}
}