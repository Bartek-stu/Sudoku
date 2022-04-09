from tkinter import *
import os
import time


def ValidateNumber(P):
    return (P.isdigit() or not P) and len(P) < 2 and P != '0'


class SudokuGUI:
    def __init__(self, master):
        self.root = master
        self.root.title("Sudoku")
        self.cells = {}
        self.reg = self.root.register(ValidateNumber)
        self.checkGenerator()

        self.right_values, self.known_values = self.loadValues()
        self.draw9x9Grid()
        self.clear_btn = Button(self.root, command=self.clearValues, text="Clear input", width=10).grid(
            row=20, column=0, columnspan=3, pady=20)
        self.check_btn = Button(self.root, command=self.checkValues, text="Check values", width=10).grid(
            row=20, column=3, columnspan=3, pady=20)
        self.gen_btn = Button(self.root, command=self.generateNewSudoku, text="Generate new sudoku", width=12).grid(
            row=20, column=6, columnspan=3, pady=20)
        self.root.mainloop()

    def loadValues(self):
        values = []
        try:
            with open("sudoku.txt") as sudoku:
                values = sudoku.read()
                values = values.split()
                values = [[value for value in values[i:i + 9]]
                          for i in range(0, len(values), 9)]
        except FileNotFoundError:
            self.generateNewSudoku()
            return self.loadValues()
        return values[:9], values[9:]

    def draw3x3Grid(self, row, column, bgcolor):
        for i in range(3):
            for j in range(3):
                if int(self.known_values[row + i][column + j]):
                    e = Label(root, text=str(
                        self.known_values[row + i][column + j]))
                    e.config(bg=bgcolor)
                    e.grid(row=row + i, column=column + j,
                           sticky="nsew", padx=5, pady=5, ipady=5)
                else:
                    e = Entry(root, width=5, bg=bgcolor,
                              justify="center", validate="key", validatecommand=(self.reg, "%P"))
                    e.grid(row=row + i, column=column + j,
                           sticky="nsew", padx=1, pady=1, ipady=5)
                self.cells[(row + i, column + j)] = e

    def draw9x9Grid(self):
        color = "#edd6c2"
        for rowNo in range(0, 9, 3):
            for colNo in range(0, 9, 3):
                self.draw3x3Grid(rowNo, colNo, color)
                color = "#c2e6ed" if color == "#edd6c2" else "#edd6c2"

    def clearValues(self):
        for row in range(0, 9):
            for col in range(0, 9):
                cell = self.cells[(row, col)]
                try:
                    cell.delete(0, "end")
                    cell.config(fg="#000000")
                except AttributeError:
                    pass

    def checkValues(self):
        is_finished = True
        for rowNo in range(0, 9):
            for colNo in range(0, 9):
                cell_value = None
                try:
                    cell_value = self.cells[(rowNo, colNo)].get()
                except AttributeError:
                    continue
                if cell_value == self.right_values[rowNo][colNo]:
                    self.cells[(rowNo, colNo)].config(fg='#74B72E')
                else:
                    if cell_value:
                        self.cells[(rowNo, colNo)].config(fg='#dc143c')
                    is_finished = False
        if is_finished:
            self.popUp()

    def checkGenerator(self):
        try:
            if not os.popen("ls ./generator | grep Generator").read().strip():
                os.system(
                    "cd generator; g++ DataStruct.cpp Sudoku.cpp InitializeArray.cpp main.cpp -o Generator > /dev/null")
        except Exception:
            print("You are not using Unix system, can't check whether generator exists...")

    def generateNewSudoku(self):
        os.system("./generator/Generator > /dev/null")
        time.sleep(3)
        self.right_values, self.known_values = self.loadValues()
        self.clearGrid()
        self.draw9x9Grid()

    def clearGrid(self):
        for cell in self.cells.values():
            cell.grid_remove()

    def popUp(self):
        popup = Toplevel()
        label = Label(popup, text="Congrats! Would you like to try a new game?")
        label.grid()
        new_game_btn = Button(popup, text="Yes", command=lambda:[self.generateNewSudoku(), popup.destroy()])
        new_game_btn.grid(row=1)
        no_btn = Button(popup, text="No", command=popup.destroy)
        no_btn.grid(row=4)


if __name__ == "__main__":

    root = Tk()
    sudoku = SudokuGUI(root)
    root.mainloop()
