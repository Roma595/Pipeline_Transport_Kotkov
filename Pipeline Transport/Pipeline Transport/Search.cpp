#include "Search.h"
#include "Utilities.h"


std::vector<Data::ID> Search::search_pipes_by_status(Data& data, bool status) {
	std::vector<Data::ID> result;

	for (const std::pair<int, Pipe> pair : data.getPipes()) {
		if (pair.second.getStatus() == status) {
			result.push_back(pair.first);
		}
	}
	return result;
}

std::vector<Data::ID> Search::search_stations_by_workshops(Data& data, float low_percent, float high_percent) {
	std::vector<Data::ID> result;
	for (std::pair<int, CompressorStation> pair : data.getStations()) {
		float percent = get_by_id_from_map(pair.first, data.getStations()).getWorkshopsInUse() * 100 / get_by_id_from_map(pair.first, data.getStations()).getWorkshops();
		if (percent >= low_percent && percent <= high_percent) {
			result.push_back(pair.first);
		}
	}
	return result;
}