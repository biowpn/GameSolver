
#ifndef _GAME_SOLVER_
#define _GAME_SOLVER_


extern "C"
{
	
	void* Game_new(double**, int, int);
	
	void Game_delete(void*);
	
	void Game_solve(void*);
	
	void Game_optstrat(void*, bool, double*);
	
	double Game_value(void*, bool);

	
}



#endif