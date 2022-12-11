#ifndef THING
    #define THING
    #include <string>
    #include <iostream>
    using namespace std;
    
    class Thing {
        private:
            string name;
            float price;
            unsigned int amount;
        public:
            Thing(string, float, unsigned int) throw (invalid_argument);
            ~Thing();

            string getName() const;
            void setName(string) throw (invalid_argument);

            float getPrice() const;
            void setPrice(float) throw (invalid_argument);

            unsigned int getAmount() const;
            void setAmount(unsigned int) throw (invalid_argument);

            string toString();
    };
 #endif