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
    
    print(data, file,false);
}

void load_from_file(Data& data) {
    std::ifstream file("result.txt");
    if (!file) {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }
    data = input_data(file);
}

Pipe add_pipe() {
    return input_pipe(std::cin);
}

CompressorStation add_station() {
    return input_station(std::cin);
}

void work_with_main_menu() {
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
            data.getPipes().insert({ id++,add_pipe() });
            break;
        case 2:                                 
            data.getStations().insert({id++,add_station() });
            break;
        case 3:                                 
            print(data, std::cout, true);
            break;
        case 4:
            /*if (!check_pipe) {
                edit_pipe(data.pipe.value());
            }
            else {
                std::cout << "There is no pipe." << std::endl;
            }*/
            break;
        case 5:                                 
            /*if (!check_station) {
                edit_station(data.station.value());
            }
            else {
                std::cout << "There is no station." << std::endl;
            }*/
            break;
        case 6:                                 
            save_to_file(data);
            break;
        case 7:                                 
            load_from_file(data);
            break;
        default:
            std::cout << "Error, option number should be from 1 to 7" << std::endl;
            break;
        }
    } while (option != 0);
}


