#include <string>

#include "stringManipulator.h"

using namespace std;

// trim from start (in place)
inline void StringManipulator::ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}

// trim from end (in place)
inline void StringManipulator::rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void StringManipulator::trim(string &s) {
    rtrim(s);
    ltrim(s);
}