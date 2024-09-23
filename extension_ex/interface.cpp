#include "Dummy.hpp"

Dummy* dummy;

extern "C" void create_dummy(const char* name){
    dummy = new Dummy(name);
}

extern "C" void print_out_the_name(){
    dummy->print_name();
}
