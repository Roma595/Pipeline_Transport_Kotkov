#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Data.h"

template <typename T>
void print_value(std::ostream& stream, const T& value, const std::string& caption, bool pretty) {
	if (pretty) {
		stream << caption << value << std::endl;
	}
	else {
		stream << value << std::endl;
	}
}

template <typename Type>
std::vector<Data::ID> Search_by_id(std::unordered_set<Data::ID>& ids, const std::unordered_map<Data::ID, Type>& objects) {
	std::vector<Data::ID> result;
	for (Data::ID id : ids) {
		if (objects.find(id) != objects.end()) {
			result.push_back(id);
		}
	}
	return result;
}

template <typename Type>
std::vector<Data::ID> Search_by_name(std::string& name, const std::unordered_map<Data::ID, Type>& objects) {
	std::vector<Data::ID> result;
	std::string::size_type n;

	for (const std::pair<Data::ID, Type> pair : objects) {
		n = pair.second.getName().find(name);
		if (std::string::npos != n) {
			result.push_back(pair.first);
		}
	}

	return result;
}

template <typename Type>
Type& get_by_id_from_map(Data::ID id, std::unordered_map<Data::ID, Type>& array) {
	auto it = array.find(id);
	if (it == array.end()) {
		std::cout << "Not found object by id" << std::endl;
	}
	return it->second;
}

template <typename Type>
void print_from_map_by_ids(std::vector<Data::ID>& found_objects, std::unordered_map<Data::ID, Type>& array) {
	for (Data::ID id : found_objects) {
		Type& object = get_by_id_from_map(id, array);
		print_value(std::cout, id, "ID: ", true);
		object.print(std::cout, true);
		std::cout << std::endl;
	}
}

template <typename Type>
void delete_from_map_by_ids(std::vector<Data::ID>& found_objects, std::unordered_map<Data::ID, Type>& array) {
	for (Data::ID id : found_objects) {
		auto it = array.find(id);
		if (it == array.end()) {
			std::cout << "Error";
		}
		array.erase(it);
	}
}

std::string read_line(std::istream& stream);

template <typename Type>
bool validity_enter(std::istream& stream, Type& value, Type low, Type high) {
	Type x;
	stream >> x;
	if (!stream || stream.peek() != '\n' || x < low || x> high) {
		stream.clear();
		stream.ignore(1000, '\n');
		return false;
	}
	value = x;
	return true;
}

template <typename Type>
Type validity_enter_interactive(Type low, Type high) {
	Type x;
	while (!validity_enter(std::cin, x, low, high)) {
		std::cout << "Error, enter value between " << low << " and " << high << std::endl;
	}
	return x;
}