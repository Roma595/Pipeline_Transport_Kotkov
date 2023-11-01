#include "Utilities.h"

std::string read_line(std::istream& stream) {
	std::string s;
	std::getline(stream, s);

	return s;
}

bool log_begin(const std::string& message, std::ostream& log) {
	log << message << "..." << std::endl;
	return true;
}

bool log_end(const std::string& message, std::ostream& log) {
	log << message << ": success" << std::endl;
	return false;
}