// Created by Dayu Wang (dwang@stchas.edu) on 2020-05-01

// Last updated by Dayu Wang (dwang@stchas.edu) on 2022-04-25


#include "Sudoku.h"

#include <string>

using std::endl;

// Static data fields

const char Sudoku::BLANK = '.';

// Constructors

Sudoku::Sudoku() : solved(false) {  // Default constructor
    board = new char* [9];
    for (size_t row = 0; row < 9; row++) { board[row] = new char[9]; }
}

Sudoku::Sudoku(const Sudoku& other) {  // Copy constructor
    board = NULL;
    *this = other;
}

// Destructor

Sudoku::~Sudoku() {
    for (size_t row = 0; row < 9; row++) { delete[] board[row]; }
    delete[] board;
}

// Deep-copy assignment operator

const Sudoku& Sudoku::operator = (const Sudoku& rhs) {
    if (this != &rhs) {
        if (board) {
            for (size_t row = 0; row < 9; row++) { delete[] board[row]; }
            delete[] board;
            board = NULL;
        }
        solved = rhs.solved;
        board = new char* [9];
        for (size_t row = 0; row < 9; row++) {
            board[row] = new char[9];
            for (size_t col = 0; col < 9; col++) { board[row][col] = rhs.board[row][col]; }
        }
    }
    return *this;
}

// Class-member functions

/** Reads the puzzle from an input stream.
    @param in: an input stream to read the puzzle
*/
void Sudoku::load_data(istream& in) {
    char ch;
    for (size_t row = 0; row < 9; row++) {
        for (size_t col = 0; col < 9; col++) {
            in >> ch;
            board[row][col] = ch;
        }
    }
}

/** Tests whether a digit already appears in a row.
    @param row: index of the row to search
    @param digit: digit to test
    @return: {true} if the digit is found in the row; {false} otherwise
*/
bool Sudoku::in_same_row(size_t row, char digit) const {
    for (size_t col = 0; col < 9; col++) {
        if (digit == board[row][col]) { return true; }
    }
    return false;
}

/** Tests whether a digit already appears in a column.
    @param col: index of the column to search
    @param digit: digit to test
    @return: {true} if the digit is found in the column; {false} otherwise
*/
bool Sudoku::in_same_col(size_t col, char digit) const {
    for (size_t row = 0; row < 9; row++) {
        if (digit == board[row][col]) { return true; }
    }
    return false;
}

/** Tests whether a digit already appears in the 3-by-3 grid a cell resides in.
    @param row: row index of the cell
    @param col: column index of the cell
    @param digit: digit to test
    @return: {true} if the digit is found in the grid; {false} otherwise
*/
bool Sudoku::in_same_grid(size_t row, size_t col, char digit) const {
    for (size_t i = row / 3 * 3; i < row / 3 * 3 + 3; i++) {
        for (size_t j = col / 3 * 3; j < col / 3 * 3 + 3; j++) {
            if (board[i][j] == digit) { return true; }
        }
    }
    return false;
}

/** Finds the row index of the next cell in row-major order.
    @param row: row index of the current cell
    @param col: column index of the current cell
    @return: row index of the next cell
*/
size_t Sudoku::next_row_index(size_t row, size_t col) const {
    if (col == 8) { return row + 1; }
    else { return row; }
}

/** Finds the column index of the next cell in row-major order.
    @param row: row index of the current cell
    @param col: column index of the current cell
    @return: column index of the next cell
*/
size_t Sudoku::next_col_index(size_t row, size_t col) const {
    if (col == 8) { return 0; }
    else { return col + 1; }
}

/** Solves the puzzle beginning with some cell.
    @param row: row index of the beginning cell
    @param col: column index of the beginning cell
*/
void Sudoku::solve(size_t row, size_t col) {
    // Base case
    if (row == 9) {
        solved = true;
        return;
    }

    // If the current cell is not blank, then go to the next cell.
    if (board[row][col] != BLANK) { solve(next_row_index(row, col), next_col_index(row, col)); }
    else {  // Current cell is blank.
        for (char digit = '1'; digit <= '9'; digit++) {
            if (in_same_row(row, digit)) { continue; }  // Digit already appears in the same row.
            if (in_same_col(col, digit)) { continue; }  // Digit already appears in the same column.
            if (in_same_grid(row, col, digit)) { continue; }  // Digit already appears in the 3-by-3 grid.

            // Fill the cell with the digit.
            board[row][col] = digit;

            // Go to the next cell and solve the puzzle recursively.
            solve(next_row_index(row, col), next_col_index(row, col));

            // If no solution found, change the cell back to blank and try the next digit.
            if (!solved) { board[row][col] = BLANK; }
        }
    }
}

// Wrapper function
void Sudoku::solve() { solve(0, 0); }

/** Writes the solution to an output stream.
    @param out: an output stream to write the solution
*/
void Sudoku::print_solution(ostream& out) const {
    for (size_t row = 0; row < 9; row++) {
        for (size_t col = 0; col < 9; col++) {
            out << board[row][col];
        }
        out << endl;
    }
}