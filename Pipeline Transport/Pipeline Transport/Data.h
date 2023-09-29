#pragma once
#include <optional>
#include <iostream>
#include "CompressorStation.h"
#include "Pipe.h"

struct Data {
	std::optional<Pipe> pipe;
	std::optional<CompressorStation> station;
};

void print(const Data& data, std::ostream& stream);
void pretty_print(const Data& data, std::ostream& stream);
bool input_data(Data& data, std::istream& stream);