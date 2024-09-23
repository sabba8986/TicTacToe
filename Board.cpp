#include "Board.hpp"
#include "defines.hpp"



constexpr static uint32_t computer_wins[] = {42, 2688, 172032, 133152, 33288, 8322, 131586, 8736};
constexpr static uint32_t player_wins[] = {21, 1344, 86016, 66576, 16644, 4161, 65793, 4368};



std::unordered_map<uint32_t, int> Game::map;




Game::Game(): cur_board(0){}


int Game::eval(uint32_t board){
    bool is_full = true;
    unsigned int trav = BITBOARD_TOP_LEFT;
    for(int i = 0; i < 8; i++, trav >>= 2){
        if(!(board & trav)){
            is_full = false;
        }
        if((board & computer_wins[i]) == computer_wins[i]) return 1;
        else if((board & player_wins[i]) == player_wins[i]) return -1;
    }
    if(is_full && (board & trav)) return 0;
    return 2;
}



void Game::print_board(uint32_t board){
    unsigned int temp = BITBOARD_TOP_LEFT;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if((board & temp) == COMPUTER) std::cout << "O";
            else if((board & temp) == PLAYER) std::cout << "X";
            else std::cout << " ";
            board <<= 2;
            if(j < 2) std::cout << " | ";
        }
        if(i < 2) std::cout << "\n---------\n";    
    }
    
}


std::vector<uint32_t> Game::all_moves(uint32_t board){

}


int8_t Game::value(uint32_t board, int8_t alpha, int8_t beta){ //computer is always a maximizer, player is always a minimizer 
    if(map.count(board) == 1) return map[board];

    int8_t val = eval(board);
    if(val != 2) return val;

    uint32_t prev_board = board;
    bool is_computer_turn = board & COMPUTER_TURN ? true : false; //if msb set then computer turn otherwise player turn
    board ^= COMPUTER_TURN; 
    uint32_t trav = BITBOARD_TOP_LEFT;
    uint32_t cur_player = is_computer_turn ? COMPUTER : PLAYER;
    val = is_computer_turn ? INT8_MIN : INT8_MAX;
    for(int i = 0; i < 9; i++){
        if(!(board & trav)){
            uint32_t new_board = (board & (~trav)) | cur_player;
            int new_val = value(new_board, is_computer_turn ? val : alpha, is_computer_turn ? beta : val);
            if(is_computer_turn ? new_val > val : new_val < val){
                val = new_val;
                if(is_computer_turn ? val >= beta : alpha >= val){
                    std::cout << "Temp \n";
                    break;
                }
            }
        }
        trav >>= 2;
        cur_player >>= 2;
    }
    map[prev_board] = val;
    return val;
}






uint32_t Game::best_possible_move(){
    uint32_t board = cur_board;
    board &= ~COMPUTER_TURN;
    int8_t alpha = INT8_MIN;
    int8_t beta = INT8_MAX;
    uint32_t best_board = board;
    unsigned int trav = BITBOARD_TOP_LEFT;
    unsigned int computer = COMPUTER;
    for(int i = 0; i < 9; i++){
        if(!(board & trav)){
            uint32_t new_board = (board & (~trav)) | computer; 
            int new_val = value(new_board, alpha, beta);
            if(new_val > alpha){ 
                alpha = new_val;
                best_board = new_board;
            }
        }
        trav >>= 2;
        computer >>= 2;
    }
    cur_board = best_board;
    return best_board;
}




bool Game::make_move(int i){
    int num_shifts = 2*(i - 1);
    uint32_t pos = BITBOARD_TOP_LEFT >> num_shifts;
    if(cur_board & pos) return false;
    uint32_t turn =  PLAYER >> num_shifts;
    cur_board = (cur_board & (~pos)) | (PLAYER >> num_shifts);
    cur_board |= COMPUTER_TURN;
    return true;
}



int Game::who_is_winning(){
    return eval(cur_board);
}


void Game::begin(){
    char response;
    std::cout << "Welcome to TicTacToe!" << std::endl;
    std::cout << "Would you like to go first? (Y or N): ";
    std::cin >> response;
    bool is_player_turn = (response == 'Y' || response == 'y') ? true : false;
    int cur_win_val = 0;
    reset();
    set_first_turn(!is_player_turn);
    print_board(cur_board);
    std::cout << std::endl;
    while((cur_win_val = eval(cur_board)) == 2){
        if(is_player_turn){
            bool repeat = false;
            int move;
            do{
                std::cout << "Where would you like to place your piece? (Enter a number between 1-9): ";
                std::cin >> move;
                repeat = (move <= 0 || move >= 10);
                if(repeat){
                    std::cout << "Please enter a number between 1-9.\n";
                } else{
                    repeat = !make_move(move);
                    if(repeat) std::cout << "There is already a piece there, please choose another tile.\n";
                }
            } while(repeat);
        } else{
            std::cout << "The computer is making its move...\n";
            best_possible_move();
        }
        std::cout << "The current state of the board is: \n";
        print_board(cur_board);
        std::cout << std::endl;
        is_player_turn = !is_player_turn;
    }
    if(cur_win_val == 0){
        std::cout << "It's a draw!\n";
    } else if(cur_win_val == 1){
        std::cout << "The computer wins!\n";
    } else{
        std::cout << "You win!\n";
    }
}

void Game::start(){
    bool repeat = false;
    char response;
    do{
        begin();
        std::cout << "Want to play again? ";
        std::cin >> response;
        std::cout << std::endl;
        if(response == 'Y' || response == 'y') repeat = true;
        else repeat = false;
    } while(repeat);
}

void Game::reset(){
    cur_board = 0;
}

void Game::set_first_turn(bool is_computer_turn){
    if(is_computer_turn){
        cur_board |= COMPUTER_TURN; 
    } else{
        cur_board &= ~COMPUTER_TURN;
    }
}
