
#ifndef _GAME_
#define _GAME_


struct Action {
	int index;
	bool player; // true for Player I, false for Player II
	
	Action(int t_index = 0, bool t_player = true)
	{
		index = t_index;
		player = t_player;
	}
};


class Game
{
public:
	// Passed in payoff matrix as a m by n 2D dynamic array
	Game(double**, int, int);
	~Game();
	
	// Solve the game
	void solve();
	
	// Get the optimal (mixed) strategy for a player.
	// true for Player I and false for Player II.
	// A new dynamic array will be allocated matching the row/column size of the payoff matrix
	void get_solution(bool, double*&);
	
	// Get the value for a player.
	// true for Player I and false for Player II.
	double get_value(bool);

protected:
	int m; // Size of strategy space of player I. Current size of X.
	int m_max; // Original size of X.
	int n; // Size of strategy space of player II. Current size of Y.
	int n_max; // Original size of Y.

	Action* X;
	Action* Y;
	double** T; // Tableu

	double value_offset;
	
	int compare_rows(int, int);
	int compare_columns(int, int);

	void remove_row(int);
	void remove_column(int);
	bool eliminate_dominated_rows();
	bool eliminate_dominated_columns();
};

#endif