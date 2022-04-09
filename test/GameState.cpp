//
//  GameState.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include "globals.h"
#include "GameState.h"

// ECE244 Student: add you code below

// initializing the game state to it's base case and setting the baord to blank
GameState::GameState() 
{
	this->selectedRow = 0;
	this->selectedColumn = 0;
	this->moveValid = true;
	this->gameOver = false;
	this->winCode = 0;
	this->turn = true;

	for (int i = 0; i < boardSize; i++) 
	{
		for (int j = 0; j < boardSize; j++) 
		{
			this->gameBoard[i][j] = Empty;
		}
	}
}

// Getters/Setters for selected row and selected column

int GameState::get_selectedRow() 
{
	return this->selectedRow;
}

int GameState::get_selectedColumn() 
{
	return this->selectedColumn;
}

void GameState::set_selectedColumn(int value) 
{
	if ((value >= 0) && (value < boardSize)) 
	{
		this->selectedColumn = value;
	}
}

void GameState::set_selectedRow(int value) 
{
	if ((value >= 0) && (value < boardSize))
	{
		this->selectedRow = value;
	}
}

// Getter/Setter for move valid

bool GameState::get_moveValid() 
{
	return this->moveValid;
}

void GameState::set_moveValid(bool value) 
{
	this->moveValid = value;
}

//Getter/Setter for game over

bool GameState::get_gameOver()
{
	return this->gameOver;
}

void GameState::set_gameOver(bool value)
{
	this->gameOver = value;
}

//Getter/Setter for wincode

int GameState::get_winCode() 
{
	return this->winCode;
}

void GameState::set_winCode(int value) 
{
	if ((value >= 0) && (value <= 8)) 
	{
		this->winCode = value;
	}
}

//Getter/Setter for turn

bool GameState::get_turn()
{
	return this->turn;
}

void GameState::set_turn(bool value)
{
	this->turn = value;
}

//Getter for a position of the gameboard

int GameState::get_gameBoard(int row, int col) 
{
	return this->gameBoard[row][col];
}

//Setter for a given position of the game board

void GameState::set_gameBoard(int row, int col, int value) 
{
	if ((row >= 0) && (row < boardSize)) 
	{
		if ((col >= 0) && (col < boardSize)) 
		{
			this->gameBoard[row][col] = value;
		}
	}
}