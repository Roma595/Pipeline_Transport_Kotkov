#pragma once

#include <string>
#include <iostream>

class CompressorStation {

public:

	const std::string& getName() const {
		return name_;
	}
	int getWorkshops() const {
		return workshops_;
	}
	int getWorkshopsInUse() const {
		return workshops_in_use_;
	}
	int getEffectiveness() const {
		return effectiveness_;
	}

	void setName(const std::string& name) {
		if (name.empty()) {
			throw std::invalid_argument("Station name should not be empty");
		}
		name_ = name;
	}
	void setWorkshops(int workshops) {
		if (workshops < 1) {
			throw std::invalid_argument("Number of workshops in station should be >= 1");
		}
		workshops_ = workshops;
	}
	void setWorkshopsInUse(int workshops_in_use) {
		if (workshops_in_use < 0) {
			throw std::invalid_argument("Number of workshops in use in station should not be negative");
		}
		if (workshops_in_use > workshops_) {
			throw std::invalid_argument("Number of workshops in use in station should not be < workshops");
		}
		workshops_in_use_ = workshops_in_use;
	}
	void setEffectiveness(int effectiveness) {
		if (effectiveness < 1 || effectiveness >10) {
			throw std::invalid_argument("Effectiveness of station should be between 1 to 10");
		}
		effectiveness_ = effectiveness;
	}

private:
	std::string name_ = "None";
	int workshops_ = 1;
	int workshops_in_use_ = 1;
	int effectiveness_ = 1;

};

void print(const CompressorStation& station, std::ostream& stream, bool pretty);
CompressorStation input_station(std::istream& in);

