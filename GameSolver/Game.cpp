#include "pch.h"
#include "Game.h"


Game::Game(std::list<std::string> _X, std::list<std::string> _Y, std::list<std::list<double>> _A)
{
	m_max = m = _X.size();
	X = new Action[m];
	int i = 0;
	for (std::list<std::string>::iterator it = _X.begin(); it != _X.end(); ++it) {
		X[i++] = Action(*it, 0, true);
	}

	n_max = n = _Y.size();
	Y = new Action[n];
	int j = 0;
	for (std::list<std::string>::iterator it = _Y.begin(); it != _Y.end(); ++it) {
		Y[j++] = Action(*it, 0, false);
	}
	
	std::list<double> first_row = _A.front();
	value_offset = first_row.front();
	for (std::list<double>::iterator it = first_row.begin(); it != first_row.end(); ++it) {
		value_offset = *it < value_offset ? *it : value_offset;
	}
	value_offset -= 1;

	T = new double*[m + 1];
	for (int i = 0; i < m + 1; ++i) {
		T[i] = new double[n + 1];
	}
	i = 0;
	for (std::list<std::list<double>>::iterator row = _A.begin(); row != _A.end(); ++row, ++i) {
		j = 0;
		for (std::list<double>::iterator cell = row->begin(); cell != row->end(); ++cell, ++j) {
			T[i][j] = *cell - value_offset;
		}
	}
	for (int i = 0; i < m; ++i) {
		T[i][n] = 1;
	}
	for (int j = 0; j < n; ++j) {
		T[m][j] = -1;
	}
	T[m][n] = 0;

	std::cout << "Payoff matrix initialized: " << m_max << " row(s), " << n_max << " column(s)" << std::endl;
}


Game::~Game()
{
	delete[] T;
	delete[] X;
	delete[] Y;
}

void Game::print()
{
	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			std::cout << T[i][j] << ',';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

int Game::compare_rows(int r1, int r2)
{
	bool r1_dominated = true, r2_dominated = true;
	for (int c = 0; c < n; ++c) {
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
	for (int r = 0; r < m; ++r) {
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
	for (int i = r; i < m; ++i) {
		T[i] = T[i + 1];
	}
	for (int i = r; i < m - 1; ++i) {
		X[i] = X[i + 1];
	}
	--m;
}

void Game::remove_column(int c)
{
	for (int i = 0; i < m + 1; i++) {
		for (int j = c; j < n; j++) {
			T[i][j] = T[i][j + 1];
		}
	}
	for (int j = c; j < n - 1; j++) {
		Y[j] = Y[j + 1];
	}
	--n;
}

bool Game::eliminate_dominated_rows()
{
	bool dominated = false;
	int r1 = 0, r2 = 1, cmp;
	while (r1 < m - 1) {
		cmp = compare_rows(r1, r2);
		if (cmp == -1) {
			remove_row(r1);
			r2 = r1 + 1;
			dominated = true;
		} else if (cmp == 1) {
			remove_row(r2);
			dominated = true;
		} else {
			++r2;
		}
		if (r2 == m) {
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
	while (c1 < n - 1) {
		cmp = compare_columns(c1, c2);
		if (cmp == -1) {
			remove_column(c1);
			c2 = c1 + 1;
			dominated = true;
		} else if (cmp == 1) {
			remove_column(c2);
			dominated = true;
		} else {
			++c2;
		}
		if (c2 == n) {
			++c1;
			c2 = c1 + 1;
		}
	}
	return dominated;
}

void Game::solve()
{
	while (eliminate_dominated_rows() || eliminate_dominated_columns()) {
	}
	std::cout << "Eliminated " << m_max - m << " row(s), " << n_max - n << " column(s)" << std::endl;

	std::cout << "Solving..." << std::endl;

	int i, j, p, q;
	double ratio, min_positive_ratio;
	Action temp;
	while (true) {
		// 1. Pick a pivot (p, q)
		q = -1;
		for (j = 0; j < n; ++j) {
			if (T[m][j] < 0) {
				q = j;
				break;
			}
		}
		if (q < 0) {
			break;
		}
		min_positive_ratio = -1;
		for (i = 0; i < m; ++i) {
			if (T[i][q] <= 0)
				continue;
			ratio = T[i][n] / T[i][q];
			if (0 < ratio && ratio < min_positive_ratio || min_positive_ratio < 0) {
				p = i;
				min_positive_ratio = ratio;
			}
		}

		// 2. Pivoting
		for (i = 0; i < p; ++i) {
			for (j = 0; j < q; ++j) {
				T[i][j] -= T[p][j] * T[i][q] / T[p][q];
			}
			for (j = q + 1; j < n + 1; ++j) {
				T[i][j] -= T[p][j] * T[i][q] / T[p][q];
			}
		}
		for (i = p + 1; i < m + 1; ++i) {
			for (j = 0; j < q; ++j) {
				T[i][j] -= T[p][j] * T[i][q] / T[p][q];
			}
			for (j = q + 1; j < n + 1; ++j) {
				T[i][j] -= T[p][j] * T[i][q] / T[p][q];
			}
		}

		for (i = 0; i < p; ++i) {
			T[i][q] /= -T[p][q];
		}
		for (i = p + 1; i < m + 1; ++i) {
			T[i][q] /= -T[p][q];
		}

		for (j = 0; j < q; ++j) {
			T[p][j] /= T[p][q];
		}
		for (j = q + 1; j < n + 1; ++j) {
			T[p][j] /= T[p][q];
		}

		T[p][q] = 1 / T[p][q];

		// 3. Exchange pivot row and column actions
		temp = X[p];
		X[p] = Y[q];
		Y[q] = temp;
	}
}

std::list<Action> Game::get_strategy(bool origin)
{
	std::list<Action> strategy = std::list<Action>();
	for (int i = 0; i < m; ++i) {
		if (!origin && !X[i].origin)
			strategy.push_back(Action(X[i].name, T[i][m] / T[m][n], false));
	}
	for (int j = 0; j < n; ++j) {
		if (origin && Y[j].origin)
			strategy.push_back(Action(Y[j].name, T[m][j] / T[m][n], true));
	}
	return strategy;
}

double Game::get_value()
{
	return 1 / T[n][m] + value_offset;
}
