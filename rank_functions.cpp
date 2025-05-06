#include <iostream>
#include <iomanip>
#include <vector>
#include "rank_functions.h"

using std::cin, std::cout, std::vector, std::endl;


vector<driver> load_driver_data() {
	int lanes = 9;
	vector<driver> Racer;
	for(int i = 0; i < lanes; i++) {
		driver d;
		cin >> d.time;
		if(d.time <= 0.0) {
			Racer.clear();
			return Racer;
		}
		cin >> d.country;
		int c_length = d.country.size();
		if(c_length != 3) {
			Racer.clear();
			return Racer;
		}
		for(int i = 0; i < c_length; i++) {
			int chara = d.country[i];
    		if(isalpha(chara) == false || isupper(chara) == false) {
				Racer.clear();
				return Racer;
			}
		}	
		cin >> d.number;
		if(d.number >= 100.0 || d.number <= 0.0) {
			Racer.clear();
			return Racer;
		}
		cin >> d.lastname;
		int n_length = d.lastname.size();
		if(n_length <= 1) {
			Racer.clear();
			return Racer;
		}
		for(int i = 0; i < n_length; i++) {
			int chara = d.lastname[i];
    		if(isalpha(chara) == false) {
				Racer.clear();
				return Racer;
			}
		}	
		d.rank = 0;
		Racer.push_back(d);
	}
	return Racer;
}


vector<driver> set_rankings(vector<driver> v) {
	double fastest = v.at(0).time;
	int index = 0;
	double limit_fast = 0;
	double curr_time = fastest;
	for(int i = 0; i < 9; i++) {
		for(int r = 0; r < 9; r++) {
			curr_time = v.at(r).time;
			if(curr_time < fastest && curr_time > limit_fast){
				index = r;
				fastest = curr_time;
			}
		}
		limit_fast = v.at(index).time;
		v.at(index).rank = i + 1;
		fastest = 100;
	}
	return v;
}

std::string trim(std::string s) {
	while(s.size() > 0 && isspace(s.at(0))){
		s.erase(0, 1);
	}
	while(s.size() > 0 && isspace(s.at(s.size()-1))){
		s.erase(s.size()-1,s.size());
	}
	return s;
}


void print_results(std::vector<driver> v)
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	for(unsigned int j = 1; j <= v.size(); j++)
	{
		
		for(unsigned int i = 0; i < v.size(); i++)
		{
			if(v.at(i).rank == 1) //
			{
				best_time = v.at(i).time;
			}
			
			
			if(v.at(i).rank == j) 
			{

				std::cout << "[" << j << "]  " << v.at(i).time << " " << std::setw(15) << std::left << v.at(i).lastname << "\t" << "(" << v.at(i).country << ")  +" << (v.at(i).time - best_time) << std::endl; 
			}
			
		}
	}	
}