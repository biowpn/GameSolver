
#include "Game.h"

#include <iostream>

int main()
{
	double **A = new double *[3];
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

	double *optimal_strat = new double[3];

	game.optstrat(true, optimal_strat);
	std::cout << "Player I: " << std::endl;
	for (int i = 0; i < 3; ++i)
	{
		std::cout << i << ":" << optimal_strat[i] << std::endl;
	}
	std::cout << "Value: " << game.value(true) << std::endl;

	std::cout << "Player II: " << std::endl;
	game.optstrat(false, optimal_strat);
	for (int i = 0; i < 3; ++i)
	{
		std::cout << i << ":" << optimal_strat[i] << std::endl;
	}
	std::cout << "Value: " << game.value(false) << std::endl;

	for (int i = 0; i < 3; ++i)
	{
		delete[] A[i];
	}
	delete[] A;
	delete[] optimal_strat;

	return 0;
}
