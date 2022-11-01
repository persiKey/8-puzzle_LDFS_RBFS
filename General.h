#pragma once
#include <forward_list>

class State;

enum class Result
{
	SUCCES,
	FAIL,
	LIMIT
};

struct Token
{
	int pos_x;
	int pos_y;
};

struct info
{
	int64_t state_count = 1;
	int64_t dead_end = 0;
	int64_t iterations = 0;
	int states_in_memory = 1;
	int depth = 0;
	std::forward_list<State> history;
};