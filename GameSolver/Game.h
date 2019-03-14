#pragma once

#include <list>
#include <string>
#include <iostream>

struct Action {
	std::string name;
	double probability;
	bool origin; // true for player I, false for Player II
	Action(std::string _name = "", double _probability = 0, bool _origin = true) {
		this->name = _name;
		this->probability = _probability;
		this->origin = _origin;
	}
};


class Game
{
public:
	Game(std::list<std::string>, std::list<std::string>, std::list<std::list<double>>);
	~Game();

	void print();

	int compare_rows(int, int);
	int compare_columns(int, int);

	void remove_row(int);
	void remove_column(int);
	bool eliminate_dominated_rows();
	bool eliminate_dominated_columns();

	void solve();
	std::list<Action> get_strategy(bool);
	double get_value();

private:
	int m; // Size of strategy space of player I. Current size of X.
	int m_max; // Original size of X.
	int n; // Size of strategy space of player II. Current size of Y.
	int n_max; // Original size of Y.

	Action* X;
	Action* Y;
	double** T; // Tableu

	double value_offset;
};

