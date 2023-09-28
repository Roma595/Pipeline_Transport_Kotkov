#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <vector>

#include "Pattern.h"
#include "Pipe.h"

// ��������� ����������� ��������� Pipe
Pipe::Pipe() {
	name = "None";
	length = 0;
	diameter = 0;
	in_repair = false;
}

// ������� ���������� ���������� ��� ����� ����� Pipe ����� �������
Pipe add_Pipe() {
	std::cin.ignore(1000, '\n');

	Pipe pipe;
	std::cout << "--------------------Adding Pipe--------------------" << std::endl;

	std::cout << "Enter name: ";							//���� �������� �����
	std::getline(std::cin, pipe.name);

	std::cout << "Enter length(m): ";						//���� ������ �����
	pipe.length = validity_enter(0.0, 100000.0);

	std::cout << "Enter diameter: ";						//���� �������� �����
	pipe.diameter = validity_enter(0, 10000);

	std::cout << "Pipe in repair? (0 - No; 1 - Yes): ";		//���� ���-�� "� �������" �����
	pipe.in_repair = validity_enter(0, 1);

	std::cout << "\nThe pipe is successfully added;" << std::endl;

	return pipe;
}

// ������� ���������� ������� Pipe � ����
void push_pipe_in_file(Pipe pipe) {
	if (pipe.length != 0 && pipe.diameter != 0) {	//�������� �� ������� ����� � ���������
		std::fstream file;
		file.open("pipes.txt");
		if (file.is_open()) {
													// ������ ����� � ����
			file << pipe.name << std::endl << pipe.length << std::endl << pipe.diameter << std::endl << pipe.in_repair << std::endl;
		}
		file.close();
		std::cout << "The pipe was successfully saved;" << std::endl;
	}
	else {
		std::cout << "Error, no pipes to save;" << std::endl;
	}
}

// ������� ��� ������ ����� Pipe � �������
void view_all_pipes(Pipe pipe) {
	std::cout << "\tPipes" << std::endl;
	if (pipe.length != 0 && pipe.diameter != 0) {	// �������� ������� ����� � ���������
		std::cout << std::left << std::setw(30) << "Name:" << std::left << std::setw(10) << pipe.name << std::endl;
		std::cout << std::left << std::setw(30) << "Length:" << std::left << std::setw(10) << pipe.length << std::left << std::endl;
		std::cout << std::left << std::setw(30) << "Diameter:" << std::left << std::setw(10) << pipe.diameter << std::endl;
		std::cout << std::left << std::setw(30) << "In repair? (0 - No; 1 - Yes):" << std::left << std::setw(10) << pipe.in_repair << std::endl;
		std::cout << "\n----------------------------\n\n";
	}
	else {
		std::cout << "There is no pipe;" << std::endl;
	}
}

//������� ��� ���������� ����� Pipe �� �����
void load_all_pipes(Pipe& pipe) {
	std::ifstream file;
	file.open("pipes.txt");

	if (file.is_open()) {
		if (file.peek() == EOF) {												// �������� �� ������� ����� � �����
			std::cout << "Error, there is no pipes in file;" << std::endl;
		}
		else {
			std::string str;
			std::getline(file, pipe.name);										//���������� ����� �� �����

			file >> pipe.length >> pipe.diameter >> pipe.in_repair;				//���������� �����, �������� � ���-�� "� ������� �� �����
			
			file.close();
			std::cout << "The pipe was successfully loaded;" << std::endl;
		}
	}
	else {
		std::cout << "Error;" << std::endl;
	}
}

// ������� ��� ��������� ���-�� ����� Pipe "� �������"
void edit_pipe(Pipe& pipe) {
	if (pipe.length != 0 && pipe.diameter !=0) {	// �������� ������� ����� � ���������

		std::cout << "The pipe status (1 - in repair, 0 - works):\t" << pipe.in_repair << std::endl;
		std::cout << "Do you want to change the pipe status? (1 - yes, 0 - no)" << std::endl;
		std::cout << "> ";

		int choice;
		choice = validity_enter(0, 1);
		if (choice == 1) {
			pipe.in_repair = !pipe.in_repair;
		}

		std::cout << "New pipe status (1 - in repair, 0 - works):\t" << pipe.in_repair << std::endl;
	}
	else {
		std::cout << "Erorr, there is no pipe to edit;" << std::endl;
	}
}