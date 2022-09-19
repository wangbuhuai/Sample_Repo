// Created by Dayu Wang (dwang@stchas.edu) on 2020-05-01

// Last updated by Dayu Wang (dwang@stchas.edu) on 2022-04-25


#include "Sudoku.h"

#include <fstream>
#include <iostream>

using namespace std;

int main() {
    // Open the input file.
    ifstream fin("puzzle.txt");

    // Tests whether the input file was successfully opened.
    if (!fin) {
        cout << "[Error] Nonexistent input file" << endl;
        system("pause");
        return -1;
    }

    // Open the output file.
    ofstream fout("solution.txt");

    Sudoku puzzle;  // Create a Sudoku puzzle.
    puzzle.load_data(fin);  // Load the puzzle from the input file.
    puzzle.solve();  // Solve the puzzle.
    puzzle.print_solution(fout);  // Write the solution to the output file.

    // Close the input and output file.
    fin.close();
    fout.close();

    return 0;
}