#include <iostream>
#include <fstream>

#include "Utilities.h"
#include "Data.h"
#include "PipeSearch.h"
#include "StationSearch.h"

void printMainMenu() {
    std::cout << "1. Add Pipe" << std::endl;
    std::cout << "2. Add CS" << std::endl;
    std::cout << "3. View all objects" << std::endl;
    std::cout << "4. Search pipe" << std::endl;
    std::cout << "5. Search station" << std::endl;
    std::cout << "6. Save" << std::endl;
    std::cout << "7. Load" << std::endl;
    std::cout << "0. Exit" << std::endl;
}
void printSearchPipesMenu() {
    std::cout << "1. Print Pipes" << std::endl;
    std::cout << "2. Delete Pipes" << std::endl;
    std::cout << "3. Edit Pipes" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}
void printSearchStationsMenu() {
    std::cout << "1. Print Stations" << std::endl;
    std::cout << "2. Delete Stations" << std::endl;
    std::cout << "3. Edit Stations" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}
void printSearchPipe() {
    std::cout << "1. Search by name" << std::endl;
    std::cout << "2. Search by status" << std::endl;
    std::cout << "3. Search by ID" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}
void printSearchStation() {
    std::cout << "1. Search by name" << std::endl;
    std::cout << "2. Search by workshops" << std::endl;
    std::cout << "3. Search by ID" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}

void search_pipes_by_name(PipeSearch& search, std::vector<Data::ID>& found_pipes) {
    std::string name;
    input_and_set<std::string>(
        std::cin,
        [&name](std::string value) {name = value; },
        "Enter name: "
    );
    found_pipes = search.searchByName(name);
}
void search_pipes_by_status(PipeSearch& search, std::vector<Data::ID>& found_pipes) {
    Pipe::Status status;
    input_and_set<Pipe::Status>(
        std::cin,
        [&status](Pipe::Status value) {status = value; },
        "Enter status (working or in_repair): "
    );
    found_pipes = search.searchByStatus(status);
}
void search_pipes_by_id(PipeSearch& search, std::vector<Data::ID>& found_pipes) {
    InputSequence<Data::ID> ids("e");
    std::cout << "Enter ids (ending with 'e' with space): ";
    std::cin >> ids;
    std::unordered_set<Data::ID> ids_set(ids.getElements().begin(), ids.getElements().end());
    found_pipes = search.searchByID(ids_set);
}
void print_pipes_from_array(Data& data, std::vector<Data::ID>& found_pipes) {
    for (Data::ID id : found_pipes) {
        const Pipe& pipe = data.getPipeById(id);
        print_value(std::cout, id, "ID: ", true);
        print(pipe, std::cout, true);
        std::cout << std::endl;
    }
}
void delete_pipes(Data& data, std::vector<Data::ID>& found_pipes) {
    for (Data::ID id : found_pipes) {
        data.delete_pipe(id);
    }
    std::cout << "Deletion successful\n" << std::endl;
}
void edit_pipes(Data& data, std::vector<Data::ID>& found_pipes) {
    Pipe::Status status;
    input_and_set<Pipe::Status>(
        std::cin,
        [&status](Pipe::Status value) {status = value; },
        "Enter new status for pipes (working or in_repair): "
    );
    for (Data::ID id : found_pipes) {
        data.getPipeById(id).setStatus(status);
    }
}

