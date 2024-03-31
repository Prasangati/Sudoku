/*
File Title: SodukuSolver.hpp
Author: Prasanga Tiwari
Description: Declares the SodokuSolver class and provides the helper functions which are implemented later on
Date: Created April 28
*/

#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
/**
  @post:  the default constructor initializes an emtpy board, that is, a board filled with zeros (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable. 
*/
  SudokuSolver(); 

  /**

  @param: input file to read
  @post:  The input files consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board. Empty squares contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not.
    */
  SudokuSolver(std::string input_file); //parameterized constructor


  /**
     @return true if sudoku is solved
    */
  bool isPuzzleSolvable() const; 


  /**
     @post records the puzzle as being solvable */
  void setSolvable();

/**
  @param: 2D pointer array representing the puzzle
  @post:  sets the  2D pointer array representing the puzzle to the value of the parameter 
    */
  void setPuzzleNumbers(int **puzzle);

/**
  @return: returns a Location object with the coordinates of the first 0 found in the 2D pointer array
    */
  Sudoku::Location returnNextEmpty();


  /**
  @param: int value, between 1-9, including 1 and 9
  @param: location, which is given by struct called "Location", part of the class
  @return:  returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location 
            in the 2D array without breaking the rules of sudoku. returns false if placing value at location is not a legal move
    */
  bool checkLegalValue(int value, Sudoku::Location location);


  /** @return: displays the puzzle
  */
  void display(); 



 /**
     @return the 2D pointer array representing the puzzle */
  int **getPuzzleNumbers();

//Helper function
/**
  @post: Recursive helper function for solving the Sudoku puzzle using the backtracking algorithm.
  @return: Returns true if the current configuration of the Sudoku puzzle leads to a solution, 
           false if the puzzle cannot be solved from the current configuration.
*/
  bool solution();




private:


  int **board_;  //2D pointer array representing the Sudoku puzzle board
  int size_; //the size of the Sudoku puzzle, set to 9
  bool solvable_; //bool representing if the puzzle is solvable or not



};

#endif
