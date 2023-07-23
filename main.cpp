//#ifndef MAIN_H // Replace PIECE_H with a unique identifier for each header file
//#define MAIN_H

#include "mainloop.h"
#include <iostream>
int main(int argc, char* args[])
{
	std::cout << "Launching the Chess Application! best of luck"<<std::endl;
	mainloop::run();
	return 0;
}
//#endif