// TODO: Implement this header file
#ifndef _MYSTRING_H
#define _MYSTRING_H

#include <iostream>

class MyString {
    private:  
        char* c;
        int len;
        int cap;
    public: 
        MyString();
        MyString(const MyString& str);
        MyString(const char* c);
        ~MyString();
        void resize(size_t s);
        int capacity();
        size_t size() const noexcept;
        size_t length();
        const char* data();
        bool empty();
        const char& front() const;
        const char& at(size_t s) const;
        void clear();
        friend std::ostream& operator<< (std::ostream& os, const MyString& str);
        MyString& operator= (const MyString& str);
        MyString& operator+= (const MyString& str);
        size_t find (const MyString& str, size_t pos = 0) const noexcept;
        bool operator== (const MyString& str) noexcept;
};
#endif 