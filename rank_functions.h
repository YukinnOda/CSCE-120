#ifndef RANKFUNCTIONS_H
#define RANKFUNCTIONS_H

#include <vector>

const unsigned int SIZE = 9;

struct driver {
	std::string lastname = "";
	std::string country = "";
	unsigned int number = 0;
	double time = 0;
	unsigned int rank = 1;
};


std::vector<driver> load_driver_data();

std::string trim(std::string);

std::vector<driver> set_rankings(std::vector<driver>);


void print_results(std::vector<driver>);

#endif