#include <string>
#include <iostream>
#include <exception>

#include "thing.h"
#include "stringManipulation.cpp"

#define MAXIMUM_NAME_SIZE 50
#define MINIMUM_PRICE 0
#define MINIMUM_AMOUNT 1

using namespace std;

Thing::Thing(string name, float price, unsigned int amount) throw (invalid_argument) {
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