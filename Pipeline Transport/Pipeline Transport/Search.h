#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Data.h"
#include "Pipe.h"
#include <functional>

class Search {
public:

	template<typename Type>
	using Filter = std::function<bool (const Type& obj)>;

	template <typename Type>
	static std::vector<Data::ID> search_by_filter(const Data& data, const Filter<Type>& f) {
		std::vector<Data::ID> result;
		const auto& objects = data.getAll<Type>();
		for (const auto& [id, obj] : objects) {
			if (f(obj)) {
				result.push_back(id);
			}
		}
		return result;
	}

	template <typename Type>
	static std::vector<Data::ID> search_by_id(const Data& data, const std::unordered_set<Data::ID>& ids) {
		std::vector<Data::ID> result;
		const auto& objects = data.getAll<Type>();
		for (Data::ID id : ids) {
			if (objects.find(id) != objects.end()) {
				result.push_back(id);
			}
		}
		return result;
	}
};