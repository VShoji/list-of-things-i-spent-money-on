#include <string>
#include <vector>
#include <exception>

#include "thingBinaryFile.h"
#include "thing.h"
#include "stringManipulator.h"

#define DEFAULT_PATH "./things.dat"
#define NAME_SIZE 50

using namespace std;

ThingBinaryFile file;

void clear() {
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

string readLine() {
    string ret;
    cin >> ret;
    cin.ignore();
    return ret;
}

void requireEnter() {
    cout << "Press enter to continue";
    cin.ignore();
}

void showFileNotFoundScreen() {
    for (;;) {
        cout << 
        "File not found." << endl << 
        "c - Create file at \"" + file.getPath() + "\"" << endl <<
        "f - Find file" << endl <<
        "x - Exit program" << endl <<
        "Selected option: ";

        string option = readLine();

        if (option == "c") {
            file.create();
            break;
        }
        if (option == "f") {
            cout << endl << "File path: ";

            string path = readLine();
            file = ThingBinaryFile(path);

            if (!file.exists())
                continue;

            break;
        }
        if (option == "x") {
            exit(0);
            break;
        }

        cout << endl << "Invalid option" << endl;
        requireEnter();
        clear();
    }

    clear();
}

void checkFile(string path = DEFAULT_PATH) {
    file = ThingBinaryFile(path);
    if (!file.exists()) 
        showFileNotFoundScreen();
}

void listThings() {
    clear();
    if (file.empty()) {
        cout << "List is empty" << endl;
        requireEnter();
        return;
    }

    int counter = 0;
    for (Thing& thing : file.load())
        cout << to_string(counter++) << ": " << thing.toString() << endl;

    requireEnter();
}

void addThing() {
    bool cancel = false;
    string name;
    for (;;) {
        clear();

        cout << "x - Cancel" << endl 
             << "Name: ";
        getline(cin, name);
        StringManipulator::trim(name);

        if (name == "x") {
            cancel = true;
            break;
        }

        if (name.empty()) {
            cout << "Enter a valid name" << endl;
            requireEnter();
            continue;
        }

        if (name.size() > NAME_SIZE) {
            cout << "Name too large" << endl;
            requireEnter();
            continue;
        }
        
        break;
    }

    float price;
    for (;;) {
        if (cancel)
            break;

        clear();

        string aux;
        cout << "x - Cancel" << endl 
             << "Price: ";
        aux = readLine();

        if (aux == "x") {
            cancel = true;
            break;
        }

        try {
            price = stof(aux);
        }
        catch (invalid_argument e) {
            cout << "Enter a valid price" << endl;
            requireEnter();
            continue;
        }

        if (price < 0) {
            cout << "Price cannot be negative" << endl;
            requireEnter();
            continue;
        }
        
        break;
    }

    unsigned int amount;
    for (;;) {
        if (cancel)
            break;

        clear();

        string aux;
        cout << "x - Cancel" << endl 
             << "Amount: ";
        aux = readLine();

        if (aux == "x") {
            cancel = true;
            break;
        }

        try {
            amount = stoul(aux);
        }
        catch (invalid_argument e) {
            cout << "Enter a valid amount" << endl;
            requireEnter();
            continue;
        }

        if (amount < 1) {
            cout << "Price cannot be zero" << endl;
            requireEnter();
            continue;
        }

        break;
    }

    if (!cancel)
        //things.push_back(Thing(name, price, amount));
        file.append(Thing(name, price, amount));
}

void removeThing() {
    unsigned long int length = file.size();
    for (;;) {
        clear();

        cout << "x - Cancel" << endl
             << "Thing to remove: ";
        string aux = readLine();

        if (aux == "x")
            break;

        unsigned long index;

        try {
            index = stoul(aux);
        }
        catch (invalid_argument e) {
            cout << "Enter a valid index" << endl;
            requireEnter();
            continue;
        }

        if (index >= length) {
            cout << "Index out of range" << endl;
            requireEnter();
            continue;
        }

        file.erase(index);
        break;
    }
}

void editThing() {
    unsigned long int length = file.size();
    bool cancel = false;
    unsigned long index;

    for (;;) {
        clear();

        cout << "x - Cancel" << endl
             << "Thing to edit: ";
        string aux = readLine();

        if (aux == "x")
            break;


        try {
            index = stoul(aux);
        }
        catch (invalid_argument e) {
            cout << "Enter a valid index" << endl;
            requireEnter();
            continue;
        }

        if (index >= length) {
            cout << "Index out of range" << endl;
            requireEnter();
            continue;
        }

        break;
    }
    
    string name;
    for (;;) {
        if (cancel)
            break;

        clear();

        cout << "x - Cancel" << endl 
             << "Name: ";
        getline(cin, name);
        StringManipulator::trim(name);

        if (name == "x") {
            cancel = true;
            break;
        }

        if (name.empty()) {
            cout << "Enter a valid name" << endl;
            requireEnter();
            continue;
        }

        if (name.size() > NAME_SIZE) {
            cout << "Name too large" << endl;
            requireEnter();
            continue;
        }
        
        break;
    }

    float price;
    for (;;) {
        if (cancel)
            break;

        clear();

        string aux;
        cout << "x - Cancel" << endl 
             << "Price: ";
        aux = readLine();

        if (aux == "x") {
            cancel = true;
            break;
        }

        try {
            price = stof(aux);
        }
        catch (invalid_argument e) {
            cout << "Enter a valid price" << endl;
            requireEnter();
            continue;
        }

        if (price < 0) {
            cout << "Price cannot be negative" << endl;
            requireEnter();
            continue;
        }
        
        break;
    }

    unsigned int amount;
    for (;;) {
        if (cancel)
            break;

        clear();

        string aux;
        cout << "x - Cancel" << endl 
             << "Amount: ";
        aux = readLine();

        if (aux == "x") {
            cancel = true;
            break;
        }

        try {
            amount = stoul(aux);
        }
        catch (invalid_argument e) {
            cout << "Enter a valid amount" << endl;
            requireEnter();
            continue;
        }

        if (amount < 1) {
            cout << "Price cannot be zero" << endl;
            requireEnter();
            continue;
        }

        break;
    }

    if (!cancel)
        file.put(Thing(name, price, amount), index);
}

void showOperations() {
    for (;;) {
        clear();
        cout << "l - List things" << endl <<
                "a - Add a new thing" << endl <<
                "r - Remove a thing" << endl <<
                "e - Edit a thing" << endl <<
                "x - Exit program" << endl <<
                "Selected option: ";
        
        string option = readLine();

        if (option == "l") {
            listThings();
            continue;
        }

        if (option == "a") {
            addThing();
            continue;
        }

        if (option == "r") {
            removeThing();
            continue;
        }

        if (option == "e") {
            editThing();
            continue;
        }

        if (option == "x") {
            clear();
            break;
        }

        cout << endl << "Invalid option" << endl;
        requireEnter();
    }
}
int main(int argc, char *argv[]) {
    clear();
    checkFile();
    showOperations();
}