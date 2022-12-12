#ifndef THINGBINARYFILE
    #include <string>
    #include <vector>

    #include "thing.h"

    using namespace std;

    #define THINGBINARYFILE
    class ThingBinaryFile {
        private:
            string path;
        public:
            ThingBinaryFile();
            ThingBinaryFile(string);
            ~ThingBinaryFile();

            void save(vector<Thing>);
            vector<Thing> load() const;

            Thing peek(long int) const;
            void put(Thing, long int);

            bool exists() const;
            void create();

            string getPath() const;
    };

#endif