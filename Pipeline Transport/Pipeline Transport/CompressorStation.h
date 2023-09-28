#ifndef CompressorStation_h
#define CompressorStation_h

#include <vector>

struct CompressorStation {
	std::string name;
	int number_of_workshop;
	int number_of_use_workshop;
	int effectiveness;

	CompressorStation();
};

CompressorStation add_CompressorStation();
void push_CS_in_file(CompressorStation station);
void view_all_stations(CompressorStation station);
void load_all_stations(CompressorStation& station);
void edit_station(CompressorStation& station);


#endif