#pragma once

#include <string>
#include <iostream>

class CompressorStation {

public:

	const std::string& getName() const;
	int getWorkshops() const;
	int getWorkshopsInUse() const;
	int getEffectiveness() const;

	void setName(const std::string& name);
	void setWorkshops(int workshops);
	void setWorkshopsInUse(int workshops_in_use);
	void setEffectiveness(int effectiveness);

private:
	std::string name_ = "None";
	int workshops_ = 1;
	int workshops_in_use_ = 1;
	int effectiveness_ = 1;

};

void print(const CompressorStation& station, std::ostream& stream, bool pretty);
CompressorStation input_station(std::istream& in);

