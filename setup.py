from setuptools import setup, Extension

game_api_module_obj = Extension('game_api', sources = ['game_api.c', 'interface_functions.cpp', 'Board.cpp'], extra_compile_args=['-std=c++11'], language = 'c++')

setup(name = 'game_api', version = '1.0', description = "An interface to the C++ Game Object", ext_modules=[game_api_module_obj])
