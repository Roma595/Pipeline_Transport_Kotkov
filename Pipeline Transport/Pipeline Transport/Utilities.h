#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

bool log_begin(const std::string& message, std::ostream& log);

bool log_end(const std::string& message, std::ostream& log);

#define WRAP_FOR_LOGGING(message, log) \
	for (bool _run = log_begin(message, log); _run; _run = log_end(message, log))

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

template <typename T>
class InputSequence {
public:
	explicit InputSequence(const std::string& end_keyword) {
		end_keyword_ = end_keyword;
	}

	const std::vector<T>& getElements() const {
		return elements_;
	}

	friend std::istream& operator>>(std::istream& stream, InputSequence& s) {
		std::string str;
		while (true){
			stream >> std::ws;
			stream >> str;
			if (str == s.end_keyword_) {
				break;
			}
			std::istringstream ss(str);
			T new_item;
			ss >> new_item;
			s.elements_.push_back(new_item);
		}
		return stream;
	}

private:
	std::string end_keyword_;
	std::vector<T> elements_;
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

template <typename T>
void validate_by_range(const T& value, const T& low, const T& high) {
	if (value < low || high < value) {
		throw std::invalid_argument("Value should be between "+ std::to_string(low) +" and " + std::to_string(high));
	}
}