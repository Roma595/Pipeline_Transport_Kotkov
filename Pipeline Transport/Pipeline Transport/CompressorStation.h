#pragma once

#include <string>
#include <iostream>

class CompressorStation {

public:
	void input_station();
	void print(std::ostream& stream, bool pretty);
	void export_station(std::istream& in);

	const std::string& getName() const;
	int getWorkshops() const;
	int getWorkshopsInUse() const;
	int getEffectiveness() const;

	void setName(const std::string& name);
	void setWorkshops(int workshops);
	void setWorkshopsInUse(int workshops_in_use);
	void setEffectiveness(int effectiveness);

private:
	std::string _name = "None";
	int _workshops = 1;
	int _workshops_in_use = 1;
	int _effectiveness = 1;
};


