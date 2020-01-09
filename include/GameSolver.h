
#ifndef _GAME_SOLVER_
#define _GAME_SOLVER_

#ifdef __EMSCRIPTEN__
// Forces LLVM to not dead-code-eliminate a function.
#include <emscripten.h>
#define FUNCTION_PREFIX EMSCRIPTEN_KEEPALIVE
#else
#define FUNCTION_PREFIX
#endif

extern "C"
{
	/**
	 * Create a new 2-player game.
	 * 
	 * @param matrix the payoff matrix
	 * @param row number of rows
	 * @param col number of columns
	 * @return pointer to the Game instance
	 */
	void *FUNCTION_PREFIX Game_new(double **matrix, int row, int col);

	/**
	 * Destroy the Game instance.
	 * 
	 * @param __this__ pointer to the Game instance to destroy
	 */
	void FUNCTION_PREFIX Game_delete(void *__this__);

	/**
	 * Solve the game
	 * 
	 * @param __this__ pointer to the Game instance
	 */
	void FUNCTION_PREFIX Game_solve(void *__this__);

	/**
	 * Get the optimal (mixed) strategy for a player.
	 * 
	 * @param __this__ pointer to the Game instance
	 * @param p1 if true, will get Player I's strategy, otherwise Player II's
	 * @param out buffer to collect the optimal weights
	 */
	void FUNCTION_PREFIX Game_optstrat(void *__this__, bool p1, double *out);

	/**
	 * Get the value of the game for a player.
	 * 
	 * @param __this__ pointer to the Game instance
	 * @param p1 if true, will get Player I's value, otherwise Player II's
	 * @return game value of the player
	 */
	double FUNCTION_PREFIX Game_value(void *__this__, bool p1);
}

#endif
