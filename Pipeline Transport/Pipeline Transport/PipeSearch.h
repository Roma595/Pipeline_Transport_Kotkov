#pragma once

#include <vector>
#include <unordered_set>
#include "Data.h"


class PipeSearch {
public:
	explicit PipeSearch(const Data& data) {
		this->data = &data;
	}

	std::vector<Data::ID> searchByName(const std::string& name) const{
		std::vector<Data::ID> result;
		std::string::size_type n;

		for (const std::pair<Data::ID, Pipe>& item : data->getPipes()) {
			n = item.second.getName().find(name);
			if (std::string::npos != n) {
				result.push_back(item.first);
			}
		}

		return result;
	}

	std::vector<Data::ID> searchByStatus(const Pipe::Status& status) const {
		std::vector<Data::ID> result;

		for (const std::pair<Data::ID, Pipe>& item : data->getPipes()) {
			if (item.second.getStatus() == status) {
				result.push_back(item.first);
			}
		}

		return result;
	}

	std::vector<Data::ID> searchByID(const std::unordered_set<Data::ID>& id) const {
		std::vector<Data::ID> result;
		for (const Data::ID i : id) {
			if (data->getPipes().find(i) != data->getPipes().end()) {
				result.push_back(i);
			}
		}

		return result;
	}

private:
	const Data* data;
};
