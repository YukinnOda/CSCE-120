#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector;

Game::Game(): players({}), suits({}), ranks({}), 
    deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename){
    std::ifstream ifs(filename);
    if(!ifs.good()) {
        throw std::runtime_error("bad read");
    }
    string line;
    std::getline(ifs, line);
    std::stringstream ss(line);
    string suit;
    while(ss >> suit) {
        suits.push_back(suit);
    }
    std::getline(ifs, line);
    std::stringstream iss(line);
    string rank;
    while(iss >> rank) {
        ranks.push_back(rank);
    }
    string tempRank;
    string tempSuit;
    string hold;
    while(std::getline(ifs, line)) {
        std::stringstream css(line);
        css >> tempRank >> tempSuit;
        if(css.bad() || css.fail() || css >> hold) {
            throw std::runtime_error("Something missing pookie");
        }
        css.clear();
        css.str("");
        Card *tempCard;
        bool isinRanks, isinSuits = false;
        try {
            tempCard = new Card(tempRank, tempSuit);
            for(int i = 0; i < ranks.size(); i++) {
                if(tempRank == ranks.at(i)) {
                    isinRanks = true;
                }
            }
            for(int i = 0; i < suits.size(); i++) {
                if(tempSuit == suits.at(i)) {
                    isinSuits = true;
                }
            }

            if(!(isinRanks && isinSuits)) {
                throw std::runtime_error("Bad Card");
            }
            else {
                isinRanks = false;
                isinSuits = false;
            }
        }
        catch(...) {
            throw std::runtime_error("Card thrown error");
        }
        deck.push_back(tempCard);
        drawPile.insert(drawPile.begin(), tempCard);
    }
}

void Game::addPlayer(bool isAI){
    Player *player = new Player(isAI);
    players.push_back(player);
}

void Game::drawCard(Player* p){
    if(drawPile.empty()) {
        if(discardPile.size() <= 1) {
            throw std::runtime_error("Too few values in discard pile to replenish draw!");
        }
        else {
            std::cout << "Draw pile, empty, flipping the discard pile.";
            for(int i = 0; i < discardPile.size() - 1; i++) {
                drawPile.insert(drawPile.begin(), discardPile.at(i));
            }
        }
    }
    discardPile.erase(discardPile.begin(), discardPile.begin() + discardPile.size() - 1);
    p->addToHand(drawPile.at(drawPile.size() - 1));
    drawPile.pop_back();
}

Card* Game::deal(int numCards){
    discardPile.push_back(drawPile.at(drawPile.size() - 1));
    drawPile.pop_back();
    for(int i = 0; i < numCards; i++) {
        for(int p = 0; p < players.size(); p++) {
            drawCard(players.at(p));
        }
    }
    return discardPile.at(0);
}

string Game::mostPlayedSuit(){
    int greatestPlayed = 0;
    int playedHold = 0;
    string suit;
    vector<int> suitsPlayed(suits.size(), 0);
    for(int i = 0; i < deck.size(); i++) {
        playedHold = deck.at(i)->getTimesPlayed();
        for(int s = 0; s < suits.size(); s++) {
            if(deck.at(i)->getSuit() == suits.at(s)) {
                suitsPlayed.at(s) += playedHold;
                if(greatestPlayed <= suitsPlayed.at(s)) {
                    greatestPlayed = suitsPlayed.at(s);
                    suit = suits.at(s);
                }
            }
        }
    }
    return suit;
}

int Game::runGame(){
    bool gameFin = false;
    int winnerIndex;
    while(!gameFin) {
        string topRank = discardPile.at(0)->getRank();
        string topSuit = discardPile.at(0)->getSuit();
        for(int i = 0; i < players.size(); i++) {
            std::cout << "Player " << i << "'s turn!" << std::endl;
            string hand = players.at(i)->getHandString();
            Card *tempCard = players.at(i)->playCard(suits, topRank, topSuit);
            if(tempCard == nullptr) {
                std::cout << "Player " << i << " draws a card." << std::endl;
                drawCard(players.at(i));
            }
            else {
                string changedSuit = topSuit;
                topSuit = tempCard->getSuit();
                if(topRank == "8") {
                    std::cout << "Player " << i << " plays " << topRank << " " << topSuit << " and changes the suit to " << changedSuit << "." << std::endl;
                }
                else {
                    std::cout << "Player " << i << " plays " << topRank << " " << topSuit << "." << std::endl;
                }
                discardPile.push_back(tempCard);
            }

            if(players.at(i)->getHandSize() == 0) {
                winnerIndex = i;
                gameFin = true;
                break;
            }
        }
    }
    return winnerIndex;
}

//Destructor--Deallocates all the dynamic memory we allocated
//You shouldn't touch this
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}