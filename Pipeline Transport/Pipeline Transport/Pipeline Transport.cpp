#include <fstream>
#include <chrono>

#include "Menu.h"
#include "Log.h"



int main()
{
	try {
		std::chrono::zoned_time now{ std::chrono::current_zone(), std::chrono::system_clock::now() };
		std::string time = std::format("{:%d_%m_%Y %H_%M_%OS}", now);
		std::ofstream logfile("log_" + time + ".txt");
		if (!logfile) {
			std::cout << "Error, can't open log file." << std::endl;
			return 0;
		}
		Teebuf redirect_cin{ std::cin, logfile };
		work_with_main_menu();
	}
	catch (std::exception ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
	
	return 0;
}

