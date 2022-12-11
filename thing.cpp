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
#define MAXIMUM_NAME_SIZE 50
#define MINIMUM_PRICE 0
#define MINIMUM_AMOUNT 1

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
    if (name.size() > MAXIMUM_NAME_SIZE)
        throw invalid_argument("Name too big");

    this -> name = name;
}

float Thing::getPrice() const {
    return this -> price;
}

void Thing::setPrice(float price) {
    if (price < MINIMUM_PRICE)
        throw invalid_argument("Price less than zero");

    this -> price = price;
}

unsigned int Thing::getAmount() const {
    return this -> amount;
}

void Thing::setAmount(unsigned int amount) {
    if (amount < MINIMUM_AMOUNT)
        throw invalid_argument("Amount less than minimum");
    this -> amount = amount;
}

string Thing::toString() {
    return "{ Name: \"" + getName() +"\" Price: " + to_string(getPrice()) + " Amount: " + to_string(getAmount()) + " }";
}