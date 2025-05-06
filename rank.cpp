#include <iostream>
#include <vector>
#include "rank_functions.h"

using std::cin; using std::cout; using std::endl;

int main()
{

	std::vector<driver> Racer;

    Racer = load_driver_data();

    Racer = set_rankings(Racer);

    print_results(Racer);

    return 0; 
}

