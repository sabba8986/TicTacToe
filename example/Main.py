from PyQt6.QtWidgets import QApplication, QVBoxLayout, QWidget, QLabel, QPushButton
from PyQt6.QtGui import QIcon
from PyQt6.QtCore import Qt, QSize
import numpy as np
import math
import sys

list_pieces = {'r': "{color}_rook.png", 'k':"{color}_knight.png", 'b':"{color}_bishop.png", 'q':"{color}_queen.png", 'l':"{color}_king.png", 'p':"{color}_pawn.png"}
state = "RKBQLBKRPPPPPPPP________________________________pppppppprkbqlbkr"

def format_button(button, j, i, func):
    button.setIconSize(QSize(100, 100))
    button.clicked.connect(func)
    button.resize(100, 100)
    button.move(100*i, 100*j)


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.resize(800, 800)
        self.setWindowTitle("Chess")
        self.setWindowIcon(QIcon("icon.jpg"))

        layout = QVBoxLayout()
        self.setLayout(layout)
        isWhite = False

        for i in range(0, 8):
            for j in range(0, 8):
                button = QPushButton(None, self)
                button.setStyleSheet("background-color: {color}; border: none;".format(color = "#E3C16F" if isWhite else "#B88B4A"))
                tempChar = state[8*i + j]
                isNotEmpty = True
                match(tempChar.lower()):
                    case 'r':
                        button.setIcon(QIcon(list_pieces['r'].format(color =  "black" if tempChar.isupper() else "white")))
                    case 'k':
                        button.setIcon(QIcon(list_pieces['k'].format(color =  "black" if tempChar.isupper() else "white")))
                    case 'b':
                        button.setIcon(QIcon(list_pieces['b'].format(color =  "black" if tempChar.isupper() else "white")))
                    case 'q':
                        button.setIcon(QIcon(list_pieces['q'].format(color =  "black" if tempChar.isupper() else "white")))
                    case 'l':
                        button.setIcon(QIcon(list_pieces['l'].format(color =  "black" if tempChar.isupper() else "white")))
                    case 'p':
                        button.setIcon(QIcon(list_pieces['p'].format(color =  "black" if tempChar.isupper() else "white")))
                    case _:
                        isNotEmpty = False
                format_button(button, i, j, self.generateMoves if isNotEmpty else self.nothing)
                isWhite = not isWhite
            isWhite =  not isWhite
        
    def generateMoves(self, piece):
        print("Will implement")

    def nothing(self):
        pass





        


app = QApplication(sys.argv)
window = Window()
window.show()
sys.exit(app.exec())



