#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit): rank(rank), suit(suit), timesPlayed(0) {
    if(rank.empty() || suit.empty()) {
        throw std::invalid_argument("Rank or Suit are empty!");
    }
    for(int i = 0; i < rank.length(); i++) {
        if(!(std::isalnum(rank[i]))) {
            throw std::invalid_argument("Rank contains invalid characters!");
        }
    }
    for(int i = 0; i < suit.length(); i++) {
        if(!(std::isalnum(suit[i]))) {
            throw std::invalid_argument("Suit contains invalid characters!");
        }
    }
}

string Card::getRank(){
    return rank;
}

string Card::getSuit(){
    return suit;
}

int Card::getTimesPlayed(){
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    if((this->rank == currentRank || this->rank == "8") || (this->suit == currentSuit)) {
        return true;
    }
    return false;
}

//You don't need to modify this
void Card::play(){
    timesPlayed++;
}