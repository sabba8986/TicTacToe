#include <iostream>
#include <string>

class Dummy{
    private:
        std::string name;
    public:
        Dummy(const char *name){
            this->name = std::string(name);
        }

        void print_name(){
            std::cout << "Hi, my name is " << name << std::endl;
        }
};
