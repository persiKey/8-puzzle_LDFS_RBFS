#include "SearchAlgs.h"
#include <iostream>
#include "State.h"
#include <algorithm>
#include <map>
#include <vector>

using std::cout;

void PrintResults(Result res, info& inf)
{
	switch (res)
	{
	case Result::FAIL: cout << "Fail\n"; break;
	case Result::SUCCES: cout << "\n\nSucces\n"; break;
	}
	std::vector<State> order(inf.history.begin(), inf.history.end());

	for (auto s = order.rbegin(); s < order.rend(); ++s)
	{
		(*s).PrintState();
	}
	cout << "State count: " << inf.state_count << '\n';
	cout << "States in memory: " << inf.states_in_memory << '\n';
	cout << "Iterations: " << inf.iterations << '\n';
	cout << "Dead ends: " << inf.dead_end << '\n';
	cout << "Depth: " << inf.depth << '\n';
}

void LimitedDFS(State s)
{
	info inf;
	inf.history.push_front(s);
	
	PrintResults(RecursiveLDFS(inf),inf);
}


Result RecursiveLDFS(info& info)
{
	++info.iterations;
	auto& top = info.history.front();
	if (top.IsFinal())
		return Result::SUCCES;
	else if (info.depth == LDFS_DEPTH_LIMIT)
	{
		++info.dead_end;
		return Result::LIMIT;
	}

	for (size_t i = 0; i < top.moves_avail; i++)
	{
		info.history.push_front(top);
		++info.depth;
		++info.state_count;
		++info.states_in_memory;
		info.history.front().DoMove(top.Moves[i]);

		if (RecursiveLDFS(info) != Result::SUCCES)
		{
			info.history.pop_front();
			--info.states_in_memory;
			--info.depth;
		}
		else
			return Result::SUCCES;
	}

	return Result::FAIL;

}

void RecursiveBestFS(State s)
{
	info inf;
	inf.history.push_front(s);

	PrintResults(RBSF(inf, std::numeric_limits<int>::max(), nullptr),inf);
}

int h(State& s)
{
	static std::map<char, Token> TableFin
	{ {'1',{0,0} },
	{'2',{1,0} },
	{'3',{2,0} },
	{'4',{0,1} },
	{'5',{1,1} },
	{'6',{2,1} },
	{'7',{0,2} },
	{'8',{1,2} },
	{' ',{2,2} } };

	auto get_token_pos = [](int linear_pos) {
		Token res;
		res.pos_x = linear_pos % 3;
		res.pos_y = linear_pos / 3;
		return res;
	};
	auto manhatten_lengt = [](const Token cur, const Token fin) -> int {
		return abs(cur.pos_x - fin.pos_x) + abs(cur.pos_y - fin.pos_y);
	};

	int res = 0;

	for (size_t k = 0; k < State::TOKEN_COUNT; k++)
	{
		if (s.field[k] == ' ')
			continue;
		res += manhatten_lengt(get_token_pos(k), TableFin[s.field[k]]);
	}
	return res;
}

Result RBSF(info& info, int limit, int* prev_best)
{
	typedef std::pair<State, int > successor_cost;

	++info.iterations;
	auto& top = info.history.front();

	if (top.IsFinal())
		return Result::SUCCES;
	
	successor_cost succesors[4];
	int s_count = 0;
	for (size_t i = 0; i < top.moves_avail; i++)
	{
		succesors[s_count].first = top;
		succesors[s_count].first.DoMove(top.Moves[i]);
		if (std::find(info.history.begin(), info.history.end(), succesors[s_count].first) != info.history.end())
		{
			continue;
		}
		succesors[s_count].second = h(succesors[s_count].first) + info.depth;
		++s_count;
	}
	info.state_count += s_count;
	info.states_in_memory += s_count;
	if (0 == s_count)
	{
		*prev_best = std::numeric_limits<int>::max();
		++info.dead_end;
		return Result::FAIL;
	}
	if (1 == s_count)
	{
		info.history.push_front(succesors[0].first);
		++info.depth;
		auto res = RBSF(info, limit, prev_best);
		if (res == Result::SUCCES)
			return res;

		--info.depth;
		--info.states_in_memory;
		info.history.pop_front();
		return res;
	}
	while (true)
	{
		std::sort(succesors, succesors + s_count,
			[](const successor_cost A, const successor_cost B)
			{ return A.second < B.second; });

		successor_cost& best = succesors[0];
		if (best.second > limit)
		{
			*prev_best = best.second;
			++info.dead_end;
			info.states_in_memory -= s_count;
			return Result::FAIL;
		}

		info.history.push_front(best.first);
		++info.depth;

		if (RBSF(info, std::min(limit, succesors[1].second), &best.second) == Result::SUCCES)
		{
			return Result::SUCCES;
		}
		--info.depth;
		info.history.pop_front();
	}
}
