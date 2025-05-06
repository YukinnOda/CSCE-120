#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t;

Player::Player(bool isAI): isAI(isAI) {
}

void Player::addToHand(Card* c){
    hand.push_back(c);
}

size_t Player::getHandSize(){
    return this->hand.size();
}

std::string Player::getHandString(){
    std::stringstream ss("");
    string handString;
    if(!hand.empty()) {
        for(int i = 0; i < hand.size() - 1; i++) {
            if(i == hand.size() - 1) {
                ss << hand.at(i)->getRank() << " " << hand.at(i)->getSuit();
            
            }
            else {
                ss << hand.at(i)->getRank() << " " << hand.at(i)->getSuit() << ", ";
            }
        }
        ss << hand.at(hand.size() - 1)->getRank() << " " << hand.at(hand.size() - 1)->getSuit();
    }
    return ss.str();
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit){
    std::vector<Card*> storage;
    if(isAI) {
        for(int i = 0; i < this->getHandSize(); i++) {
            if(hand.at(i)->canBePlayed(currentRank, currentSuit)) {
                hand.at(i)->play();
                currentRank = hand.at(i)->getRank();
                currentSuit = hand.at(i)->getSuit();
                storage.push_back(hand.at(i));
                hand.erase(hand.begin() + i);
                return storage.at(0);
            } 
        }
        return nullptr;
    }
    else {
        std::cout << "Your hand contains: " << this->getHandString() << std::endl;
        std::cout << "The next card played must be a " << currentRank << " or " << currentSuit << std::endl;
        std::cout << "What would you like to play? (enter \"draw card\" to draw a card)" << std::endl;
        string input;
        std::cin.ignore(1000, '\n');
        std::getline(std::cin, input);
        std::stringstream ss(input);
        std::string tempRank, tempSuit;
        ss >> tempRank >> tempSuit;
        if(tempRank == "draw" && tempSuit == "card") {
            return nullptr;
        }
        bool cardInHand = false;
        bool suitInDeck = false;
        Card tempCard(tempRank, tempSuit);
        int cardIndex;
        bool canBePlayed = tempCard.canBePlayed(currentRank, currentSuit);
        for(int c = 0; c < hand.size(); c++) {
            if(hand.at(c)->getRank() == tempRank && hand.at(c)->getSuit() == tempSuit) {
                cardInHand = true;
                cardIndex = c;
            }
        }
        
        if(!cardInHand) {
            std::cout << "That's not a card you have. Try again." << std::endl;
        }
        else if(!canBePlayed) {
            std::cout << "You can't play that card. Try again." << std::endl;
        }

        bool goodCard = (canBePlayed && cardInHand);
        if(goodCard) {
            currentRank = tempCard.getRank();
            currentSuit = tempCard.getSuit();
        }
        else {
            while(!goodCard) {
                std::getline(std::cin, input);
                std::stringstream ss(input);
                std::string tempRank, tempSuit;
                ss >> tempRank >> tempSuit;
                if(tempRank == "draw" && tempSuit == "card") {
                    return nullptr;
                }
                else {
                    cardInHand = false;
                    Card tempCard(tempRank, tempSuit);
                    canBePlayed = tempCard.canBePlayed(currentRank, currentSuit);
                    for(int c = 0; c < hand.size(); c++) {
                        if(hand.at(c)->getRank() == tempRank && hand.at(c)->getSuit() == tempSuit) {
                            cardInHand = true;
                            cardIndex = c;
                        }
                    }
                    if(!cardInHand) {
                        std::cout << "That's not a card you have. Try again." << std::endl;
                    }
                    else if(!canBePlayed) {
                        std::cout << "You can't play that card. Try again." << std::endl;
                    }
                    else {
                        goodCard = (canBePlayed && cardInHand);
                        currentRank = tempRank;
                        currentSuit = tempSuit;
                    }
                }
            }
        }

        if(tempRank == "8") {
            std::cout << "What suit would you like to declare?" << std::endl;
            std::getline(std::cin, input);
            std::stringstream ss(input);
            std::string DeclareSuit;
            ss >> DeclareSuit;
            for(int s = 0; s < suits.size(); s++) {
                if(DeclareSuit == suits.at(s)) {
                    suitInDeck = true;
                    tempSuit = DeclareSuit;
                    currentRank = tempRank;
                    currentSuit = tempSuit;
                    break;
                }
            }
            while(!suitInDeck) {
                std::cout << "That's not a suit in this deck. Try again." << std::endl;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                std::string DeclareSuit;
                ss >> DeclareSuit;
                for(int s = 0; s < suits.size(); s++) {
                    if(DeclareSuit == suits.at(s)) {
                        suitInDeck = true;
                        tempSuit = DeclareSuit;
                        currentRank = tempRank;
                        currentSuit = tempSuit;
                    }
                }
            }
        }
        Card *returnCard = hand.at(cardIndex);
        returnCard->play();
        hand.erase(hand.begin() + cardIndex);
        return returnCard;
    }
}