#include "Board.hpp"

int main(){
    Game game; 
    /*while(true){
        std::string response;
        std::cout << "Enter a board config: ";
        std::cin >> response;

        uint32_t new_board = 0;
        unsigned int comp = 131072;
        unsigned int player = 65536;
        for(int i = 0; i < 9; i++){
            if(response[i] == 'X'){
                new_board |= player;
            } else if(response[i] == 'O'){
                new_board |= comp;
            }
            comp >>= 2;
            player >>= 2;
        }
        Game::print_board(new_board);
        std::cout << "   has a win value of " << Game::who_won(new_board) << "and value (with comp first and not) ";
        std::cout << game.value(new_board, true) << " and " << game.value(new_board, false) << std::endl << std::endl; 
    }*/  
    game.start();
    return 0;
}
