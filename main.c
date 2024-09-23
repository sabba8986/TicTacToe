#include<stdint.h>
#include<stdio.h> 


extern void init_game(int is_computer_turn);
extern int make_the_move(int i);
extern uint32_t best_move();
extern int who_is_currently_winning();
extern void reset(int is_computer_turn);


int main(){
    init_game(1);
    make_the_move(2);
    printf("%u", best_move());
    return 0;
}
