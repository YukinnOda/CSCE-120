# include "Database.h"

using std::string, std::vector;

Database::Database(): stateParkList(), camperList() {}

Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)

	StatePark *newPark = new StatePark(parkName, entranceFee, trailMiles);
	stateParkList.push_back(newPark);
}

void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)

	Passport *newPass = new Passport(camperName, isJuniorPassport);
	camperList.push_back(newPass);
}

void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)

	bool ParkExists = false;
	bool CamperExists = false;
	int parkIndex;
	int camperIndex;
	int stateParkSize = stateParkList.size();
	int camperListSize = camperList.size();
	for(int p = 0; p < stateParkSize; p++) {
		if(parkName == stateParkList.at(p)->getParkName()) {
			ParkExists = true;
			parkIndex = p;
		}
	}
	for(int c = 0; c < camperListSize; c++) { 
		if(camperName == camperList.at(c)->getCamperName()) {
			CamperExists = true;
			camperIndex = c;
		}
	}
	if(CamperExists && ParkExists) {
		camperList.at(camperIndex)->addParkVisited(stateParkList.at(parkIndex));
	}
}

vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)

	// TODO: (optional) implement function
	
	return {};
}

vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)

	// TODO: (optional) implement function

	return {};
}
