
#ifndef _GAME_SOLVER_
#define _GAME_SOLVER_


extern "C"
{
	
	void* Game_new(double**, int, int);
	
	void Game_delete(void*);
	
	void Game_solve(void*);
	
	double* Game_get_solution(void*, bool);
	
	double Game_get_value(void*, bool);
	
	void delete_double_array(double*);
	
}



#endif