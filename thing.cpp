#include "thing.h"
#include <string>
#include <iostream>
#include <exception>
using namespace std;

// trim from start (in place)
static inline void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(string &s) {
    rtrim(s);
    ltrim(s);
}

Thing::Thing(std::string name, float price, unsigned int amount) {
    setName(name);
    setPrice(price);
    setAmount(amount);
}

string Thing::getName() const {
    return this -> name;
}

void Thing::setName(string name) {
    trim(name);
    if (name.empty())
        throw invalid_argument("Empty name");

    this -> name = name;
}

float Thing::getPrice() const {
    return this -> price;
}

void Thing::setPrice(float price) {
    if (price < 0)
        throw invalid_argument("Price less than zero");

    this -> price = price;
}

unsigned int Thing::getAmount() const {
    return this -> amount;
}

void Thing::setAmount(unsigned int amount) {
    this -> amount = amount;
}

string Thing::toString() {
    return "{ Name: \"" + getName() +"\" Price: " + to_string(getPrice()) + " Amount: " + to_string(getAmount()) + " }";
}