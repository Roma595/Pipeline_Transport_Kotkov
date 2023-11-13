#include <iostream>
#include <fstream>
#include <chrono>
#include <format>

#include "Utilities.h"
#include "Data.h"

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

std::unordered_set <Data::ID> Input_sequence() {
    std::unordered_set<Data::ID> ids;
    std::string input;
    while (true) {
        std::cin >> std::ws;
        std::cin >> input;
        if (input == "end") {
            break;
        }
        std::istringstream ss(input);
        int new_item;
        ss >> new_item;
        ids.insert(new_item);
    }
    return ids;
}

//void search_pipes_by_status(PipeSearch& search, std::vector<Data::ID>& found_pipes) {
//    Pipe::Status status;
//    input_and_set<Pipe::Status>(
//        std::cin,
//        [&status](Pipe::Status value) {status = value; },
//        "Enter status (working or in_repair): "
//    );
//    found_pipes = search.searchByStatus(status);
//}
void search_pipes_by_name(Data& data, std::vector<Data::ID>& found_pipes) {
    std::string name;
    std::cout << "Enter name: ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, name);
    found_pipes = Search_by_name(name, data.getPipes());
}

void search_pipes_by_id(Data& data, std::vector<Data::ID>& found_pipes) {
    std::cout << "Enter ids (ending with 'end' with space): ";
    std::unordered_set<Data::ID> ids = Input_sequence();
    found_pipes = Search_by_id(ids, data.getPipes());
}


//void edit_pipes(Data& data, std::vector<Data::ID>& found_pipes) {
//    std::cout << "Enter new status for pipes (1 - work, 0 - in repair): ";
//    bool status = validity_enter_interactive(0, 1);
//    for (Data::ID id : found_pipes) {
//        data.getPipeById(id).setStatus(status);
//    }
//}

void search_stations_by_name(Data& data, std::vector<Data::ID>& found_stations) {
    std::string name;
    std::cout << "Enter name: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, name);
    found_stations = Search_by_name(name, data.getStations());
}
//void search_stations_by_percent(StationSearch& search, std::vector<Data::ID>& found_stations) {
//    float low, high;
//    input_and_set<float>(
//        std::cin,
//        [&low](float value) { validate_by_range(value, 0.0f, 100.f); low = value; },
//        "Enter low percent: "
//    );
//
//    input_and_set<float>(
//        std::cin,
//        [&high](float value) { validate_by_range(value, 0.0f, 100.f); high = value; },
//        "Enter high percent: "
//    );
//    found_stations = search.searchByWorkshopsPercent(low, high);
//}
void search_stations_by_id(Data& data, std::vector<Data::ID>& found_stations) {
    std::cout << "Enter ids (ending with 'end' with space): ";
    std::unordered_set<Data::ID> ids = Input_sequence();
    found_stations = Search_by_id(ids, data.getStations());
}

void edit_stations(Data& data, std::vector<Data::ID>& found_stations) {
    std::cout << "Enter percent of use workshops: ";
    float percent = validity_enter_interactive<float>(0.0, 100.0);
    for (Data::ID id : found_stations) {
        CompressorStation& station = get_by_id_from_map(id, data.getStations());
        int workshops_in_use = (int)(station.getWorkshops() * percent / 100);
        station.setWorkshopsInUse(workshops_in_use);
    }
}



void workWithSearchPipeMenu(Data& data) {
    if (!data.getPipes().empty()) {
        std::vector<Data::ID> found_pipes;

        printSearchPipe();
        std::cout << "\n>";
        int option = validity_enter_interactive(0, 3);
        switch (option) {
        case 1:
            search_pipes_by_name(data, found_pipes);
            break;
        case 2:
            //search_pipes_by_status(search, found_pipes);
            break;
        case 3:
            search_pipes_by_id(data, found_pipes);
            break;
        case 0:
            return;
        }

        std::cout << "\nFound: " << found_pipes.size() << " pipes.\n" << std::endl;

        if (found_pipes.size() != 0) {
            do {
                printSearchPipesMenu();
                std::cout << "\n>";
                option = validity_enter_interactive(0, 3);
                switch (option) {
                case 1:
                    print_from_map_by_ids(found_pipes, data.getPipes());
                    break;
                case 2:
                    delete_from_map_by_ids(found_pipes, data.getPipes());
                    return;
                case 3:
                    //edit_pipes(data, found_pipes);
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

void workWithSearchStationMenu(Data& data) {
    if (!data.getStations().empty()) {
        std::vector<Data::ID> found_stations;

        printSearchStation();
        std::cout << "\n>";
        int option = validity_enter_interactive(0, 3);
        switch (option) {
        case 1:
            search_stations_by_name(data,found_stations);
            break;
        case 2:
            //search_stations_by_percent(search, found_stations);
            break;
        case 3:
            search_stations_by_id(data, found_stations);
            break;
        case 0:
            return;
        }

        std::cout << "\nFound: " << found_stations.size() << " stations.\n" << std::endl;

        if (found_stations.size() != 0) {
            do {
                printSearchStationsMenu();
                std::cout << "\n>";
                option = validity_enter_interactive(0, 3);
                switch (option) {
                case 1:
                    print_from_map_by_ids(found_stations, data.getStations());
                    break;
                case 2:
                    delete_from_map_by_ids(found_stations, data.getStations());
                    return;
                case 3:
                    edit_stations(data, found_stations);
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
    std::cout << "Enter file name (filename.txt): ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, file_name);
    return file_name;
}

void save_to_file(Data& data) {
    if (!data.getPipes().empty() || !data.getStations().empty()) {
        std::ofstream file(enter_filename());
        if (!file) {
            std::cout << "Error, can't open file" << std::endl;
            return;
        }
        data.print(file, false);
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
    data.load_data(file);
    std::cout << "Loading successfully\n" << std::endl;
}

void add_pipe(Data& data) {
    Pipe pipe;
    pipe.input_pipe();
    int id = data.add_pipe(pipe);
    std::cout << "\nAdd pipe with ID = " << id << std::endl;
}
void add_station(Data& data) {
    CompressorStation station;
    station.input_station();
    int id = data.add_station(station);
    std::cout << "\nAdd station with ID = " << id << std::endl;
}

void view_all_data(Data& data) {
    if (!data.getPipes().empty() || !data.getStations().empty()) {
        data.print(std::cout, true);
    }
    else {
        std::cout << "Data is empty." << std::endl;
    }
}


void work_with_main_menu() {
    Data data;
    int option = 0;
    Data::ID id = 0;
    do {
        printMainMenu();
        std::cout << "\n>";
        option = validity_enter_interactive(0, 7);
        switch (option)
        {
        case 1:  
            add_pipe(data);
            break;
        case 2: 
            add_station(data);
            break;
        case 3: 
            view_all_data(data);
            break;
        case 4:
            workWithSearchPipeMenu(data);
            break;
        case 5:      
            workWithSearchStationMenu(data);
            break;
        case 6:         
            save_to_file(data);
            break;
        case 7:    
            load_from_file(data);
            break;
        case 0:
            return;
        default:
            std::cout << "Error, option number should be from 0 to 7" << std::endl;
            break;
        }
    } while (option != 0);
}


