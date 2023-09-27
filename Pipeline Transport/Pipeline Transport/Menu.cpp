#include <iostream>
#include <vector>

#include "Pattern.h"
#include "Pipe.h"
#include "CompressorStation.h"

// функция вывода главного меню на консоль
void printMainMenu() {
    std::cout << "1. Add Pipe" << std::endl;
    std::cout << "2. Add CS" << std::endl;
    std::cout << "3. View all objects" << std::endl;
    std::cout << "4. Edit the pipe" << std::endl;
    std::cout << "5. Edit the CS" << std::endl;
    std::cout << "6. Save" << std::endl;
    std::cout << "7. Load" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "\n> ";
}

// функция вывода меню сохранения на консоль
void printSaveMenu() {
    std::cout << "1. Save Pipes" << std::endl;
    std::cout << "2. Save Compressor Stations" << std::endl;
    std::cout << "3. Save All" << std::endl;
    std::cout << "0. Cancel" << std::endl;
    std::cout << "\n>";
}

// функция вывода меню загрузки на консоль
void printLoadMenu() {
    std::cout << "1. Load Pipes" << std::endl;
    std::cout << "2. Load Compressor Stations" << std::endl;
    std::cout << "3. Load All" << std::endl;
    std::cout << "0. Cancel" << std::endl;
    std::cout << "\n> ";
}

// работа с меню загрузки
void work_With_LoadMenu(Pipe& pipe,CompressorStation& station) {
    int option = 0;

    do {
        system("cls");
        printLoadMenu();
        option = validity_enter(0, 3);

        switch (option)
        {
        case 1:                     //Load Pipes
            system("cls");
            load_all_pipes(pipe);
            system("pause");
            break;
        case 2:                     //Load Compressor Stations
            system("cls");
            load_all_stations(station);
            system("pause");
            break;
        case 3:                     //Load All
            system("cls");
            load_all_pipes(pipe);
            load_all_stations(station);
            system("pause");
            break;
        default:
            break;
        }
    } while (option != 0);
}

// работа с меню сохранения
void work_With_SaveMenu(Pipe pipe, CompressorStation station) {
    int option = 0;

    do {
        system("cls");
        printSaveMenu();
        option = validity_enter(0, 3);

        switch (option)
        {
        case 1:                         //Save Pipes
            system("cls");
            push_pipe_in_file(pipe);
            system("pause");
            break;
        case 2:                         //Save Compressor Stations
            system("cls");
            push_CS_in_file(station);
            system("pause");
            break;
        case 3:                         //Save All
            system("cls");
            push_pipe_in_file(pipe);
            push_CS_in_file(station);
            system("pause");
            break;
        default:
            break;
        }
    } while (option != 0);
}

// работа с главным меню
void work_With_MainMenu() {
    Pipe pipe;
    CompressorStation station;
    int option = 0;

    do {
        system("cls");

        printMainMenu();

        option = validity_enter(0, 7);

        switch (option)
        {
        case 1:                                 //Add Pipe
            system("cls");
            pipe = add_Pipe();
            system("pause");
            break;
        case 2:                                 //Add CS
            system("cls");
            station = add_CompressorStation();
            system("pause");
            break;
        case 3:                                 //View all objects
            system("cls");
            view_all_pipes(pipe);
            view_all_stations(station);
            system("pause");
            break;
        case 4:                                 //Edit the pipe
            system("cls");
            edit_pipe(pipe);
            system("pause");
            break;
        case 5:                                 //Edit the CS
            system("cls");
            edit_station(station);
            system("pause");
            break;
        case 6:                                 //Save
            work_With_SaveMenu(pipe,station);
            break;
        case 7:                                 //Load
            work_With_LoadMenu(pipe, station);
            break;
       
        default:
            break;
        }
        
    } while (option != 0);

}