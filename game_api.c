#define PY_SSIZE_T_CLEAN
#include <python3.10/Python.h>
#include <wchar.h>


extern void init_game();
extern int make_the_move(int i);
extern uint32_t best_move();
extern int who_is_currently_winning();
extern void reset();
extern void set_first_turn(int is_computer_turn);


static PyObject* py_game_api_start(PyObject* self, PyObject* args){
    init_game();
    Py_INCREF(Py_None);
    return Py_None;
}



static PyObject* py_make_move(PyObject* self, PyObject* args){
    int place;
    
    if(!PyArg_ParseTuple(args, "i", &place)){
        return NULL;
    }

    int result = make_the_move(place);
    if(result){
        Py_INCREF(Py_True);
        return Py_True;
    }
    Py_INCREF(Py_False);
    return Py_False;
}



static PyObject* py_best_possible_move(PyObject* self, PyObject* args){
    uint32_t best_board = best_move();
    unsigned long best_board_in_long = (unsigned long)best_board;
    return PyLong_FromUnsignedLong(best_board_in_long);
}



static PyObject* py_who_is_winning(PyObject* self, PyObject* args){
    int win_val = who_is_currently_winning();
    return PyLong_FromLong(win_val);
}


static PyObject* py_reset_game(PyObject* self, PyObject* args){
    reset();
    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject* py_set_first_turn(PyObject* self, PyObject* args){
    int is_computer_turn;

    if(!PyArg_ParseTuple(args, "i", &is_computer_turn)){
        return NULL;
    }

    set_first_turn(is_computer_turn);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef game_api_methods[] = {
    {"init_game", py_game_api_start, METH_VARARGS, "Creates the Game Object that represents the current state of the game."},
    {"make_move", py_make_move, METH_VARARGS, "Places an X (player's token) at the input spot, and updates the board state."},
    {"best_possible_move", py_best_possible_move, METH_VARARGS, "Returns the state of the board after the computer makes the best possible move it can make. Will set current board to be this state."},
    {"who_won", py_who_is_winning, METH_VARARGS, "Returns who is currently winning in the current board."},
    {"reset_game", py_reset_game, METH_VARARGS, "Clears the board and resets the game."}, 
    {"set_first_turn", py_set_first_turn, METH_VARARGS, "Sets the first turn of the current game to the given input boolean."},
    {NULL, NULL, 0, NULL}
};



static PyModuleDef game_api_module = {
    PyModuleDef_HEAD_INIT, 
    "game_api",
    NULL, 
    -1, 
    game_api_methods
};


PyMODINIT_FUNC PyInit_game_api(){
    return PyModule_Create(&game_api_module);
}

