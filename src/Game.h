
#ifndef _GAME_H_
#define _GAME_H_

struct Action
{
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
	/**
	 * Create a new 2-player game.
	 * 
	 * @param matrix the payoff matrix
	 * @param row number of rows
	 * @param col number of columns
	 */
	Game(double **matrix, int row, int col);

	~Game();

	/**
	 * Solve the game
	 */
	void solve();

	/**
	 * Get the optimal (mixed) strategy for a player.
	 * 
	 * @param p1 if true, will get Player I's strategy, otherwise Player II's
	 * @param out buffer to collect the optimal weights
	 */
	void optstrat(bool p1, double *out);

	/**
	 * Get the value of the game for a player.
	 * 
	 * @param p1 if true, will get Player I's value, otherwise Player II's
	 */
	double value(bool);

protected:
	void init(double **, int, int);

	int m;	 // Size of strategy space of player I. Current size of X.
	int m_max; // Original size of X.
	int n;	 // Size of strategy space of player II. Current size of Y.
	int n_max; // Original size of Y.

	Action *X;
	Action *Y;
	double **T; // Tableu

	double value_offset;

	int compare_rows(int, int);
	int compare_columns(int, int);

	void remove_row(int);
	void remove_column(int);
	bool eliminate_dominated_rows();
	bool eliminate_dominated_columns();
};

#endif
