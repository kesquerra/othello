#include "MinimaxPlayer.h"

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you
	stack<BoardState*> stack;
	char cur_player = get_symbol();
	BoardState* root = new BoardState(*b, cur_player);
	stack.push(root);
	BoardState* cur_state = NULL;
	while (!stack.empty()) {
		cur_state = stack.top();
		stack.pop();
		vector<BoardState*> children = cur_state->get_next_states(cur_player);
		for (int i=0; i<children.size(); i++) {
			stack.push(children[i]);
		}
		cur_player = toggle_player(cur_player);
	}
	BoardState* best_state = get_next_best_state(root);
	col = best_state->move[0];
	row = best_state->move[1];
}

BoardState* MinimaxPlayer::get_next_best_state(BoardState* root) {
	int idx, val = INT_MIN;
	for (int i=0; i<root->children.size(); i++) {
		int new_val = minimax(root->children[i], false);
		if (new_val > val) {
			val = new_val;
			idx = i;
		}
	}
	cout << val << endl;
	return root->children[idx];
}

char MinimaxPlayer::toggle_player(char player) {
	if (player == 'X') {
		return 'O';
	} else {
		return 'X';
	}
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}

int MinimaxPlayer::minimax(BoardState* state, bool max) {
    if (state->is_terminal(get_symbol())) {
        return state->minimax;
    } else {
        if (max) {
            int val = INT_MIN;
            for (int i=0; i<state->children.size(); i++) {
                int new_val = minimax(state->children[i], max + 1 % 2);
                if (new_val > val) {
                    val = new_val;
                }
            }
            return val;
        } else {
            int val = INT_MAX;
            for (int i=0; i<state->children.size(); i++) {
                int new_val = minimax(state->children[i], max + 1 % 2);
                if (new_val < val) {
                    val = new_val;
                }
            }
            return val;
        }
    }
}
