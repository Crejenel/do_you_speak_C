#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdbool.h>
#include "user_interface.h"
#include "tests.h"

int main() {
	
	//get started
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//user_interface(); 
	run_all_tests();
	return 0;
	
}
