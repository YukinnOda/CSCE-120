#include <iostream>
#include <sstream>
#include <fstream>
using std::cin, std::cout, std::endl, std::string, std::getline,
      std::ifstream, std::istringstream;

int main() {
  string filename;
  cout << "Enter donation filename: ";
  cin >> filename;
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Failed to open file " << filename << "." << endl;
    return 1;
  }
  
  double maxTotalDonation = 0;
  int maxTotalCollector = 0;
  
  string donationline;
  int donator = 0;
  double donationval = 0;
  double donTotalHold = 0;

  while(!ifs.eof()) {
    getline(ifs, donationline);
    int count = 0;
    donTotalHold = 0;
    istringstream donation(donationline);
    donation >> donator;
    while(donation >> donationval) {
      donTotalHold += donationval;
      count++;
    }

    if(donTotalHold > maxTotalDonation && count > 1) {
      maxTotalDonation = donTotalHold;
      maxTotalCollector = donator;
    }

  }
  
  if(maxTotalDonation == 0) {
    cout << "Highest donation total: No donations";
  }
  else {
    cout << "Highest donation total: " << maxTotalDonation << endl;
    cout << "-- collected by id: " << maxTotalCollector << endl;
  }
}
