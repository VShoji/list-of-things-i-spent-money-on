#include <string>
#include <vector>
#include <exception>

#include "thingBinaryFile.h"
#include "thing.h"

#define DEFAULT_PATH "./things.dat"

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

        cout << endl << 
        "Invalid option" << endl <<
        "Press enter to continue...";
        
        cin.ignore();
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