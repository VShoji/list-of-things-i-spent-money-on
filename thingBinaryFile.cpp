#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <iomanip>
#include <sstream>

#include "thingBinaryFile.h"
#include "thing.h"

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

void ThingBinaryFile::writeThing(Thing thing, ofstream file) {
}

bool ThingBinaryFile::exists() const {
    struct stat buffer;   
    return (stat(this -> path.c_str(), &buffer) == 0); 
}

unsigned int ThingBinaryFile::size() const {
    ifstream file(this->path, ios::binary);

    file.seekg(0, ios::end);
    return file.tellg();
}

// Loads the file into a vector
vector<Thing> ThingBinaryFile::load() const {
    vector<Thing> ret;

    unsigned int length = this->size();
    ifstream file(this->path, ios::binary);
    while (file.tellg() < length) {
        char* name = new char[Thing::NAME_SIZE + 1];
        file.read(name, Thing::NAME_SIZE + 1);

        float price;
        file.read(reinterpret_cast<char*>(&price), PRICE_SIZE);

        unsigned int amount;
        file.read(reinterpret_cast<char*>(&amount), AMOUNT_SIZE);

        ret.push_back(Thing(string(name, Thing::NAME_SIZE), price, amount));
        delete[] name;
    }
        
    return ret;
}

void ThingBinaryFile::create() {
    ofstream create(path);
}

string ThingBinaryFile::getPath() const {
    return path;
}

bool ThingBinaryFile::empty() const {
    ifstream file(this -> path, ios::binary);
    file.seekg(0, ios::end);
    return file.tellg() == 0;
}

void ThingBinaryFile::insert(Thing thing) {
    ofstream file(this -> path, ios::binary | ios_base::app);
    file.seekp(0, ios::end);

    string name = thing.getName();
    ostringstream oss;
    oss << std::setw(Thing::NAME_SIZE) << name << std::endl;
    name = oss.str();

    file.write(name.c_str(), Thing::NAME_SIZE + 1);

    float price = thing.getPrice();
    file.write(reinterpret_cast<char*>(&price), PRICE_SIZE);

    unsigned int amount = thing.getAmount();
    file.write(reinterpret_cast<char*>(&amount), AMOUNT_SIZE);
}

void ThingBinaryFile::put(Thing thing, unsigned int id) throw (exception){
    ofstream file(this->path, ios::binary | ios_base::app);
    if (index >= this->size())
        throw exception("Index out of range");

    file.seekp(Thing::TOTAL_SIZE * index);

    string name = thing.getName();
    ostringstream oss;
    oss << std::setw(Thing::NAME_SIZE) << name << std::endl;
    name = oss.str();

    file.write(name.c_str(), Thing::NAME_SIZE + 1);

    float price = thing.getPrice();
    file.write(reinterpret_cast<char*>(&price), PRICE_SIZE);

    unsigned int amount = thing.getAmount();
    file.write(reinterpret_cast<char*>(&amount), AMOUNT_SIZE);
}

void ThingBinaryFile::erase(unsigned int id) {

}