#ifndef CompressorStation_h
#define CompressorStation_h

#include <iostream>

struct CompressorStation {
	std::string name;
	int number_of_workshop;
	int number_of_use_workshop;
	int effectiveness;

	CompressorStation();
	CompressorStation(std::string name_cs, int number_of_workshop, int number_of_use_workshop, int effectiveness);
};

void add_CompressorStation();
void push_CS_in_file(CompressorStation CS);
void view_all_stations();



#endif