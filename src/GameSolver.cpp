
#include "GameSolver.h"
#include "Game.h"

void *Game_new(double **t_A, int t_m, int t_n)
{
	return new Game(t_A, t_m, t_n);
}

void Game_delete(void *__this__)
{
	delete static_cast<Game *>(__this__);
}

void Game_solve(void *__this__)
{
	static_cast<Game *>(__this__)->solve();
}

void Game_optstrat(void *__this__, bool t_player, double *r_weights)
{
	static_cast<Game *>(__this__)->optstrat(t_player, r_weights);
}

double Game_value(void *__this__, bool t_player)
{
	return static_cast<Game *>(__this__)->value(t_player);
}
