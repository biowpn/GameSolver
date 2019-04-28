

#include "GameSolver.h"
#include "Game.h"


void* Game_new(double** t_A, int t_m, int t_n)
{
	return new Game(t_A, t_m, t_n);
}

	
void Game_delete(void* __this__)
{
	delete static_cast<Game*>(__this__);
}

	
void Game_solve(void* __this__)
{
	static_cast<Game*>(__this__)->solve();
}

	
double* Game_get_solution(void* __this__, bool t_player)
{
	double* r_weights;
	static_cast<Game*>(__this__)->get_solution(t_player, r_weights);
	return r_weights;
}

	
double Game_get_value(void* __this__, bool t_player)
{
	return static_cast<Game*>(__this__)->get_value(t_player);
}


void delete_double_array(double* t_arr)
{
	if (t_arr)
	{
		delete[] t_arr;
	}
}









