from PyQt6.QtWidgets import QVBoxLayout, QWidget, QLabel, QPushButton, QMessageBox 
from PyQt6.QtGui import QIcon, QFont
from PyQt6.QtWidgets import QApplication
from PyQt6.QtCore import QSize
import sys
import game_api





def format_tile(window, i, j):
    n = 3*i + j
    button = QPushButton(None, window)
    button.setStyleSheet("background-color: green; border: 1px solid black;") 
    button.clicked.connect(lambda temp, ind = (n): window.make_a_move(ind)) 
    button.resize(QSize(200, 200))
    button.move(200 * j, 200 * i)
    button.setIconSize(QSize(200, 200))
    return button

def format_play_again_button(window):
    play_again = QPushButton("Play again", window)
    play_again.setFont(QFont('Arial', 40))
    play_again.resize(QSize(400, 250))
    play_again.move(800, 250)
    play_again.clicked.connect(window.start_game)
    return play_again

def format_message_text(window):
    player_message = QLabel("", window)
    player_message.setFont(QFont('Arial', 20))
    player_message.move(50, 650)
    player_message.resize(QSize(800, 50))
    return player_message



class Window(QWidget):
    game_in_session = False
    is_computer_turn = False
    tiles = list(range(9))
    player_message = None
    play_again = None
    X = None
    O = None
    Empty = None

    def __init__(self):
        super().__init__()
        self.resize(1400, 700)

        layout = QVBoxLayout()
        self.setLayout(layout)
        for i in range(0, 3):
            for j in range(0, 3):
                (self.tiles)[3*i + j] = format_tile(self, i, j)
        
        self.play_again = format_play_again_button(self)

        self.player_message = format_message_text(self)

        game_api.init_game()
        self.show()

        self.X = QIcon("X.png")
        self.O = QIcon("O.png")
        self.Empty = QIcon("Empty.png")
        self.start_game()


    def make_a_move(self, index):
        if(not self.game_in_session):
            return
        repeat = game_api.make_move(index + 1)
        if(not repeat):
            self.player_message.setText("Please choose an empty square")
        else:
            (self.tiles)[index].setIcon(self.X)
            self.game_loop_iteration_player(True)
            self.check_win()
    

    def display_board(self, board):
        trav = 196608
        comp = 131072
        player = 65536
        counter = 0
        while(trav != 0):
            button = (self.tiles)[counter]
            val = board & trav
            if((val & comp) != 0):
                button.setIcon(self.O)
            elif((val & player) != 0):
                button.setIcon(self.X)
            else:
                button.setIcon(self.Empty)
            trav >>= 2 
            comp >>= 2 
            player >>= 2 
            counter += 1



    def game_loop_iteration_player(self, is_computer_turn):
        if(is_computer_turn):
            self.player_message.setText("The computer is making its turn...")
            new_board = game_api.best_possible_move()
            self.display_board(new_board)
        self.player_message.setText("Please choose a square")


    def check_win(self):
        continue_game = game_api.who_won()
        if(continue_game != 2):
            self.game_in_session = False
            if(continue_game == 0):
                self.player_message.setText("It's a draw!")
            elif(continue_game == 1):
                self.player_message.setText("The computer won!")
            elif(continue_game == -1):
                self.player_message.setText("The player won!")


    def start_game(self):
        self.display_board(0)
        game_api.reset_game()
        pop_up = QMessageBox(self)
        pop_up.setWindowTitle("Welcome!")
        pop_up.setFont(QFont('Arial', 20))
        pop_up.resize(600, 400)
        pop_up.setText("Would you like to go first?")
        pop_up.addButton("Yes", QMessageBox.ButtonRole.AcceptRole)
        pop_up.addButton("No", QMessageBox.ButtonRole.RejectRole)
        result = pop_up.exec() 
        input = (False if result==0 else True)
        game_api.set_first_turn(input)
        self.is_computer_turn = input
        self.game_in_session = True
        self.game_loop_iteration_player(input)


        

if(__name__ == '__main__'):
    app = QApplication(sys.argv)
    window = Window()
    sys.exit(app.exec())



