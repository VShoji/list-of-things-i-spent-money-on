#include <string>
#include <vector>
#include <exception>

#include "thingBinaryFile.h"
#include "thing.h"
#include "stringManipulator.h"

#define DEFAULT_PATH "./things.dat"
#define NAME_SIZE 50

using namespace std;

vector<Thing> things;
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

void loadFile(string path = DEFAULT_PATH) {
    file = ThingBinaryFile(path);
    if (!file.exists()) 
        showFileNotFoundScreen();
    
    things = file.load();
}

void listThings() {
    clear();
    if (things.empty())
        cout << "List is empty" << endl;

    int counter = 0;
    for (Thing& thing : things)
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
        things.push_back(Thing(name, price, amount));
}


}

void showOperations() {
    for (;;) {
        cout << "l - List things" << endl <<
                "a - Add a new thing" << endl <<
                "r - Remove a thing" << endl <<
                "e - Edit a thing" << endl <<
                "Selected option: ";
        
        string option = readLine();

        if (option == "l")
            listThings();
    }
}


int main(int argc, char *argv[]) {
    clear();
    loadFile();
    showOperations();
}