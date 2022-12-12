#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <iomanip>
#include <sstream>

#include "thingBinaryFile.h"
#include "thing.h"

#define NAME_SIZE 51
#define PRICE_SIZE sizeof(float)
#define AMOUNT_SIZE sizeof(unsigned int)

using namespace std;

ThingBinaryFile::ThingBinaryFile() {

}

ThingBinaryFile::ThingBinaryFile(string path) {
    this -> path = path;
}

ThingBinaryFile::~ThingBinaryFile() {

}

bool ThingBinaryFile::exists() const {
    struct stat buffer;   
    return (stat(this -> path.c_str(), &buffer) == 0); 
}

// Loads the file into a vector
vector<Thing> ThingBinaryFile::load() const {
    ifstream file(this -> path, ios::binary);
    vector<Thing> ret;

    file.seekg(0, ios::end);
    unsigned long int length = file.tellg();
    
    file.seekg(file.beg);
    while (file.tellg() < length) {
        char name[NAME_SIZE];
        file.read(name, NAME_SIZE);

        float price;
        file.read(reinterpret_cast<char*>(&price), PRICE_SIZE);

        unsigned int amount;
        file.read(reinterpret_cast<char*>(&amount), AMOUNT_SIZE);

        ret.push_back(Thing(string(name, NAME_SIZE - 1), price, amount));
    }
        
    return ret;
}

void ThingBinaryFile::save(vector<Thing> things) {
    ofstream file(this -> path, ios::binary | ios::trunc);

    for (Thing& thing : things) {
        string name = thing.getName();
        ostringstream oss;
        oss << std::setw (NAME_SIZE - 1) << name << std::endl;
        name = oss.str();

        file.write(name.c_str(), NAME_SIZE);

        float price = thing.getPrice();
        file.write(reinterpret_cast<char*>(&price), PRICE_SIZE);

        unsigned int amount = thing.getAmount();
        file.write(reinterpret_cast<char*>(&amount), AMOUNT_SIZE);
    }
}

void ThingBinaryFile::create() {
    ofstream create(path);
}

string ThingBinaryFile::getPath() const {
    return path;
}