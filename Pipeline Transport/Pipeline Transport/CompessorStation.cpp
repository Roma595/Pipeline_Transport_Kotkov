#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "CompressorStation.h"
#include "Pattern.h"

// дефолтный конструктор структуры CompressorStation
CompressorStation::CompressorStation() {
	name = "None";
	number_of_workshop = 0;
	number_of_use_workshop = 0;
	effectiveness = 0;
}

// конструктор структуры CompressorStation
CompressorStation::CompressorStation(std::string name, int number_of_workshop, int number_of_use_workshop,int effectiveness) {
	this->name = name;
	this->number_of_workshop = number_of_workshop;
	this->number_of_use_workshop = number_of_use_workshop;
	this->effectiveness = effectiveness;
}

// функция добавления параметров для новой станции CompressorStation через консоль
CompressorStation add_CompressorStation() {
	std::cin.ignore(1000, '\n');

	CompressorStation station;
	std::cout << "--------------------Adding CompressorStation--------------------" << "\n";

	std::cout << "Enter name: ";								//ввод названия станции
	std::getline(std::cin, station.name);

	std::cout << "Enter number of workshop: ";					//ввод количества цехов станции
	station.number_of_workshop = validity_enter(1, 100000);

	std::cout << "Enter number of use workshop: ";				//ввод количества работающих цехов станции
	station.number_of_use_workshop = validity_enter(0, station.number_of_workshop);

	std::cout << "Enter effectiveness(1-10): ";					//ввод эффективности станции
	station.effectiveness = validity_enter(1, 10);

	std::cout << "\nThe station is successfully added;" << std::endl;

	return station;
}

// функция сохранения обьекта CompressorStation в файл
void push_CS_in_file(CompressorStation station) {
	if (station.name != "None" && station.number_of_workshop != 0) {	// проверка наличия станции в программе
		std::fstream file;
		file.open("compressor_stations.txt");
		if (file.is_open()) {
																		// запись станции в файл
			file << station.name << std::endl << station.number_of_workshop << std::endl << station.number_of_use_workshop << std::endl << station.effectiveness << std::endl;
		}
		file.close();
		std::cout << "The station was successfully saved;" << std::endl;
	}
	else {
		std::cout << "Error, no stations to save;" << std::endl;
	}
	
}

// функция для вывода станции CompressorStation в консоль
void view_all_stations(CompressorStation station) {
	std::cout << "\tCompressor stations"<< std::endl;
	if (station.name != "None" && station.number_of_workshop != 0) {	//проверка наличия станции в программе
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

//функция для считывания станции CompressorStation из файла
void load_all_stations(CompressorStation& station) {
	std::ifstream file;
	file.open("compressor_stations.txt");
	if (file.is_open()) {
		if (file.peek() == EOF) {																			//проверка наличия станции в файле
			std::cout << "Error, there is no stations in file;" << std::endl;
		}
		else {
			std::string str;

			std::getline(file, station.name);																//считывание имени из файла
																								
			file >> station.number_of_workshop >> station.number_of_use_workshop >> station.effectiveness;	//считывание кол-ва цехов, кол-ва работ.
																											//цехов, эффективность из файла
			
			file.close();
			std::cout << "The station was successfully loaded;" << std::endl;
		}
		
	}
	else {
		std::cout << "Error;" << std::endl;
	}
}

// функция для изменения кол-ва работающих цехов станции CompressorStation 
void edit_station(CompressorStation& station) {
	if (station.name != "None" && station.number_of_workshop != 0) {	// проверка наличия станции в программе
		int option;
		std::cout << "The number of workshops in work is " << station.number_of_use_workshop << std::endl;
		std::cout << "If you want to start the workshop press 1, stop - 0" << std::endl;

		option = validity_enter(0, 1);
		//уменьшение кол-ва работающих станций
		if (station.number_of_use_workshop > 0 && option == 0) {
			station.number_of_use_workshop--;
		}
		//увеличение кол-ва работающих станций
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