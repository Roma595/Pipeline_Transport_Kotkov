#pragma once

#include <iostream>
#include <string>

template <typename Type>
bool validity_enter(std::istream& stream, Type& value, Type low, Type high) {
	Type x;
	stream >> x;
	if (!stream || stream.peek() != '\n' || x < low || x> high) {
		stream.clear();
		stream.ignore(1000, '\n');
		return false;
	}
	value = x;
	return true;
}

template <typename Type>
Type validity_enter_interactive(Type low, Type high) {
	Type x;
	while (!validity_enter(std::cin, x, low, high)) {
		std::cout << "Error, enter value between " << low << " and " << high << std::endl;
	}
	return x;
}

std::string read_line(std::istream& stream);