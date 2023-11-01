#pragma once

#include <stdexcept>
#include <iostream>


class Pipe{	
public:

	enum Status {
		WORKING,
		IN_REPAIR
	};

	const std::string& getName() const;
	double getLength() const;
	int getDiameter() const;
	Status getStatus() const;

	void setName(const std::string& name);
	void setLength(double length);
	void setDiameter(int diameter);
	void setStatus(Status status);

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