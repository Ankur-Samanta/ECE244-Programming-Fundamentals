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
    //see if the place is occupied or if the place is logically ok
    //if it is, then place the item, switch
    int counter = 0;
    if ((game_state.get_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn()) != Empty) && game_state.get_gameOver() == false) {
        game_state.set_moveValid(false);
        game_state.set_gameOver(false);
        game_state.set_winCode(0);
    }
    else if (game_state.get_gameOver() == false) {
        game_state.set_moveValid(true);
        if (game_state.get_turn() == true) {
            game_state.set_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn(), 1);
            game_state.set_turn(false);
        }
        else if (game_state.get_turn() == false) {
            game_state.set_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn(), -1);
            game_state.set_turn(true);
        }
        //winchecking once move has been made
        game_state.set_winCode(0);
        if ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(1, 1) + game_state.get_gameBoard(2, 2)) == 3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 7) {
                game_state.set_winCode(7);
            }
        }
        else if ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(1, 1) + game_state.get_gameBoard(2, 2)) == -3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 7) {
                game_state.set_winCode(7);
            }
        }
        if ((game_state.get_gameBoard(2, 0) + game_state.get_gameBoard(1, 1) + game_state.get_gameBoard(0, 2)) == 3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 8) {
                game_state.set_winCode(8);
            }    
        }
        else if ((game_state.get_gameBoard(2, 0) + game_state.get_gameBoard(1, 1) + game_state.get_gameBoard(0, 2)) == -3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 8) {
                game_state.set_winCode(8);
            }
        }

        if ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(0, 1) + game_state.get_gameBoard(0, 2)) == 3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 1) {
                game_state.set_winCode(1);
            }
        }
        else if ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(0, 1) + game_state.get_gameBoard(0, 2)) == -3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 1) {
                game_state.set_winCode(1);
            }
        }
        if ((game_state.get_gameBoard(1, 0) + game_state.get_gameBoard(1, 1) + game_state.get_gameBoard(1, 2)) == 3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 2) {
                game_state.set_winCode(2);
            }
        }
        else if ((game_state.get_gameBoard(1, 0) + game_state.get_gameBoard(1, 1) + game_state.get_gameBoard(1, 2)) == -3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 2) {
                game_state.set_winCode(2);
            }
        }
        if ((game_state.get_gameBoard(2, 0) + game_state.get_gameBoard(2, 1) + game_state.get_gameBoard(2, 2)) == 3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 3) {
                game_state.set_winCode(3);
            }
        }
        else if ((game_state.get_gameBoard(2, 0) + game_state.get_gameBoard(2, 1) + game_state.get_gameBoard(2, 2)) == -3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 3) {
                game_state.set_winCode(3);
            }
        }
        
        if ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(1, 0) + game_state.get_gameBoard(2, 0)) == 3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 4) {
                game_state.set_winCode(4);
            }
        }
        else if ((game_state.get_gameBoard(0, 0) + game_state.get_gameBoard(1, 0) + game_state.get_gameBoard(2, 0)) == -3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 4) {
                game_state.set_winCode(4);
            }
        }
        if ((game_state.get_gameBoard(0, 1) + game_state.get_gameBoard(1, 1) + game_state.get_gameBoard(2, 1)) == 3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 5) {
                game_state.set_winCode(5);
            }
        }
        else if ((game_state.get_gameBoard(0, 1) + game_state.get_gameBoard(1, 1) + game_state.get_gameBoard(2, 1)) == -3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 5) {
                game_state.set_winCode(5);
            }
        }
        if ((game_state.get_gameBoard(0, 2) + game_state.get_gameBoard(1, 2) + game_state.get_gameBoard(2, 2)) == 3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 6) {
                game_state.set_winCode(6);
            }
        }
        else if ((game_state.get_gameBoard(0, 2) + game_state.get_gameBoard(1, 2) + game_state.get_gameBoard(2, 2)) == -3) {
            game_state.set_gameOver(true);
            if (game_state.get_winCode() < 6) {
                game_state.set_winCode(6);
            }
        }
    }
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (game_state.get_gameBoard(i, j) != Empty) {
                counter ++;
            }
        }
    }
    
    if (counter == 9 && game_state.get_winCode() == 0) {
        game_state.set_gameOver(true);
        game_state.set_winCode(0);
    }
    
    //gameOver
}

