#include <vector>
#include <unordered_set>

#include "Data.h"
#include "PipeSearch.h"

PipeSearch::PipeSearch(const Data& data) {
	this->data = &data;
}

std::vector<Data::ID> PipeSearch::searchByName(const std::string& name) const {
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

std::vector<Data::ID> PipeSearch::searchByStatus(const Pipe::Status& status) const {
	std::vector<Data::ID> result;

	for (const std::pair<Data::ID, Pipe>& item : data->getPipes()) {
		if (item.second.getStatus() == status) {
			result.push_back(item.first);
		}
	}

	return result;
}

std::vector<Data::ID> PipeSearch::searchByID(const std::unordered_set<Data::ID>& id) const {
	std::vector<Data::ID> result;
	for (const Data::ID i : id) {
		if (data->getPipes().find(i) != data->getPipes().end()) {
			result.push_back(i);
		}
	}

	return result;
}