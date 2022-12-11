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
            Thing(string, float, unsigned int);
            ~Thing();

            string getName() const;
            void setName(string);

            float getPrice() const;
            void setPrice(float);

            unsigned int getAmount() const;
            void setAmount(unsigned int);

            string toString();
    };
 #endif