/*
 * BoardState.h
 *
 *  Created on: Apr 24, 2021
 *      Author: kesquerra
 */

#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "OthelloBoard.h"
#include <vector>
#include <limits.h>
using namespace std;

class BoardState {
    public:
        BoardState(const BoardState& rhs);
        BoardState(const OthelloBoard& b, char player);
        BoardState& operator=(const BoardState& rhs); 
        OthelloBoard* board;
        vector<BoardState*> children;
        bool terminal;
        int minimax;
        char turn;
        int move[2];
        vector<BoardState*> get_next_states(char player);
        void set_move(int col, int row, char player);
        int evaluate_state(char player);
        char get_opponent(char player);
        bool has_children();
        bool is_terminal(char player);
        bool is_winning(char player);
        bool is_a_tie(char player);
        void set_minimax(char player);

};

#endif