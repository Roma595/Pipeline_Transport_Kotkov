#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Data.h"

class Search {
public:

	template <typename Type>
	static std::vector<Data::ID> search_by_id(std::unordered_set<Data::ID>& ids, const std::unordered_map<Data::ID, Type>& objects) {
		std::vector<Data::ID> result;
		for (Data::ID id : ids) {
			if (objects.find(id) != objects.end()) {
				result.push_back(id);
			}
		}
		return result;
	}

	template <typename Type>
	static std::vector<Data::ID> search_by_name(const std::string& name, const std::unordered_map<Data::ID, Type>& objects) {
		std::vector<Data::ID> result;

		for (const std::pair<Data::ID, Type> pair : objects) {
			std::string::size_type n = pair.second.getName().find(name);
			if (std::string::npos != n) {
				result.push_back(pair.first);
			}
		}
		return result;
	}

	static std::vector<Data::ID> search_pipes_by_status(Data& data, bool status);

	static std::vector<Data::ID> search_stations_by_workshops(Data& data, float low_percent, float high_percent);
};