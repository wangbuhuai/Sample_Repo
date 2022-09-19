// Created by Dayu Wang (dwang@stchas.edu) on 2020-05-01

// Last updated by Dayu Wang (dwang@stchas.edu) on 2022-04-25


#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>

using std::istream;
using std::ostream;

/** A 9-by-9 Sudoku puzzle */
class Sudoku {
public:
    // Constructors
    Sudoku();  // Default constructor
    Sudoku(const Sudoku&);  // Copy constructor

    // Destructor
    ~Sudoku();

    // Operator
    const Sudoku& operator = (const Sudoku&);  // Deep-copy assignment operator

    // Class-member functions
    void load_data(istream&);  // Reads the puzzle from an input stream.
    void print_solution(ostream&) const;  // Writes the solution to an output stream.
    void solve();  // Wrapper function

private:
    // Data fields
    char** board;  // A 9-by-9 grid to store the puzzle
    static const char BLANK;  // Character to represent a blank cell
    bool solved;  // Indicates whether the puzzle is solved.

    // Class-member functions
    bool in_same_row(size_t, char) const;  // Tests whether a digit already appears in a row.
    bool in_same_col(size_t, char) const;  // Tests whether a digit already appears in a column.
    bool in_same_grid(size_t, size_t, char) const;  // Tests whether a digit already appears in the 3-by-3 grid.
    size_t next_row_index(size_t, size_t) const;  // Finds the row index of the next cell (row-major order).
    size_t next_col_index(size_t, size_t) const;  // Finds the column index of the next cell (row-major order).
    void solve(size_t, size_t);  // Solves the puzzle starting from a specific cell.
};

#endif