#include "Board.hpp"
#include "interface_functions.hpp"


extern "C" void init_game(){
    game = new Game();
}

extern "C" int make_the_move(int i){
    if(game->make_move(i)){
        return 1;
    }
    return 0;
}

extern "C" uint32_t best_move(){
    return game->best_possible_move();
}

extern "C" int who_is_currently_winning(){
    return game->who_is_winning();
}

extern "C" void reset(){
    game->reset();
}

extern "C" void set_first_turn(int is_computer_turn){
    game->set_first_turn(is_computer_turn);
}
