#ifndef Pattern_h
#define Pattern_h

#include <iostream>

template <typename Type>
Type validity_enter(Type low, Type high) {
	Type x;
	std::cin >> x;
	while (!std::cin || std::cin.peek() != '\n' || x < low || x> high) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Error, try again" << std::endl;
		std::cin >> x;
	}
	return x;
}
#endif