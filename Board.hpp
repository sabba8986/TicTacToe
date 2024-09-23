#ifndef BOARD 
#define BOARD
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <unordered_map>


/*Board format:
  1 | 2 | 3
  ---------
  4 | 5 | 6
  ---------
  7 | 8 | 9
*/



/*
 * Empty = " " = 00
 * Player = X = 01
 * Computer = O = 10
*/


class Game{
public:
private:
    uint32_t cur_board; //current state of board. The most significant bit is set to 1 if it is the computer's turn next, and 0 if it is the player's turn next
    static std::unordered_map<uint32_t, int> map; //map of states to their values
    
    //prints the given board onto standard output
    static void print_board(uint32_t board);
    
    //returns -1 if the player won, 1 if the computer won, 0 if it is a draw, or 2 if the game should be continued, in board
    static int eval(uint32_t board);
       
    //returns the value of the current board for the computer (this is used to calculate the best move using min-max)
    int8_t value(uint32_t board, int8_t alpha, int8_t beta);
    
    //private function used to help start the current board
    void begin();

    //returns a list of all possible moves that can be made from the given board configuration
    static std::vector<uint32_t> all_moves(uint32_t board);

public:
    //initializes the current Game, setting the board to 0 (if no boolean is provided, it is assumed the player goes first)
    Game();
   
    //places an X (player's token) at the given index i (from 1-9), returning true if the piece was successfully placed, or false otherwise
    bool make_move(int i);
    
    //returns the best possible move the computer could make from the current board configuration. Changes the current board to that board
    uint32_t best_possible_move();

    //returns the value of who_won of the current board (who is currently winning)
    int who_is_winning();

    //starts the current game instance
    void start();

    //resets the current board to empty
    void reset();

    //sets the first turn of the current game instance 
    void set_first_turn(bool is_computer_turn);
};

#endif
