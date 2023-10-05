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

void edit_pipe(Data& data) {
    if (!data.pipe.has_value()) {
        std::cout << "Error, there is no pipe"<<std::endl;
        return;
    }
    Pipe& pipe = data.pipe.value();
    std::cout << "Do you want to change the pipe status? (1 - yes, 0 - no)" << std::endl;
    if (validity_enter_interactive(0, 1) == 1) {
        pipe.in_repair = !pipe.in_repair;
    }
}

void edit_station(Data& data) {
    if (!data.station.has_value()) {
        std::cout << "Error, there is no station" << std::endl;
        return;
    }
    CompressorStation& station = data.station.value();
    std::cout << "How many workshops do you want to run? ";
    station.number_of_use_workshop = validity_enter_interactive(0, station.number_of_workshop);
}

void work_with_main_menu(Data& data) {
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
            edit_pipe(data);
            break;
        case 5:                                 
            edit_station(data);
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


