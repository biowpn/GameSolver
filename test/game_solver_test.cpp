
#include "../src/Game.h"

#include <iostream>


int main()
{
	double** A = new double*[3];
	for (int i = 0; i < 3; ++i)
	{
		A[i] = new double[3];
	}
	A[0][0] = 0;
	A[0][1] = -1;
	A[0][2] = 1;
	A[1][0] = 1;
	A[1][1] = 0;
	A[1][2] = -1;
	A[2][0] = -1;
	A[2][1] = 1;
	A[2][2] = 0;
	
	Game game(A, 3, 3);
	game.solve();
	game.get_value(true);
	game.get_value(false);
	
	int strat_size;
	double* optimal_strat;
	
	game.get_solution(true, optimal_strat, strat_size);
	std::cout << "Player I: " << std::endl;
	for (int i = 0; i < strat_size; ++i)
	{
		std::cout << i << ":" << optimal_strat[i] << std::endl;
	}
	std::cout << std::endl;
	delete[] optimal_strat;
	
	std::cout << "Player II: " << std::endl;
	game.get_solution(false, optimal_strat, strat_size);
	for (int i = 0; i < strat_size; ++i)
	{
		std::cout << i << ":" << optimal_strat[i] << std::endl;
	}
	std::cout << std::endl;
	delete[] optimal_strat;
	
	for (int i = 0; i < 3; ++i)
	{
		delete[] A[i];
	}
	delete[] A;
	
	return 0;
}




