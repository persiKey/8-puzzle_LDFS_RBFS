#pragma once
#include "General.h"

class State
{
	friend Result RecursiveLDFS(info& i);
	friend int h(State& s);
	friend Result RBSF(info& info, int limit, int* prev_best);

public:
	static constexpr int TOKEN_COUNT = 9;

	enum class Move
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

private:
	Move Moves[4];
	int moves_avail;

	int empty_pos;
	char field[TOKEN_COUNT];

	void CalcMovesAvail();
	bool IsSolvable();
public:
	State();
	State(const State&) = default;
	~State() = default;
	bool operator==(const State& A) const;

	void PrintState();
	void PrintMovesAvail();
	void EditState();

	bool IsFinal();
	void DoMove(Move m);
};

