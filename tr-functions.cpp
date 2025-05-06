#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "tr-functions.h"

using std::vector, std::string;
using std::cout, std::cin;

// Part 1 Functions

void getUserInput(std::string& filename, unsigned int& rows, unsigned int& cols) {
    cout << "Enter filename: ";
    string streamin;
    cin >> streamin;
    while(streamin.empty()) {
        cin >> streamin;
    }   
    filename = streamin;

    cout << "Enter number of rows (1 - 4000): ";
    int row;
    cin >> row;
    while(cin.fail() || row > 4000 || row < 1) {
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin >> row;
    }
    rows = row;

    cout << "Enter number of columns (1 - 4000): ";
    int col;
    cin >> col;
    while(cin.fail() || col > 4000 || col < 1) {
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin >> col;
    }
    cols = col;

}

vector<vector<unsigned int>> loadElevations(string filename, unsigned int rows, unsigned int cols) {
    vector<vector<unsigned int>> v;
    vector<unsigned int> c;
    int val;
    std::ifstream ifs(filename);
    int rnum = rows;
    int cnum = cols;
    if(ifs.good()) {
        for(int i = 0; i < rnum; i++) {
            for(int r = 0; r < cnum; r++) {
                ifs >> val;
                if(ifs.good()) {
                    c.push_back(val);
                }
                else if(ifs.eof()) {
                    throw std::runtime_error("loadElevations: Not enough values");
                }
                else {
                    throw std::runtime_error("loadElevations: Invalid elevation value");
                }
            }
            v.push_back(c);
            c.clear();
        }
    }
    else {
        throw std::invalid_argument("loadElevations: Failed to open " + filename);
    }

    if(ifs >> val) {
        throw std::runtime_error("loadElevations: Too many values");
    }
    return v;
}

void findMinMax(const vector<vector<unsigned int>>& elevations, unsigned int& min, unsigned int& max) {
    if(elevations.size() == 0 || elevations.at(0).size() == 0) {
        throw std::invalid_argument("findMinMax: Invalid elevations vector");
    }

    min = elevations.at(0).at(0);
    max = min;
    int esize = elevations.size();
    int ecsize = elevations.at(0).size();

    for(int i = 0; i < esize; i++) {
        if(elevations.at(i).size() == 0) {
            throw std::invalid_argument("findMinMax: Invalid elevations vector");
        }

        for(int r = 0; r < ecsize; r++) {
            if(elevations.at(i).at(r) > max) {
                max = elevations.at(i).at(r);
            }
            if(elevations.at(i).at(r) < min) {
                min = elevations.at(i).at(r);
            }
        }
    }
}

unsigned short scaleValue(unsigned int value, unsigned int min, unsigned int max) {
    if(min >= max) {
        throw std::out_of_range("scaleValue: min must be less than max");
    }
    else if(value > max || value < min) {
        throw std::out_of_range("scaleValue: value must be in the range min <= value <= max");
    }

    double dmin = min;
    double dmax = max;
    double dval = value;
    double pre_round = ((dval - dmin) / (dmax - dmin)) * 255;
    int rounded = pre_round + 0.5;
    return rounded;
}

vector<vector<Pixel>> createImage(const vector<vector<unsigned int>>& elevations) {
    vector<vector<Pixel>> v;
    vector<Pixel> c;
    Pixel tempP;
    unsigned short rgb;
    unsigned int val;
    unsigned int min;
    unsigned int max;
    try {
        findMinMax(elevations, min, max);
    }
    catch(...) {
        throw std::invalid_argument("createImage: Invalid elevations vector"); 
    }

    int esize = elevations.size();
    int ecsize = elevations.at(0).size();
    for(int i = 0; i < ecsize; i++) {
        for(int r = 0; r < esize; r++) {
            if(elevations.size() == 0 || elevations.at(r).size() == 0) { 
                throw std::invalid_argument("createImage: Invalid elevations vector");
            }
            val = elevations.at(r).at(i);
            rgb = scaleValue(val, min, max);
            tempP.b = rgb;
            tempP.g = rgb;
            tempP.r = rgb;
            c.push_back(tempP);
        }
        v.push_back(c);
        c.clear();
    }
    return v;
}

void saveImage(string filename, const vector<vector<Pixel>>& image) {
    std::ofstream ofs(filename + ".ppm");
    if(!ofs.good()) {
        cout << "im at check files!";
        throw std::invalid_argument("saveImage: Failed to open " + filename);
    }
    int isize = image.size();
    int icsize = image.at(0).size();
    ofs << "P3" << std::endl;
    ofs << isize << " " << icsize << std::endl;
    ofs << 255 << std::endl;
    Pixel tempP;
    if(isize == 0 || icsize == 0) { 
        cout << "Im before the for loop!";
        throw std::invalid_argument("saveImage: Invalid image vector");
    }
    for(int i = 0; i < icsize; i++) {
        for(int r = 0; r < isize; r++) {
            if(image.at(r).size() == 0) { 
                cout << "Im inside the for loop!";
                throw std::invalid_argument("saveImage: Invalid image vector");
            }
            tempP = image.at(r).at(i);
            ofs << tempP.r << " " << tempP.g << " " << tempP.b << " ";
        }
        ofs << std::endl;
    }
}

// uncomment the following for part 2

// void processRoutes(vector<vector<Pixel>>& image, const vector<unsigned int>& elevations, Pixel colorAll, Pixel colorMin) {

// }

// int colorRoute(vector<vector<Pixel>>& image, const vector<unsigned int>& elevations, Pixel color, int startRow) {
//     return 0;
// }

