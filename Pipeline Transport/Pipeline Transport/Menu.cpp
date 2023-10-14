#include <iostream>
#include <fstream>

#include "Utilities.h"
#include "Data.h"

void printMainMenu() {
    std::cout << "1. Add Pipe" << std::endl;
    std::cout << "2. Add CS" << std::endl;
    std::cout << "3. View all objects" << std::endl;
    std::cout << "4. Edit the pipe" << std::endl;
    std::cout << "5. Edit the CS" << std::endl;
    std::cout << "6. Save" << std::endl;
    std::cout << "7. Load" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void save_to_file(const Data& data) {
    std::ofstream file("result.txt");
    if (!file) {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }
    if (!data.pipe.has_value() && !data.station.has_value()) {
        std::cout << "Error, there are no pipes and stations!" << std::endl;
        return;
    }
    print(data, file);
}

void load_from_file(Data& data) {
    std::ifstream file("result.txt");
    if (!file) {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }
    bool success = input_data(data, file);
    if (!success) {
        std::cout << "Error, can't read file" << std::endl;
    }
}

Pipe add_pipe() {
    return input_pipe_interactive();
}

CompressorStation add_station() {
    return input_station_interactive();
}


bool check_pipe(Data& data) {
    return data.pipe.has_value() ? true : false;
}

bool check_station(Data& data) {
    return data.station.has_value() ? true : false;
}

void edit_pipe(Pipe& pipe) {
    std::cout << "Do you want to change the pipe status? (1 - yes, 0 - no)" << std::endl;
    if (validity_enter_interactive(0, 1) == 1) {
        pipe.in_repair = !pipe.in_repair;
    }
}

void edit_station(CompressorStation& station) {
    std::cout << "How many workshops do you want to run? ";
    station.number_of_use_workshop = validity_enter_interactive(0, station.number_of_workshop);
}

void work_with_main_menu() {
    Data data;
    int option = 0;
    do {
        printMainMenu();
        std::cout << "\n>";
        option = validity_enter_interactive(0, 7);
        switch (option)
        {
        case 1:                                 
            data.pipe = add_pipe();
            break;
        case 2:                                 
            data.station = add_station();
            break;
        case 3:                                 
            pretty_print(data, std::cout);
            break;
        case 4:
            if (!check_pipe) {
                edit_pipe(data.pipe.value());
            }
            else {
                std::cout << "There is no pipe." << std::endl;
            }
            break;
        case 5:                                 
            if (!check_station) {
                edit_station(data.station.value());
            }
            else {
                std::cout << "There is no station." << std::endl;
            }
            break;
        case 6:                                 
            save_to_file(data);
            break;
        case 7:                                 
            load_from_file(data);
            break;
        default:
            break;
        }
    } while (option != 0);
}


