#include "Menu.h"
#include "Data.h"

#include <sstream>

int main()
{
	try {
		work_with_main_menu();
	}
	catch (std::exception ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
	
	return 0;
}