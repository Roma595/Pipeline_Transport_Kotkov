#pragma once

#include <iostream>
#include <sstream>
#include <string>

class InputStringWithSpaces {
public:
	operator const std::string& () const {
		return data_;
	}

	friend std::istream& operator>>(std::istream& stream, InputStringWithSpaces& s) {
		std::getline(stream, s.data_);
		return stream;
	}

private:
	std::string data_ = "";
};

template <typename Value, typename Setter>
void input_raw(std::istream& in, const Setter& setter) {
	Value value;
	std::string s;
	in >> std::ws;
	std::getline(in, s);
	std::istringstream ss(s);
	ss >> value;
	if (!ss.eof()) {
		throw std::runtime_error("Invalid input data");
	}
	setter(value);
}

template <typename Value, typename Setter>
void input_interactive(std::istream& in, const Setter& setter) {
	while (true) {
		try {
			input_raw<Value>(in, setter);
			return;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

template <typename Value, typename Setter>
void input_and_set(std::istream& in, const Setter& setter, const std::string& promt) {
	if (&in == &std::cin) {
		std::cout << promt;
		input_interactive<Value>(
			in,
			setter
		);
	}
	else {
		input_raw<Value>(
			in,
			setter
		);
	}
}

template <typename T>
void print_value(std::ostream& stream, const T& value, const std::string& caption, bool pretty) {
	if (pretty) {
		stream << caption << value << std::endl;
	}
	else {
		stream << value << std::endl;
	}
}

std::string read_line(std::istream& stream);