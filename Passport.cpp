# include "Passport.h"

using std::string, std::vector;

Passport::Passport(std::string camperName, bool isJuniorPassport): camperName(camperName), isJuniorPassport(isJuniorPassport), parksVisited() {}

string Passport::getCamperName() {
	return this->camperName;
}

bool Passport::checkJuniorPassport() {
	return this->isJuniorPassport;
}

void Passport::addParkVisited(StatePark* park) {
	INFO(park)
	parksVisited.push_back(park);
	park->addCamper(this);
}

double Passport::getMilesHiked() {
	// TODO: (optional) implement function

	return 0.0;
}

int Passport::getHikerLevel() {
	// TODO: (optional) implement function

	return 0;
}
