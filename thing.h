#ifndef THING
    #include <string>
    #include <iostream>
    using namespace std;

    #define THING
    class Thing {
        private:
            unsigned int id;
            string name;
            float price;
            unsigned int amount;
        public:
            static const int NAME_SIZE;
            static const int TOTAL_SIZE;

            Thing();
            Thing(string, float, unsigned int) throw (invalid_argument);
            // ~Thing();

            string getName() const;
            void setName(string) throw (invalid_argument);

            float getPrice() const;
            void setPrice(float) throw (invalid_argument);

            unsigned int getAmount() const;
            void setAmount(unsigned int) throw (invalid_argument);

            string toString();
    };
 #endif