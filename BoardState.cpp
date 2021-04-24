/*
 * BoardState.h
 *
 *  Created on: Apr 24, 2021
 *      Author: kesquerra
 */

#include "BoardState.h"

BoardState::BoardState(const BoardState& rhs) {
    board = new OthelloBoard(*rhs.board);
    turn = get_opponent(rhs.turn);
    move[0] = rhs.move[0];
    move[1] = rhs.move[1];
    terminal = is_terminal(turn);
    minimax = evaluate_state(turn);
}

BoardState::BoardState(const OthelloBoard& b, char player) {
    board = new OthelloBoard(b);
    turn = player;
    move[0] = -1; 
    move[1] = -1;
    terminal = is_terminal(turn);
    minimax = evaluate_state(turn);
}

BoardState& BoardState::operator=(const BoardState& rhs) {
	if (this == &rhs) {
		return *this;
	} else {
		board = new OthelloBoard(*rhs.board);
        turn = rhs.turn;
		move[0] = rhs.move[0];
		move[1] = rhs.move[1];
        minimax = evaluate_state(turn);
		return *this;
	}
}

void BoardState::set_move(int col, int row, char player) {
    board->play_move(col, row, player);
    move[0] = col;
    move[1] = row;
    turn = get_opponent(player);
    terminal = is_terminal(player);
    minimax = evaluate_state(player);
}

vector<BoardState*> BoardState::get_next_states(char player) {
    vector<BoardState*> next_states;
	if (board->has_legal_moves_remaining(player)) {
		for (int i=0; i<board->get_num_cols(); i++) {
			for (int j=0; j<board->get_num_rows(); j++) {
				if (board->is_legal_move(i, j, player)) {
					BoardState* bs = new BoardState(*this);
					bs->set_move(i, j, player);
					next_states.push_back(bs);
                    children.push_back(bs);
				}
			}
		}
	}
	return next_states;
}

char BoardState::get_opponent(char player) {
    if (player == 'X') {
        return 'O';
    } else {
        return 'X';
    }
}

bool BoardState::is_winning(char player) {
    return board->count_score(player) > board->count_score(get_opponent(player));
}

bool BoardState::is_a_tie(char player) {
    return board->count_score(player) == board->count_score(get_opponent(player));
}

bool BoardState::is_terminal(char player) {
    int score_diff = board->count_score(player) - board->count_score(get_opponent(player));
    int score_total = board->count_score(player) + board->count_score(get_opponent(player));
    int max_points = board->get_num_cols() * board->get_num_cols();
    if (!board->has_legal_moves_remaining(player) || (score_total == max_points)) {
        return true;
    }
    return false;
}

int BoardState::evaluate_state(char player) {
    int score_diff = board->count_score(player) - board->count_score(get_opponent(player));
    int bonus = 0;
    int corners[2] = {0,3};
    for (int i=0; i<2; i++) {
        if (board->get_cell(corners[i], corners[i]) == player) {
            bonus += 10;
        }
        if (board->get_cell(corners[i], corners[(i+1)%2]) == player) {
            bonus += 10;
        }  
    }
    if (is_terminal(player)) {
        if (is_a_tie(player)) {
            return 0;
        }
        if (is_winning(player)) {
            return 100 + score_diff + bonus;
        } else {
            return -100 + score_diff + bonus;
        }
    } else {
        return score_diff + bonus;
    }
}

void BoardState::set_minimax(char player) {
    minimax = evaluate_state(player);
}

bool BoardState::has_children() {
    if (children.size() > 0) {
        return true;
    }
    return false;
}

