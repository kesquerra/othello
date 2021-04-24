/*
 * MinimaxPlayer.h
 *
 *  Created on: Apr 24, 2021
 *      Author: kesquerra
 */

#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "OthelloBoard.h"
#include "BoardState.h"
#include "Player.h"
#include <vector>
#include <stack>
#include <cstdlib> 
#include <iostream>
using namespace std;

/**
 * This class represents an AI player that uses the Minimax algorithm to play the game
 * intelligently.
 */
class MinimaxPlayer : public Player {
public:

	/**
	 * @param symb This is the symbol for the minimax player's pieces
	 */
	MinimaxPlayer(char symb);

	/**
	 * Destructor
	 */
	virtual ~MinimaxPlayer();

	/**
	 * @param b The board object for the current state of the board
	 * @param col Holds the return value for the column of the move
	 * @param row Holds the return value for the row of the move
	 */
    void get_move(OthelloBoard* b, int& col, int& row);
	vector<OthelloBoard*> get_next_states(OthelloBoard* b, char player);
	char toggle_player(char player);
	BoardState* get_next_best_state(BoardState* state);
	int minimax(BoardState* state);

    /**
     * @return A copy of the MinimaxPlayer object
     * This is a virtual copy constructor
     */
    MinimaxPlayer* clone();

private:

};


#endif
