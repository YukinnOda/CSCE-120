#include <iostream>
#include "functions.h"

using std::cout, std::endl;

// this function checks if the range is valid
bool is_valid_range(long long a, long long b) {
	long long num1 = 1000;
	long long num2 = 1000000000000;
	// TODO complete the code for this function to ensure that a and b are within valid range
	if((num1 <= a) && (a <= b) && (b < num2)) 
	return true;
	else
	return false;
}

// classify_geo_type operates on a number, slices it and detects if it is plateau, basin or none
// it is called recursively by count_valid_pb_numbers
char classify_geo_type(long long number) {
	int count = 1;
	int numStore = number;
	long long workingnum = number;
	int holdInt = number % 10;
	number = number / 10;
	int nextInt = number % 10;
	char returnchar = 'n';
	char changeVal = ' ';
	int changeUp {0};
	int changeDown {0};
	int changeEq {0};
	if(holdInt < nextInt) {
		changeVal = '<';
		changeUp = count;
	}
	if(holdInt == nextInt) {
		changeVal = '=';
		changeEq = count;
	}
	if(holdInt > nextInt) {
		changeVal = '>';
		changeDown = count;
	}

	// TODO find number of digits
	// Note: It is possible to have a single loop to detect plateau or basin, but it can get complicated
	// It is easier to create code that iterates twice, once to check if it is a plateau, 
	// second time if it is a basin
	// TODO Initialize local variables
	while(number != 0) {
		if(holdInt == nextInt && ((changeVal == '<' || changeVal == '>'))) {
			changeVal = '=';
			count++;
			changeEq = count;
		}
		if(holdInt > nextInt && ((changeVal == '=' || changeVal == '<'))) {
			changeVal = '>';
			count++;
			changeDown = count;
		}
		if(holdInt < nextInt && ((changeVal == '=' || changeVal == '>'))) {
			changeVal = '<';
			count++;
			changeUp = count;
		}
		holdInt = number % 10;
		number = number / 10; 
		nextInt = number % 10;
	}
	if(changeUp == 3 && changeEq == 2 && changeDown == 1)
		returnchar = 'b';
	else if(changeDown == 3 && changeEq == 2 && changeUp == 1)
		returnchar = 'p';
	else
		returnchar = 'n';

	// TODO Use a while loop to number slice and detect a plateau: this is the key loop
	// TODO (Re)Initialize local variables

	// TODO Use a while loop to number slice and detect a basin: if you get the logic for plateau right, 
	// minor tweaks can create the code for basins.

	// return the appropriate char, p for plateau, b for basin, n for neither, e for error
	return returnchar; 
}

void count_valid_pb_numbers(long long a, long long b) {
	long long int distance = b-a;
	int plat_count = 0;
	int bas_count = 0;
	char x;

	for(int i = 0; i < distance; i++) {
		x = classify_geo_type(a + i);
		if(x == 'p')
		plat_count++;
		if(x == 'b')
		bas_count++;
	}

	// TODO for loop to iterate from 0 to distance
	// recursively call classify_geo_type
	// count plateaus and basins based on char returned

	cout << "There are ";
	cout << plat_count;
	cout << " plateaus and ";
	cout << bas_count;
	cout << " basins between ";
	cout << a;
	cout << " and ";
	cout << b;
	cout <<'.' << endl;
}