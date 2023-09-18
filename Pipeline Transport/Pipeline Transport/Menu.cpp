#include <iostream>
#include "Pattern.h"
#include "Pipe.h"
#include "CompressorStation.h"
#include <vector>

void printMainMenu() {
    std::cout << "1. Add Pipe" << std::endl;
    std::cout << "2. Add CS" << std::endl;
    std::cout << "3. View all objects" << std::endl;
    std::cout << "4. Edit the pipe" << std::endl;
    std::cout << "5. Edit the CS" << std::endl;
    std::cout << "6. Save" << std::endl;
    std::cout << "7. Load" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << ">";
}

void printSaveMenu() {
    std::cout << "1. Save Pipes" << std::endl;
    std::cout << "2. Save Compressor Stations" << std::endl;
    std::cout << "3. Save All" << std::endl;
    std::cout << "0. Cancel" << std::endl;
    std::cout << "\n>";
}

void work_With_SaveMenu(std::vector <Pipe>& pipes) {
    int option = 0;

    do {
        system("cls");
        printSaveMenu();
        option = validity_enter(0, 3);

        switch (option)
        {
        case 1:
            push_pipe_in_file(pipes);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
    } while (option != 0);
}


void work_With_MainMenu() {
    std::vector <Pipe> pipes;
    std::vector <CompressorStation> stations;
    int option = 0;

    do {
        system("cls");

        printMainMenu();

        option = validity_enter(0, 7);

        switch (option)
        {
        case 1:
            pipes.push_back(add_Pipe());
            break;
        case 2:
            stations.push_back(add_CompressorStation());
            break;
        case 3:
            view_all_pipes(pipes);
            view_all_stations(stations);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            work_With_SaveMenu(pipes);
            break;
        case 7:
            break;
       
        default:
            break;
        }
        if (option != 0) {
            system("pause");
        }
        
    } while (option != 0);

}