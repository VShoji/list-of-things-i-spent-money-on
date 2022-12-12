#ifndef STRINGMANIPULATION
    #include <string>
    using namespace std;
    
    #define STRINGMANIPULATION
        static class StringManipulator {
            public:
                static inline void ltrim(string &s);
                static inline void rtrim(string &s);
                static inline void trim(string &s);
        };
#endif