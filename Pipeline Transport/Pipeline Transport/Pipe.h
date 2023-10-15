#pragma once

#include <stdexcept>
#include <iostream>


class Pipe{	
public:
	enum Status {
		WORKING,
		IN_REPAIR
	};

	const std::string& getName() const {
		return name_;
	}
	double getLength() const {
		return length_;
	}
	int getDiameter() const {
		return diameter_;
	}
	Status getStatus() const {
		return status_;
	}

	void setName(const std::string& name);
	void setLength(double length) {
		if (length < 1.0) {
			throw std::invalid_argument("Pipe length should be >= 1");
		}
		length_ = length;
	}
	void setDiameter(int diameter) {
		if (diameter < 1) {
			throw std::invalid_argument("Pipe diameter should be >= 1");
		}
		diameter_ = diameter;
	}
	void setStatus(Status status) {
		status_ = status;
	}

private:

	std::string name_ = "None";
	double length_ = 1;
	int diameter_ = 1;
	Status status_ = WORKING;

};

void print(const Pipe& pipe, std::ostream& stream, bool pretty);
Pipe input_pipe(std::istream& in);

std::ostream& operator << (std::ostream& out, Pipe::Status status);
std::istream& operator >> (std::istream& in, Pipe::Status& status);