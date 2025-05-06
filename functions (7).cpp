#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>
#include "functions.h"

using std::cout, std::cin, std::endl, std::exception, std::invalid_argument; 
using std::getline, std::string;

int mapping (string loc) {
            int num = 0;
            if (loc == "Boston") num = 1;
            else if (loc == "Hartford") num = 2;
            else if (loc == "NewYork") num = 3;
            else if (loc == "Philadelphia") num = 4;
            else if (loc == "Baltimore") num = 5;
            else if (loc == "WashingtonDC") num = 6;
            else if (loc == "Pittsburgh") num = 7;
            else if (loc == "Cleveland") num = 8;
            else if (loc == "Detroit") num = 9;
            else if (loc == "Chicago") num = 10;
            else if (loc == "Indianapolis") num = 11;
            else if (loc == "Nashville") num = 12;
            else if (loc == "Atlanta") num = 13;
            else if (loc == "Houston") num = 14;
            else if (loc == "Austin") num = 15;
            else if (loc == "Dallas") num = 16;
            else if (loc == "Denver") num = 17;
            else if (loc == "Albuquerque") num = 18;
            else if (loc == "Phoenix") num = 19;
            else if (loc == "Sacramento") num = 20;
            else {
                try { throw invalid_argument("Undefined location"); } 
                catch (std::invalid_argument const& e) { cout << e.what() << endl; } 
            }
            return num;
}

string rev_mapping (int num) {
            string loc;
            switch (num)
            {
            case 1: { loc = "Boston"; break; }
            case 2: { loc = "Hartford"; break; }
            case 3: { loc = "NewYork"; break; }
            case 4: { loc = "Philadelphia"; break; } 
            case 5: { loc = "Baltimore"; break; }
            case 6: { loc = "WashingtonDC"; break; }
            case 7: { loc = "Pittsburgh"; break; }
            case 8: { loc = "Cleveland"; break ; }
            case 9: { loc = "Detroit"; break; }
            case 10: { loc = "Chicago"; break; }
            case 11: { loc = "Indianapolis"; break; }
            case 12: { loc = "Nashville"; break; }
            case 13: { loc = "Atlanta"; break; }
            case 14: { loc = "Houston"; break; }
            case 15: { loc = "Austin"; break; }
            case 16: { loc = "Dallas"; break; }
            case 17: { loc = "Denver"; break; }
            case 18: { loc = "Albuquerque"; break; }
            case 19: { loc = "Phoenix"; break; }
            case 20: { loc = "Sacramento"; break; }
            default: { loc = "undefined"; break;}
            }            
            if (loc == "undefined") {
                try { throw invalid_argument("Undefined location"); } 
                catch (std::invalid_argument const& e) { cout << e.what() << endl; } 
            }
            return loc;
}

void get_op(const string& line, string* operation) {
    std::istringstream sin(line);
    sin >> *operation;
    if (sin.fail()) {
        sin.clear();
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        *operation = "ignore";
    }
}

