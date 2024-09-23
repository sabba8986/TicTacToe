#ifndef INTERFACE  
#define INTERFACE  

#include "Board.hpp"

static Game* game;

extern "C" void init_game();

extern "C" int make_the_move(int i);

extern "C" uint32_t best_move();

extern "C" int who_is_currently_winning();

extern "C" void reset();

extern "C" void set_first_turn(int is_computer_turn);
#endif
