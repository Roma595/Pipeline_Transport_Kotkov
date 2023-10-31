#pragma once

#include <vector>
#include <unordered_set>
#include "Data.h"


class StationSearch {
public:
	explicit StationSearch(const Data& data) {
		this->data = &data;
	}

	std::vector<Data::ID> searchByName(const std::string& name) const {
		std::vector<Data::ID> result;
		std::string::size_type n;

		for (const std::pair<Data::ID, CompressorStation>& item : data->getStations()) {
			n = item.second.getName().find(name);
			if (std::string::npos != n) {
				result.push_back(item.first);
			}
		}

		return result;
	}

	std::vector<Data::ID> searchByWorkshopsPercent(float low_percent, float high_percent) const {
		std::vector<Data::ID> result;

		for (const std::pair<Data::ID, CompressorStation>& item : data->getStations()) {
			float percent = static_cast<float>(item.second.getWorkshopsInUse())*100 / item.second.getWorkshops();
			if (percent >= low_percent && percent <= high_percent) {
				result.push_back(item.first);
			}
		}

		return result;
	}

	std::vector<Data::ID> searchByID(const std::unordered_set<Data::ID>& id) const {
		std::vector<Data::ID> result;
		for (const Data::ID i : id) {
			if (data->getStations().find(i) != data->getStations().end()) {
				result.push_back(i);
			}
		}
		return result;
	}

private:
	const Data* data;
};