void search_stations_by_name(StationSearch& search, std::vector<Data::ID>& found_stations) {
    std::string name;
    input_and_set<std::string>(
        std::cin,
        [&name](std::string value) {name = value; },
        "Enter name: "
    );
    found_stations = search.searchByName(name);
}
void search_stations_by_percent(StationSearch& search, std::vector<Data::ID>& found_stations) {
    float low, high;
    input_and_set<float>(
        std::cin,
        [&low](float value) { validate_by_range(value, 0.0f, 100.f); low = value; },
        "Enter low percent: "
    );

    input_and_set<float>(
        std::cin,
        [&high](float value) { validate_by_range(value, 0.0f, 100.f); high = value; },
        "Enter high percent: "
    );
    found_stations = search.searchByWorkshopsPercent(low, high);
}
void search_stations_by_id(StationSearch& search, std::vector<Data::ID>& found_stations) {
    InputSequence<Data::ID> ids("e");
    std::cout << "Enter ids (ending with 'e' with space): ";
    std::cin >> ids;
    std::unordered_set<Data::ID> ids_set(ids.getElements().begin(), ids.getElements().end());
    found_stations = search.searchByID(ids_set);
}
void print_stations_from_array(Data& data, std::vector<Data::ID>& found_stations) {
    for (Data::ID id : found_stations) {
        const CompressorStation& station = data.getStationById(id);
        print_value(std::cout, id, "ID: ", true);
        print(station, std::cout, true);
        std::cout << std::endl;
    }
}
void delete_stations(Data& data, std::vector<Data::ID>& found_stations) {
    for (Data::ID id : found_stations) {
        data.delete_station(id);
    }
    std::cout << "Deletion successful\n" << std::endl;
}
void edit_stations(Data& data, std::vector<Data::ID>& found_stations) {
    float percent;
    input_and_set<float>(
        std::cin,
        [&percent](float value) {validate_by_range(value, 0.0f, 100.f); percent = value; },
        "Enter percent of use workshops: "
    );
    for (Data::ID id : found_stations) {
        CompressorStation& station = data.getStationById(id);
        int workshops_in_use = static_cast<int>(station.getWorkshops() * percent / 100);
        station.setWorkshopsInUse(workshops_in_use);
    }
}

void workWithSearchPipeMenu(Data& data, std::ofstream& log) {
    if (!data.getPipes().empty()) {
        int option = 0;
        std::vector<Data::ID> found_pipes;

        PipeSearch search(data);
        printSearchPipe();
        std::cout << "\n>";
        std::cin >> option;
        switch (option) {
        case 1:
            WRAP_FOR_LOGGING("search_pipes_by_name", log) {
                search_pipes_by_name(search, found_pipes);
            }
            break;
        case 2:
            WRAP_FOR_LOGGING("search_pipes_by_status", log) {
                search_pipes_by_status(search, found_pipes);
            }
            break;
        case 3:
            WRAP_FOR_LOGGING("search_pipes_by_id", log) {
                search_pipes_by_id(search, found_pipes);
            }
            break;
        case 0:
            return;
        }

        std::cout << "\nFound: " << found_pipes.size() << " pipes.\n" << std::endl;

        if (found_pipes.size() != 0) {
            do {

                printSearchPipesMenu();
                std::cout << "\n>";
                std::cin >> option;
                switch (option) {
                case 1:
                    WRAP_FOR_LOGGING("print_pipes_from_array", log) {
                        print_pipes_from_array(data, found_pipes);
                    }
                    break;
                case 2:
                    WRAP_FOR_LOGGING("delete_pipes", log) {
                        delete_pipes(data, found_pipes);
                    }
                    return;
                case 3:
                    WRAP_FOR_LOGGING("edit_pipes", log) {
                        edit_pipes(data, found_pipes);
                    }
                    break;
                case 0:
                    return;
                }

            } while (option != 0);
        }
    }
    else {
        std::cout << "Data is empty." << std::endl;
        return;
    }
    
}

