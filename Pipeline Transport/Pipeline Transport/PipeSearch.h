#pragma once

#include <vector>
#include <unordered_set>
#include "Data.h"


class PipeSearch {
public:
	explicit PipeSearch(const Data& data);

	std::vector<Data::ID> searchByName(const std::string& name) const;

	std::vector<Data::ID> searchByStatus(const Pipe::Status& status) const;

	std::vector<Data::ID> searchByID(const std::unordered_set<Data::ID>& id) const;

private:
	const Data* data;
};