void get_loc(const string& line, string* location) {
    std::istringstream sin(line);
    sin >> *location;
    if (sin.fail()) {
        sin.clear();
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void print_inst_1() {
    cout << "*** enter operation: push <location> | insert <location> | delete <location> | pop | clear | print | locations | quit" << endl;
    cout << "*** enter location from above list on next line" << endl;
    cout << "*** enter an empty line to end input" << endl;
    cout << "***" << endl;
    cout << "*** WARNING: push operation pushes location in push order without any location ordering" << endl;
    cout << "***" << endl;
}

void print_inst_2() {
    cout << "*** Locations: Boston | Hartford | NewYork | Philadelphia | Baltimore | WashingtonDC | Pittsburgh | Cleveland | Detroit | Chicago | " << endl;
    cout << "*** Indianapolis | Nashville | Atlanta | Houston | Dallas | Austin | Denver | Albuquerque | Phoenix | Sacramento" << endl;
    cout << "*** .... you can repeat this list anytime at prompt by typing locations ...." << endl;
    cout << "***" << endl;   
}

void print_inst_3() {
    cout << endl;
    cout << "next" << endl;
}

node::node (int arg_val, node *ptr = nullptr) {
            this->value = arg_val;
            this->ptr = ptr;    
}

// getters, gets value, gets ptr
// HOMEWORK
int node::getvalue () {
    return value;
}
node *node::getptr () {
    return ptr;
}

// setter
// HOMEWORK
void node::setptr (node *ptr) {
    this->ptr = ptr;
}
void node::setvalue (int value) {
    this->value = value;
}

//LinkedList constructor
LinkedList::LinkedList () : headptr(nullptr) {
            this->headptr = nullptr;
}

//LinkedList destructor
// HOMEWORK
LinkedList::~LinkedList () {
    node* current = headptr;
    while(current != nullptr) {
        node* next = current->getptr();
        delete current;
        current = next;
    }
    headptr = nullptr;
}

//LinkedList copy constructor
// HOMEWORK
LinkedList::LinkedList (const LinkedList& object) : headptr(nullptr){
    if(object.headptr != nullptr) {
        node* current = object.headptr;
        while(current != nullptr) {
            node* temp = new node(current->getvalue(), current->getptr());
            temp = temp;
            current = current->getptr();
        }
    }
}

// Copy assignment constructor
// HOMEWORK
LinkedList& LinkedList::operator=(const LinkedList &object) {
    node* current = object.headptr;
    while(current != nullptr) {
        node* temp = new node(current->getvalue(), current->getptr());
        temp = temp;
        current = current->getptr();
    }
    return *this;
}

// push a node
// HOMEWORK
void LinkedList::push (int value) {
    node* temp = new node(value, headptr);
    headptr = temp;
}

// pop a node
// HOMEWORK
int LinkedList::pop () {
    if(headptr == nullptr) {
        cout << "Cannot remove elements from empty link list" << endl;
        return 0;
    }
    node* temp = headptr;
    int value_to_remove = headptr->getvalue();
    headptr = headptr->getptr();
    delete temp;

    return value_to_remove;
}

// helper function: print linked list
void LinkedList::printLinkedList () {
    node *curNode = headptr;
    int i=0;
    int reference;
        while (curNode != nullptr) {
            reference = curNode->getvalue();
            cout << rev_mapping(reference) << " -> ";
            curNode = curNode->getptr();
            // this piece of code prevents printing of endless nodes if you have an infinite loop
            // you can delete this if so desired, it doesn't affect functionality
            i++;
            if (i>20) {
                    cout << "Warning: broken linked list possible." << endl;    
                    break;
            }
        }
    cout << endl;
}

// Find the node closest to and less than value, i.e. where in the linked list
// should you insert. It approximates the correct driving order for the driver.
// HOMEWORK
int LinkedList::find_closest_less_than(int value) {
    node* current = headptr;
    int storediff = INT32_MIN;
    while(current != nullptr) {
        if(current->getvalue() < value && current->getvalue() > storediff) {
            storediff = current->getvalue();
        }
        current = current->getptr();
    }
    return storediff;
}

// inserts a node in a sepcific location
// HOMEWORK
void LinkedList::insertNode(int value, int reference_value) {
    node* newNode = new node(value);
    node* current = headptr;
    if(reference_value == INT32_MIN) {
        push(value);
        return;
    }
    while(current != nullptr) {
        if(current->getvalue() == reference_value) {
            newNode->setptr(current->getptr());
            current->setptr(newNode);
            return;
        }
        current = current->getptr();
    }
} // end insertNode

// deletes a node in a specific location
// HOMEWORK
void LinkedList::deleteNode(int reference_value) {
    node* current = headptr;
    node* temp =  nullptr;
    bool found = false;
    if(headptr->getvalue() == reference_value) {
        headptr = headptr->getptr();
        delete current;
        return;
    }
    while(current != nullptr && current->getvalue() != reference_value) {
        temp = current;
        current = current->getptr();
        if(current != nullptr) {
            if(current->getvalue() == reference_value) {
                found = true;
            }
        }
    }
    if(!found) {
        cout << "Trying to delete a node that does not exist" << endl;
        return;
    }

    temp->setptr(current->getptr());
    delete current;
} // end deleteNode

// helper function: Is the link list empty?
bool LinkedList::link_list_empty() {
    if (this->headptr == nullptr) {return true;}
        else {return false;}
}

// function for unit test, do not change
int LinkedList::obtain_value_head () {
    node *curNode = headptr;
    return curNode->getvalue();
}

// function for unit test, do not change
int LinkedList::obtain_value_node (int steps) {
    node *curNode = headptr;
    for (int i = 0; i < steps; i++) {
        curNode = curNode->getptr();
    }
    return curNode->getvalue();
}
// end of public methods for LinkedList