void workWithSearchStationMenu(Data& data, std::ofstream& log) {
    if (!data.getStations().empty()) {
        std::vector<Data::ID> found_stations;
        int option = 0;

        StationSearch search(data);
        printSearchStation();
        std::cout << "\n>";
        std::cin >> option;
        switch (option) {
        case 1:
            WRAP_FOR_LOGGING("search_stations_by_name", log) {
                search_stations_by_name(search, found_stations);
            }
            break;
        case 2:
            WRAP_FOR_LOGGING("search_stations_by_percent", log) {
                search_stations_by_percent(search, found_stations);
            }
            break;
        case 3:
            WRAP_FOR_LOGGING("search_stations_by_id", log) {
                search_stations_by_id(search, found_stations);
            }
            break;
        case 0:
            return;
        }

        std::cout << "\nFound: " << found_stations.size() << " stations.\n" << std::endl;

        if (found_stations.size() != 0) {
            do {
                printSearchStationsMenu();
                std::cout << "\n>";
                std::cin >> option;
                switch (option) {
                case 1:
                    WRAP_FOR_LOGGING("print_stations_from_array", log) {
                        print_stations_from_array(data, found_stations);
                    }
                    break;
                case 2:
                    WRAP_FOR_LOGGING("delete_stations", log) {
                        delete_stations(data, found_stations);
                    }
                    return;
                case 3:
                    WRAP_FOR_LOGGING("edit_stations", log) {
                        edit_stations(data, found_stations);
                    }
                    break;
                case 0:
                    return;
                }

            } while (option != 0);
        }
    }
    else {
        std::cout << "Data is empty." << std::endl;
        return;
    }
}

std::string enter_filename() {
    std::string file_name;
    input_and_set<std::string>(
        std::cin,
        [&file_name](std::string value) { file_name = value; },
        "Enter file name ( filename.txt ): "
    );
    return file_name;
}

void save_to_file(const Data& data) {
    if (!data.getPipes().empty() || !data.getStations().empty()) {
        std::ofstream file(enter_filename());
        if (!file) {
            std::cout << "Error, can't open file" << std::endl;
            return;
        }
        print(data, file, false);
        std::cout << "Saving successfully\n" << std::endl;
    }
    else {
        std::cout << "Data is empty." << std::endl;
        return;
    }
}

void load_from_file(Data& data) {
    std::ifstream file(enter_filename());
    if (!file) {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }
    data = input_data(file);
    std::cout << "Loading successfully\n" << std::endl;
}

void add_pipe(Data& data) {
    Pipe pipe = input_pipe(std::cin);
    int id = data.add_pipe(pipe);
    std::cout << "\nAdd pipe with ID = " << id << std::endl;
}

void add_station(Data& data) {
    CompressorStation station = input_station(std::cin);
    int id = data.add_station(station);
    std::cout << "\nAdd station with ID = " << id << std::endl;
}
void view_all_data(Data& data) {
    if (!data.getPipes().empty() || !data.getStations().empty()) {
        print(data, std::cout, true);
    }
    else {
        std::cout << "Data is empty." << std::endl;
    }
}

void work_with_main_menu() {
    std::ofstream log("log.txt");
    Data data;
    int option = 0;
    Data::ID id = 0;
    do {
        printMainMenu();
        std::cout << "\n>";
        std::cin >> option;
        switch (option)
        {
        case 1:  
            WRAP_FOR_LOGGING("add_pipe", log) {
                add_pipe(data);
            }
            break;
        case 2:         
            WRAP_FOR_LOGGING("add_station", log) {
                add_station(data);
            }
            break;
        case 3:       
            WRAP_FOR_LOGGING("print", log) {
                view_all_data(data);
            }
            break;
        case 4:
            WRAP_FOR_LOGGING("searchPipe", log) {
                workWithSearchPipeMenu(data, log);
            }
            break;
        case 5:      
            WRAP_FOR_LOGGING("searchStation", log) {
                workWithSearchStationMenu(data, log);
            }
            break;
        case 6:         
            WRAP_FOR_LOGGING("Save", log) {
                save_to_file(data);
            }
            break;
        case 7:    
            WRAP_FOR_LOGGING("Load", log) {
                load_from_file(data);
            }
            break;
        case 0:
            return;
        default:
            std::cout << "Error, option number should be from 0 to 7" << std::endl;
            break;
        }
    } while (option != 0);
}


