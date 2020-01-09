
#include "Game.h"

const double EPSILON = 0.000000000001;

Game::Game(double **t_A, int t_m, int t_n)
{
	init(t_A, t_m, t_n);
}

void Game::init(double **t_A, int t_m, int t_n)
{
	m_max = m = t_m;
	n_max = n = t_n;
	T = new double *[m_max + 1];
	for (int i = 0; i < m; ++i)
	{
		T[i] = new double[n_max + 1];
		for (int j = 0; j < n; ++j)
		{
			T[i][j] = t_A[i][j];
		}
		T[i][n] = 1;
	}
	T[m] = new double[n_max + 1];
	for (int j = 0; j < n; ++j)
	{
		T[m][j] = -1;
	}
	T[m][n] = 0;

	X = new Action[m];
	for (int i = 0; i < m; ++i)
	{
		X[i] = Action(i, true);
	}
	Y = new Action[n];
	for (int j = 0; j < n; ++j)
	{
		Y[j] = Action(j, false);
	}

	value_offset = T[0][0];
	for (int j = 1; j < n; ++j)
	{
		if (T[0][j] < value_offset)
		{
			value_offset = T[0][j];
		}
	}
	value_offset -= 1;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			T[i][j] -= value_offset;
		}
	}
}

Game::~Game()
{
	for (int i = 0; i < m + 1; ++i)
	{
		delete[] T[i];
	}
	delete[] T;

	delete[] X;
	delete[] Y;
}

void Game::solve()
{
	while (eliminate_dominated_rows() || eliminate_dominated_columns())
		;

	int i, j, p, q;
	double ratio;
	Action temp;
	while (true)
	{
		// 1. Pick a pivot (p, q)
		q = -1;
		for (j = 0; j < n; ++j)
		{
			if (T[m][j] < 0)
			{
				q = j;
				break;
			}
		}
		if (q < 0)
		{
			break;
		}
		ratio = 0;
		for (i = 0; i < m; ++i)
		{
			if (T[i][q] > EPSILON)
			{
				if (T[i][n] < 0)
				{
					p = i;
					break;
				}
				else if (T[i][q] > T[i][n] * ratio)
				{
					p = i;
					ratio = T[i][q] / T[i][n];
				}
			}
		}

		// 2. Pivoting
		for (i = 0; i < p; ++i)
		{
			for (j = 0; j < q; ++j)
			{
				T[i][j] -= T[p][j] * T[i][q] / T[p][q];
			}
			for (j = q + 1; j < n + 1; ++j)
			{
				T[i][j] -= T[p][j] * T[i][q] / T[p][q];
			}
		}
		for (i = p + 1; i < m + 1; ++i)
		{
			for (j = 0; j < q; ++j)
			{
				T[i][j] -= T[p][j] * T[i][q] / T[p][q];
			}
			for (j = q + 1; j < n + 1; ++j)
			{
				T[i][j] -= T[p][j] * T[i][q] / T[p][q];
			}
		}

		for (i = 0; i < p; ++i)
		{
			T[i][q] /= -T[p][q];
		}
		for (i = p + 1; i < m + 1; ++i)
		{
			T[i][q] /= -T[p][q];
		}

		for (j = 0; j < q; ++j)
		{
			T[p][j] /= T[p][q];
		}
		for (j = q + 1; j < n + 1; ++j)
		{
			T[p][j] /= T[p][q];
		}

		T[p][q] = 1 / T[p][q];

		// 3. Exchange pivot row and column actions
		temp = X[p];
		X[p] = Y[q];
		Y[q] = temp;
	}
}

void Game::optstrat(bool t_player, double *r_weights)
{
	if (t_player) // Player I
	{
		for (int i = 0; i < m_max; ++i)
		{
			r_weights[i] = 0;
		}
		for (int j = 0; j < n; ++j)
		{
			if (Y[j].player)
			{
				r_weights[Y[j].index] = T[m][j] / T[m][n];
			}
		}
	}
	else // Player II
	{
		for (int j = 0; j < n_max; ++j)
		{
			r_weights[j] = 0;
		}
		for (int i = 0; i < m; ++i)
		{
			if (!X[i].player)
			{
				r_weights[X[i].index] = T[i][n] / T[m][n];
			}
		}
	}
}

double Game::value(bool t_player)
{
	return t_player ? (1 / T[n][m] + value_offset) : -value(true);
}

int Game::compare_rows(int r1, int r2)
{
	bool r1_dominated = true, r2_dominated = true;
	for (int c = 0; c < n; ++c)
	{
		if (T[r1][c] > T[r2][c])
			r1_dominated = false;
		else if (T[r1][c] < T[r2][c])
			r2_dominated = false;
		if (!r1_dominated && !r2_dominated)
			return 0;
	}
	return r1_dominated ? -1 : 1;
}

int Game::compare_columns(int c1, int c2)
{
	bool c1_dominated = true, c2_dominated = true;
	for (int r = 0; r < m; ++r)
	{
		if (T[r][c1] < T[r][c2])
			c1_dominated = false;
		else if (T[r][c1] > T[r][c2])
			c2_dominated = false;
		if (!c1_dominated && !c2_dominated)
			return 0;
	}
	return c1_dominated ? -1 : 1;
}

void Game::remove_row(int r)
{
	delete T[r];
	for (int i = r; i < m; ++i)
	{
		T[i] = T[i + 1];
	}
	for (int i = r; i < m - 1; ++i)
	{
		X[i] = X[i + 1];
	}
	--m;
}

void Game::remove_column(int c)
{
	for (int i = 0; i < m + 1; i++)
	{
		for (int j = c; j < n; j++)
		{
			T[i][j] = T[i][j + 1];
		}
	}
	for (int j = c; j < n - 1; j++)
	{
		Y[j] = Y[j + 1];
	}
	--n;
}

bool Game::eliminate_dominated_rows()
{
	bool dominated = false;
	int r1 = 0, r2 = 1, cmp;
	while (r1 < m - 1)
	{
		cmp = compare_rows(r1, r2);
		if (cmp == -1)
		{
			remove_row(r1);
			r2 = r1 + 1;
			dominated = true;
		}
		else if (cmp == 1)
		{
			remove_row(r2);
			dominated = true;
		}
		else
		{
			++r2;
		}
		if (r2 == m)
		{
			++r1;
			r2 = r1 + 1;
		}
	}
	return dominated;
}

bool Game::eliminate_dominated_columns()
{
	bool dominated = false;
	int c1 = 0, c2 = 1, cmp;
	while (c1 < n - 1)
	{
		cmp = compare_columns(c1, c2);
		if (cmp == -1)
		{
			remove_column(c1);
			c2 = c1 + 1;
			dominated = true;
		}
		else if (cmp == 1)
		{
			remove_column(c2);
			dominated = true;
		}
		else
		{
			++c2;
		}
		if (c2 == n)
		{
			++c1;
			c2 = c1 + 1;
		}
	}
	return dominated;
}
