// TODO: Implement this source file
#include "MyString.h"
#include <iostream>

//Default Constructor
MyString::MyString(): c(new char[1]()), len(0), cap(1) {}

//Copy Constructor
MyString::MyString(const MyString& str): c(new char[str.cap]()), len(str.len), cap(str.cap) {
    for(int i = 0; i < str.len; i++) {
        c[i] = str.c[i];
    }
}

//From c-string constructor
MyString::MyString(const char* s): c(new char[1]()), len(0), cap(1) { 
    int i = 0;
    while(s[i] != '\0') {
        c[i] = s[i];
        len++;
        if(cap == len) {
            resize(cap);
        }
        i++;
    }
}

//Destructor
MyString::~MyString() {
    if(c != nullptr) {
        delete[] c;
        c = nullptr;
    }
    len = 0;
    cap = 1;
}

//Resize Function
void MyString::resize(size_t s) {
    char* temp = new char[s * 2]();
    for(int i = 0; i < s; i++) {
        temp[i] = c[i];
    }
    delete[] c;
    c = temp;
    cap = s * 2;
}

//Capacity Function
int MyString::capacity() {
    return cap;
}

//Size Function
size_t MyString::size() const noexcept {
    return len;
}

//Length Function
size_t MyString::length() {
    return len;
}

//Data Function
const char* MyString::data() {
    return c;
}

//Empty Function
bool MyString::empty() {
    if(len == 0) {
        return true;
    }
    else {
        return false;
    }
}

//Front Function
const char& MyString::front() const{
    return c[0];
}

//At Function
const char& MyString::at(size_t s) const {
    if(s >= len) {
        throw std::out_of_range("Out of Bounds");
    }
    return c[s];
}

//Clear Function
void MyString::clear() {
    if(c != nullptr) {
        delete[] c;
        c = new char[1]();
    }
    len = 0;
    cap = 1;
}

//Copy assignment operator
MyString& MyString::operator= (const MyString& str) {
    if(this == &str) {
        return *this;
    }
    clear();
    int i = 0;
    while(str.c[i] != '\0') {
        c[i] = str.c[i];
        len++;
        if(cap == len) {
            resize(cap);
        }
        i++;
    }
    return *this;
}

//Override += operator
MyString& MyString::operator+= (const MyString& str) {
    char* temp = new char[len + str.len + 1]();
    for(int i = 0; i < len; i++) {
        temp[i] = c[i];
    }
    for(int i = 0; i < str.len; i++) {
        temp[len + i] = str.c[i];
    }
    delete[] c;
    c = temp;
    len = len + str.len;
    cap = len + 1;
    return *this;
}

//Override << operator
std::ostream& operator<< (std::ostream& os, const MyString& str) {
    for(int i = 0; i < str.len; i++) {
        os << str.c[i];
    }
    return os;
}

//Find Function
size_t MyString::find(const MyString& str, size_t pos) const noexcept{
    bool match = false;
    if(pos >= len) {
        return -1;
    }

    for(int i = pos; i < len; i++) {
        if(c[i] == str.c[0] && (i + str.len) <= len) {
            for(int in = 0; in < str.len; in++) {
                match = true;
                if(c[i + in] != str.c[in]) {
                    match = false;
                }
            }
        }
        if(match == true) {
            return i;
        }
    }
    return -1;
}

//Override == operator
bool MyString::operator== (const MyString& str) noexcept {
    bool equiv = false;
    if(!(str.len == len)) {
        return equiv;
    }
    else {
        for(int i = 0; i < len; i++) {
            if(c[i] == str.c[i]) {
                equiv = true;
            }
            else {
                equiv = false;
                return equiv;
            }
        }
    }
    return equiv;
}