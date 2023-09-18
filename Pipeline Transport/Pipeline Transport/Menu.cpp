#include <iostream>
#include "Pattern.h"
#include "Pipe.h"
#include "CompressorStation.h"

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


void work_With_MainMenu() {
    int option = 0;

    do {
        system("cls");

        printMainMenu();

        option = validity_enter(0, 7);

        switch (option)
        {
        case 1:
            add_Pipe();
            break;
        case 2:
            add_CompressorStation();
            break;
        case 3:
            view_all_pipes();
            view_all_stations();
            
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 0:
            break;
        default:
            break;
        }
        /*if (option != 0) {
            system("pause");
        }*/
        
    } while (option != 0);

}