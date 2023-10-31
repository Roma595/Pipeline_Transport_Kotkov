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

void workWithSearchPipeMenu(Data& data) {
    int option = 0;
    std::vector<Data::ID> found_pipes;
   
    PipeSearch search(data);
    printSearchPipe();
    std::cout << "\n>";
    std::cin >> option;
    switch (option) {
    case 1: {
        std::string name;
        input_and_set<std::string>(
            std::cin, 
            [&name](std::string value) {name = value; }, 
            "Enter name: "
        );
        found_pipes = search.searchByName(name);
        break;
    }
    case 2: {
        Pipe::Status status;
        input_and_set<Pipe::Status>(
            std::cin,
            [&status](Pipe::Status value) {status = value; },
            "Enter status (working or in_repair): "
        );
        found_pipes = search.searchByStatus(status);
        break;
    }
    case 3: {
        InputSequence<Data::ID> ids("e");
        std::cout << "Enter ids (ending with 'e' with space): ";
        std::cin >> ids;
        std::unordered_set<Data::ID> ids_set(ids.getElements().begin(), ids.getElements().end());
        found_pipes = search.searchByID(ids_set);
        break;
    }
    case 0:
        return;
    }

    std::cout << "Found: " << found_pipes.size() << " pipes." << std::endl;  

    do {
        
        printSearchPipesMenu();
        std::cout << "\n>";
        std::cin >> option;
        switch (option) {
        case 1:
            for (Data::ID id : found_pipes) {
                const Pipe& pipe = data.getPipeById(id);
                print_value(std::cout, id, "ID: ", true);
                print(pipe, std::cout, true);
                std::cout << std::endl;
            }
            break;
        case 2:
            for (Data::ID id : found_pipes) {
                data.delete_pipe(id);
            }
            return;
        case 3:
            Pipe::Status status;
            input_and_set<Pipe::Status>(
                std::cin,
                [&status](Pipe::Status value) {status = value; },
                "Enter new status for pipe#(working or in_repair): "
            );
            for (Data::ID id : found_pipes) {
                data.getPipeById(id).setStatus(status);
            }
            break;
        case 0:
            return;
        }

    } while (option != 0);
}

void workWithSearchStationMenu(Data& data) {
    std::vector<Data::ID> found_stations;
    int option = 0;
   
    StationSearch search(data);
    printSearchStation();
    std::cout << "\n>";
    std::cin >> option;
    switch (option) {
    case 1:{
        std::string name;
        input_and_set<std::string>(
            std::cin,
            [&name](std::string value) {name = value; },
            "Enter name: "
        );
        found_stations = search.searchByName(name);
        break;
    }
    case 2:{
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
        break;
    }
    case 3: {
        InputSequence<Data::ID> ids("e");
        std::cout << "Enter ids (ending with 'e' with space): ";
        std::cin >> ids;
        std::unordered_set<Data::ID> ids_set(ids.getElements().begin(), ids.getElements().end());
        found_stations = search.searchByID(ids_set);
        break;
    }
    case 0:
        return;
    }

    std::cout << "Found: " << found_stations.size() << " stations." << std::endl;

    do {
        printSearchStationsMenu();
        std::cout << "\n>";
        std::cin >> option;
        switch (option) {
        case 1:
            for (Data::ID id : found_stations) {
                const CompressorStation& station = data.getStationById(id);
                print_value(std::cout, id, "ID: ", true);
                print(station, std::cout, true);
                std::cout << std::endl;
            }
            break;
        case 2:
            for (Data::ID id : found_stations) {
                data.delete_station(id);
            }
            return;
        case 3:{
            float percent;
            input_and_set<float>(
                std::cin,
                [&percent](float value) {validate_by_range(value, 0.0f, 100.f); percent = value; },
                "Enter percent of use workshops: "
            );
            for (Data::ID id : found_stations) {
                CompressorStation& station =  data.getStationById(id);
                int workshops_in_use = static_cast<int>(station.getWorkshops() * percent / 100);
                station.setWorkshopsInUse(workshops_in_use);
            }
            break;
        }
        case 0:
            return;
        }

    } while (option != 0);
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
    std::ofstream file(enter_filename());
    if (!file) {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }
    
    print(data, file,false);
}

void load_from_file(Data& data) {
    std::ifstream file(enter_filename());
    if (!file) {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }
    data = input_data(file);
}

void add_pipe(Data& data) {
    Pipe pipe = input_pipe(std::cin);
    int id = data.add_pipe(pipe);
    std::cout << "Add pipe with ID = " << id << std::endl;
}

void add_station(Data& data) {
    CompressorStation station = input_station(std::cin);
    int id = data.add_station(station);
    std::cout << "Add station with ID = " << id << std::endl;
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
                print(data, std::cout, true);
            }
            break;
        case 4:
            WRAP_FOR_LOGGING("searchPipe", log) {
                workWithSearchPipeMenu(data);
            }
            break;
        case 5:      
            WRAP_FOR_LOGGING("searchStation", log) {
                workWithSearchStationMenu(data);
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


