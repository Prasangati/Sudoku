/*
File Title: SodukuSolver.cpp
Author: Prasanga Tiwari
Description: implements the SodokuSolver class and solves a sodoku puzzle using a recursive backtracking allgorith. It 
explores soluions via a decision tree
*/


#include "SudokuSolver.hpp"

/**
  @post:  the default constructor initializes an emtpy board, that is, a board filled with zeros (an array of 9 arrays, each filled with 9 zeros). This board will be marked unsolvable. 
*/
SudokuSolver::SudokuSolver() //Default Constructor
{
    size_ = 9;
    board_ = new int *[size_];
    for (int i = 0; i < size_; i++)
    {
        board_[i] = new int[size_];
        for (int j = 0; j < size_; j++)
        {
            board_[i][j] = 0;
        }
    }
    solvable_ = false;
}

/**

  @param: input file to read
  @post:  The input files consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, corresponding to a sudoku board. Empty squares contain the digit 0. After reading the puzzle, the constructor tries to solve it and records whether the puzzle has a solution or not.
    */
SudokuSolver::SudokuSolver(std::string input_file) // Parameterized constructor
{
    size_ = 9;
    board_ = new int *[size_];
    for (int row = 0; row < size_; row++)               //the board is filled with zero before anything is put here
    {
        board_[row] = new int[size_];                   
        for (int col = 0; col < size_; col++)
        {
            board_[row][col] = 0;
        }
    }

    std::ifstream file_input(input_file);                  //just in case the file is not detected
    if (file_input.fail())
    {
        std::cerr << "Error. File can not be opened.";
        exit(1);
    }

    std::string line;
    int current_row = 0;

    while (std::getline(file_input, line))
    {
        int current_col = 0;
        std::stringstream line_stream(line);
        std::string cell_value;

        while (std::getline(line_stream, cell_value, ','))
        {
            board_[current_row][current_col] = std::stoi(cell_value);
            current_col++;
        }
        current_row++;
    }

    solvable_ = solution();
}


/**
    @return true if puzzle is solved, false otherwise 
*/
bool SudokuSolver::isPuzzleSolvable() const
{
    return solvable_;
}


/**
     @post records the puzzle as being solvable */

void SudokuSolver::setSolvable()
{
    solvable_ = true;
}


/**
  @post: Recursive helper function for solving the Sudoku puzzle using the backtracking algorithm.
  @return: Returns true if the current configuration of the Sudoku puzzle leads to a solution, 
           false if the puzzle cannot be solved from the current configuration.
*/
bool SudokuSolver::solution()
{
        Sudoku::Location empty_space = returnNextEmpty(); //This line finds the next empty cell in the puzzle grid and stores its location in empty_space.

    if (empty_space.row == -1 && empty_space.col == -1)
    {
        return true; //: If there are no more empty cells, the function returns true, indicating that the puzzle is solved.
    }

    for (int i = 1; i <= size_; i++)
    {
        if (checkLegalValue(i, empty_space))
        {
            board_[empty_space.row][empty_space.col] = i;

            if (solution())
            {
                return true;
            }

            board_[empty_space.row][empty_space.col] = 0;
        }
    }

    return false;
    //After trying all possible values for the current cell and none of them lead to a solution, the function returns false, indicating that the current configuration doesn't lead to a solution.

    //The function will continue trying different combinations of numbers in the cells using backtracking until it either finds a solution or exhausts all possibilities.




}

  /** @return: displays the puzzle
  */
void SudokuSolver::display() 
{
     for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            if (board_[i][j] == 0)
            {
                std::cout << "X ";
            }
            else
            {
                std::cout << board_[i][j] << " ";
            }
            if (j % 3 == 2 && j != size_ - 1)
            {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i % 3 == 2 && i != size_ - 1)
        {
            std::cout << "- - - - - - - - - - - -" << std::endl;
        }
    }
}






/**
    @return the 2D pointer array representing the puzzle 
*/
int **SudokuSolver::getPuzzleNumbers()
{
    return board_;
}

/**
  @param: 2D array pointer representing the puzzle
  @post:  sets the  2D pointer array representing the puzzle to the value of the parameter 
*/
void SudokuSolver::setPuzzleNumbers(int **puzzle)
{
   size_ = 9;
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            board_[i][j] = puzzle[i][j];
        }
    }
}

/**
  @return: returns a Location object with the coordinates of the first 0 found in the 2D pointer array
    */
Sudoku::Location SudokuSolver::returnNextEmpty()
{
    Sudoku::Location location{-1, -1};

    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            if (board_[i][j] == 0)
            {
                location = {i, j};
                return location;
            }
        }
    }
    return location;
}

/**
  /**
  @param: int value, between 1-9, including 1 and 9
  @param: location, which is given by struct called "Location", part of the class
  @return:  returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location 
            in the 2D array without breaking the rules of sudoku. returns false if placing value at location is not a legal move
    */
bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location)
{
     int row = location.row;
    int col = location.col;

    // Check if the value already appears in the same row or column
    for (int i = 0; i < size_; i++)
    {
        if (board_[row][i] == value || board_[i][col] == value)
        {
            return false;
        }
    }

    // Check if the value already appears in the same subgrid
    int subgrid_size = sqrt(size_);
    int subgrid_row = row / subgrid_size;
    int subgrid_col = col / subgrid_size;

    for (int i = subgrid_row * subgrid_size; i < (subgrid_row + 1) * subgrid_size; i++)
    {
        for (int j = subgrid_col * subgrid_size; j < (subgrid_col + 1) * subgrid_size; j++)
        {
            if (board_[i][j] == value)
            {
                return false;
            }
        }
    }

    // If the value can be placed at the location without breaking the rules, return true
    return true;
}





