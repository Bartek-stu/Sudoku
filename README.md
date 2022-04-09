# Sudoku DLX
Simple sudoku program with generator written in C++ and GUI in Python.  
Generator uses Donald Knuth's Dancing Links technique, which treats sudoku as an exact cover problem.  
GUI is implemented in Python with tkinter library.

## Requirements
* g++
* Python 3

Note: If you're having problems with compiling the generarator go to /generator directory and run:
```
g++ DataStruct.cpp Sudoku.cpp InitializeArray.cpp main.cpp -std=c++11 -o Generator
```
#
To execute the program just go to /Sudoku directory and run:
```
python sudoku.py
```
![](https://github.com/Bartek-stu/Sudoku/blob/master/readme/sudoku.gif)



