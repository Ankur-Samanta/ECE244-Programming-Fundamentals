//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

void playMove(GameState& game_state) {

    //declaring helper variables

    bool moveWasMade = false;
    bool win = false;
    int row = game_state.get_selectedRow();
    int col = game_state.get_selectedColumn();
    int token;
    bool currentPlayer = game_state.get_turn();

    token = currentPlayer ? 1 : -1;

    //move making

    if (game_state.get_gameBoard(row, col) != Empty)
    {
        game_state.set_moveValid(false);

    }
    else {

        moveWasMade = true;
        game_state.set_moveValid(true);
        game_state.set_gameBoard(row, col, token);
    }

    //win checking ONLY IF a move was made
    if (moveWasMade) 
    {
    
        //row checking
        for (int i = 0; i < boardSize; i++) 
        {
            bool gameWon = true;
            int standard = game_state.get_gameBoard(i, 0);

            for (int j = 0; j < boardSize; j++)
            {
                if (standard == 0) 
                {
                    gameWon = false;
                    break;
                } else {
                    if (game_state.get_gameBoard(i, j) != standard) 
                    {
                        gameWon = false;
                        break;
                    }
                }
            }

            if (gameWon) 
            {
                game_state.set_winCode(i + 1);
                game_state.set_gameOver(true);
                win = true;
                break;
            }
        }

        //col checking
        for (int i = 0; i < boardSize; i++)
        {
            bool gameWon = true;
            int standard = game_state.get_gameBoard(0, i);

            for (int j = 0; j < boardSize; j++)
            {
                if (standard == 0)
                {
                    gameWon = false;
                    break;
                }
                else {
                    if (game_state.get_gameBoard(j, i) != standard)
                    {
                        gameWon = false;
                        break;
                    }
                }
            }

            if (gameWon)
            {
                game_state.set_winCode(i + 4);
                game_state.set_gameOver(true);
                win = true;
                break;
            }
        }

        //diag checking
        bool gameWon = true;
        int standard = game_state.get_gameBoard(0, 0);

        for (int i = 0; i < boardSize; i++)
        {
            if (standard == 0)
            {
                gameWon = false;
                break;
            }
            else {

                if (game_state.get_gameBoard(i, i) != standard)
                {
                    gameWon = false;
                    break;
                }
            }
        }

        if (gameWon)
        {
            game_state.set_winCode(7);
            game_state.set_gameOver(true);
            win = true;
        }

        if (!gameWon) {
            gameWon = true;
            standard = game_state.get_gameBoard(2, 0);

            for (int i = 2; i > -1; i--)
            {
                if (standard == 0)
                {
                    gameWon = false;
                    break;
                }
                else {
                    if (game_state.get_gameBoard(i, -1 * i + 2) != standard)
                    {
                        gameWon = false;
                        break;
                    }
                }
            }

            if (gameWon)
            {
                game_state.set_winCode(8);
                game_state.set_gameOver(true);
                win = true;
            }
        }

        //tie game checking
        if (!win)
        {
            bool tieGame = true;

            for (int i = 0; i < boardSize; i++)
            {
                for (int j = 0; j < boardSize; j++)
                {
                    if (game_state.get_gameBoard(i, j) == Empty)
                    {
                        tieGame = false;
                    }
                }
            }

            if (tieGame)
            {
                game_state.set_winCode(0);
                game_state.set_gameOver(true);
            }
        }

        //switching turn only if a move was made
        bool turn = currentPlayer ? false : true;
        game_state.set_turn(turn);
    }
}

