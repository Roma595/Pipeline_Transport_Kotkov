#pragma once

#include <vector>
#include <unordered_set>
#include "Data.h"


class StationSearch {
public:
	explicit StationSearch(const Data& data);

	std::vector<Data::ID> searchByName(const std::string& name) const;

	std::vector<Data::ID> searchByWorkshopsPercent(float low_percent, float high_percent) const;

	std::vector<Data::ID> searchByID(const std::unordered_set<Data::ID>& id) const;

private:
	const Data* data;
};

