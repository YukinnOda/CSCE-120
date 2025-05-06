#include <iostream>
#include "functions.h"
using namespace std;

void function_one(int i, int& j) {
	// TODO: implement function_one so that it takes two integer arguments i and j, adds 2 to i,
    // adds 1 to j, (after execution of the function, only j is changed)
    i += 2;
    j += 1;
}

void function_two(example& x) {
    // TODO: implement function_two so that it takes an argument of type example, and increments
    // its integer by 1 (should persist after the function)
    x.value++;
}

void function_three(int* k, int& l) {
    // TODO: implement function_three so that it increments both variables by one (both changes must
    // persist after the function call)
    *k += 1;
    l += 1;
}

void function_four(int arr[], int size, int& lowest, int& highest) {
    lowest = arr[0] + 2;
    highest = arr[0] + 2;
    for(int i = 0; i < size; i++) {
        arr[i] += 2;
        if(arr[i] < lowest) {
            lowest = arr[i];
        }
        if(arr[i] > highest) {
            highest = arr[i];
        }
    }
}