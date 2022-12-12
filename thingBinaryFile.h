#ifndef THINGBINARYFILE
    #include <string>
    #include <vector>

    #include "thing.h"

    using namespace std;

    #define THINGBINARYFILE
    class ThingBinaryFile {
        private:
            string path;
            Thing readThing();
            void writeThing(Thing, ofstream);

        public:
            ThingBinaryFile();
            ThingBinaryFile(string);
            ~ThingBinaryFile();

            void save(vector<Thing>);
            vector<Thing> load() const;

            Thing peek(unsigned int) const;
            void put(Thing, unsigned int) throw (exception);
            void erase(unsigned int);
            void insert(Thing);

            bool exists() const;
            void create();

            string getPath() const;
            bool empty() const;
            unsigned int size() const;
    };

#endif