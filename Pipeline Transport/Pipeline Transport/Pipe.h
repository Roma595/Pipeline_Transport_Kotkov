#pragma once

#include <iostream>
#include <string>


class Pipe{	
public:

	void input_pipe();

	void input_pipe_without_diameter(int diameter);

	void print(std::ostream& stream, bool pretty);
	void export_pipe(std::istream& in);

	const std::string& getName() const;
	double getLength() const;
	int getDiameter() const;
	bool getStatus() const;

	double getCapacity() {
		int lenght = _length ;
		double diameter = _diameter / 1000.0;
		int V = 10;

		double capacity = (V * 3.14 * diameter * diameter) * lenght / 4;

		return (_status ? capacity : 0.0);
	}

	double getWeigth() {
		return _status ? _length : 0.0;
	}

	void setName(const std::string& name);
	void setLength(double length);
	void setDiameter(int diameter);
	void setStatus(bool status);

private:
	std::string _name = "None";
	double _length = 1;
	int _diameter = 1;
	bool _status = false;

};


