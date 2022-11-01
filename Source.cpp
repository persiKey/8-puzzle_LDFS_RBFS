//#include <iostream>
//#include <vector>
//#include <time.h>
//#include <random>
//
//#include <string>
//#include <stack>
//#include <map>
//
//#include <forward_list>
//
//
//using std::cout;
//using std::cin;
//using std::vector;
//
//
//constexpr int LDFS_DEPTH_LIMIT = 25;
//
//constexpr int RBSF_DEPTH_LIMIT = 100;
//
//struct Token
//{
//	int pos_x;
//	int pos_y;
//};
//
//
//std::map<char, Token> TableFin
//{ {'1',{0,0} },
//{'2',{1,0} },
//{'3',{2,0} },
//{'4',{0,1} },
//{'5',{1,1} },
//{'6',{2,1} },
//{'7',{0,2} },
//{'8',{1,2} },
//{' ',{2,2} }};
//
//
//enum class Result
//{
//	SUCCES,
//	FAIL,
//	LIMIT
//};
//
//struct info;
//
//Result RecursiveLDFS(info& i);
//
//class State
//{
//public:
//	friend Result RecursiveLDFS(info& i);
//	friend int h(State& s);
//	friend Result RBSF(info& info, int limit, int& prev_best);
//
//	static constexpr int TOKEN_COUNT = 9;
//
//	enum class Move
//	{
//		UP,
//		DOWN,
//		LEFT,
//		RIGHT
//	};
//private:
//	Move Moves[4];
//	size_t moves_avail;
//
//	size_t empty_pos;
//	char field[TOKEN_COUNT];
//public:
//	static auto move_name(State::Move m) {
//		switch (m)
//		{
//		case State::Move::UP: return "UP";
//		case State::Move::DOWN: return "DOWN";
//		case State::Move::LEFT: return "LEFT";
//		case State::Move::RIGHT: return "RIGHT";
//		}
//	};
//
//	bool operator==(const State& A) const
//	{
//		for (size_t i = 0; i < TOKEN_COUNT; i++)
//		{
//			if (this->field[i] != A.field[i])
//				return false;
//		}
//		return true;
//	}
//
//	State()
//	{
//	
//
//		vector<int> UNUM(TOKEN_COUNT);
//		for (int i = 0; i < TOKEN_COUNT-1; i++)
//		{
//			UNUM[i] = i;
//		}
//		UNUM[TOKEN_COUNT-1] = ' ' - '1';
//
//		for (int i = 0; i < TOKEN_COUNT; i++)
//		{
//			int ind = rand() % UNUM.size();
//			field[i] = '1' + UNUM[ind];
//			UNUM.erase(UNUM.begin() + ind);
//		}
//		
//		empty_pos = std::find(field, field + TOKEN_COUNT, ' ') - field;
//		GetMovesAvail();
//	}
//
//	State(const State&) = default;
//
//	void EditState()
//	{
//		auto is_correct = [this](char field[TOKEN_COUNT]) {
//			using std::find;
//			char* field_end = field + this->TOKEN_COUNT;
//			if (field_end == find(field, field_end, ' '))
//				return false;
//			for (size_t i = 0; i < this->TOKEN_COUNT - 1; i++)
//			{
//				if (field_end == find(field, field_end, '1' + i))
//					return false;
//			}
//			return true;
//		};
//		cout << "Enter the matrix:\n";
//
//		do
//		{
//			for (size_t i = 0; i < TOKEN_COUNT; ++i)
//			{
//				field[i] = cin.get();
//				if(cin.peek() == '\n')
//					cin.ignore();
//			}
//
//			PrintState();
//			if (is_correct(field))
//			{
//				empty_pos = std::find(field, field + TOKEN_COUNT, ' ') - field;
//				GetMovesAvail();
//				break;
//			}
//			else
//			{
//				cout << "Data entered incorrect. Try again\n";
//			}
//		} while (true);
//		
//	}
//
//	void GetMovesAvail()
//	{
//		moves_avail = 0;
//		size_t val = empty_pos + 1;
//		size_t cmp = val % 3;
//		if (val < 7)
//			Moves[moves_avail++] = Move::UP;
//		if (2 == cmp)
//		{
//			Moves[moves_avail++] = Move::LEFT;
//			Moves[moves_avail++] = Move::RIGHT;
//		}
//		else
//			Moves[moves_avail++] = cmp ? Move::LEFT : Move::RIGHT;
//
//		if (3 < val)
//			Moves[moves_avail++] = Move::DOWN;
//		
//	}
//
//	bool IsFinal()
//	{
//		if(field[0] == '1' && 
//			field[1] == '2' &&
//			field[2] == '3' &&
//			field[3] == '4' &&
//			field[4] == '5' &&
//			field[5] == '6' &&
//			field[6] == '7' &&
//			field[7] == '8' )
//		return true;
//		
//		return false;
//	}
//
//	void MakeMove(Move m)
//	{
//		switch (m)
//		{
//		case State::Move::UP:
//			std::swap(field[empty_pos], field[empty_pos + 3]);
//			empty_pos += 3;
//			break;
//		case State::Move::DOWN:
//			std::swap(field[empty_pos], field[empty_pos - 3]);
//			empty_pos -= 3;
//			break;
//		case State::Move::LEFT:
//			std::swap(field[empty_pos], field[empty_pos + 1]);
//			++empty_pos;
//			break;
//		case State::Move::RIGHT:
//			std::swap(field[empty_pos], field[empty_pos - 1]);
//			--empty_pos;
//			break;
//		}
//		GetMovesAvail();
//	}
//
//	void PrintState()
//	{
//		const int BORDER_LEN = 2 + TOKEN_COUNT;
//		for (int i = 0; i < BORDER_LEN; i++)
//			cout << "*";
//		cout << '\n';
//		for (size_t i = 0; i < 3; i++)
//		{
//			cout << '*';
//			for (size_t k = 0; k < 3; k++)
//			{
//				cout << '|' << field[i * 3 + k] << '|';
//			}
//			cout << "*\n";
//
//		}
//
//		for (int i = 0; i < BORDER_LEN; i++)
//			cout << "*";
//		
//		cout << '\n';
//	}
//
//	void PrintMovesAvail()
//	{
//		
//		cout << "Moves available:" << moves_avail << '\n';
//		for (size_t i = 0; i < moves_avail; i++)
//		{
//			cout << move_name(Moves[i]) << '\n';
//		}
//	}
//};
//
//struct info
//{
//	int64_t state_count = 1;
//	int64_t dead_end = 0;
//
//	size_t depth = 0;
//	std::stack<State> history;
//};
//
//
//
//int h(State& s)
//{
//	auto get_token_pos = [](int linear_pos) {
//		Token res;
//		res.pos_x = linear_pos % 3;
//		res.pos_y = linear_pos / 3;
//		return res;
//	};
//	auto manhatten_lengt = [](const Token cur, const Token fin) -> int {
//		return abs(cur.pos_x - fin.pos_x) + abs(cur.pos_y - fin.pos_y);
//	};
//
//	int res = 0;
//
//	for (size_t k = 0; k < State::TOKEN_COUNT; k++)
//	{
//		if (s.field[k] == ' ')
//			continue;
//		res += manhatten_lengt(get_token_pos(k), TableFin[s.field[k]]);
//	}
//	return res;
//}
//
//
//std::forward_list<State> st;
//
//Result RBSF(info& info, int limit, int& prev_best)
//{
//	typedef std::pair<State, int > successor_h;
//
//	st.push_front(info.history.top());
//
//	if (info.history.top().IsFinal())
//		return Result::SUCCES;
//
//	successor_h succesors[4];
//	int s_count = 0;
//	for (size_t i = 0; i < info.history.top().moves_avail; i++)
//	{
//		succesors[s_count].first = info.history.top();
//		succesors [s_count].first.MakeMove(succesors[s_count].first.Moves[i]);
//		if (std::find(st.begin(), st.end(), succesors[s_count].first) != st.end())
//		{
//			continue;
//		}
//		succesors[s_count].second = h(succesors[s_count].first) + info.depth;
//		++info.state_count;
//		++s_count;
//	}
//	if (0 == s_count)
//	{
//		prev_best = std::numeric_limits<int>::max();
//		++info.dead_end;
//		return Result::FAIL;
//	}
//	if (1 == s_count)
//	{
//		//st.push_front(succesors[0].first);
//		info.history.push(succesors[0].first);
//		++info.depth;
//		//succesors[0].first.PrintState();
//		auto res = RBSF(info, limit, prev_best);
//		if (res == Result::SUCCES)
//			return res;
//		--info.depth;
//		st.pop_front();
//		info.history.pop();
//		return res;
//	}
//	for (;;)
//	{
//		std::sort(succesors, succesors + s_count,
//			[](const successor_h A, const successor_h B)
//			{ return A.second < B.second; });
//
//		successor_h &best = succesors[0];
//		//best.first.PrintState();
//		auto p_best = &best.second;
//		//cout << "best " << best.second << '\n';
//		if (best.second > limit)
//		{
//			prev_best = best.second;
//			++info.dead_end;
//			return Result::FAIL;
//		}
//		
//		info.history.push(best.first);
//		++info.depth;
//		if (RBSF(info, std::min(limit,succesors[1].second),best.second) == Result::SUCCES)
//		{
//			return Result::SUCCES;
//		}
//		--info.depth;
//		st.pop_front();
//		info.history.pop();
//		
//	}
//	return Result::FAIL;
//}
//
//void RecursiveBestFS(State& s)
//{
//	info inf;
//	inf.history.push(s);
//	int MAX_limit = std::numeric_limits<int>::max();
//	int dummy;
//
//	switch (RBSF(inf, MAX_limit,dummy))
//	{
//	case Result::FAIL: cout << "FAIL\n"; break;
//	case Result::SUCCES: cout << "\n\nSucces\n";
//
//	}
//	while (!inf.history.empty())
//	{
//		inf.history.top().PrintState();
//		inf.history.pop();
//	}
//	cout << "State count: " << inf.state_count << '\n';
//	cout << "Dead ends: " << inf.dead_end << '\n';
//	cout << "Depth: " << inf.depth << '\n';
//}
//
//Result RecursiveLDFS(info &info)
//{
//	if (info.history.top().IsFinal())
//		return Result::SUCCES;
//	else if (info.depth == LDFS_DEPTH_LIMIT)
//	{
//		++info.dead_end;
//		return Result::LIMIT;
//	}
//	
//	for (size_t i = 0; i < info.history.top().moves_avail; i++)
//	{
//		auto cur_move = info.history.top().Moves[i];
//		info.history.push(info.history.top());
//		++info.depth;
//		++info.state_count;
//		info.history.top().MakeMove(cur_move);
//		if (RecursiveLDFS(info) != Result::SUCCES)
//		{
//			info.history.pop();
//			--info.depth;
//		}
//		else
//			return Result::SUCCES;
//	}
//	
//	return Result::FAIL;
//
//}
//
//void LimitedDFS(State &s)
//{
//	info inf;
//	inf.history.push(s);
//	switch (RecursiveLDFS(inf))
//	{
//	case Result::FAIL: cout << "Fail\n"; break;
//	case Result::SUCCES: cout << "\n\nSucces\n";
//
//	}
//	while (!inf.history.empty())
//	{
//		inf.history.top().PrintState();
//		inf.history.pop();
//	}
//	cout << "State count: " << inf.state_count << '\n';
//	cout << "Dead ends: " << inf.dead_end << '\n';
//	cout << "Depth: " << inf.depth << '\n';
//}
//
//int main()
//{
//	
//	State A;
//	//A.PrintState();
//
//	A.EditState();
//	//cout << "h() " << h(A) << '\n';
//	
//	//cout << "LDFS:\n";
//	//LimitedDFS(A);
//	cout << "RBFS:\n";
//	RecursiveBestFS(A);
//	cin.get();
//
//	char key;
//	do
//	{
//		A.PrintState();
//		A.PrintMovesAvail();
//		cout << "Is final:" << std::boolalpha << A.IsFinal() << '\n';
//		key = cin.get();
//		cin.ignore();
//		switch (key)
//		{
//		case 'W':
//		case 'w': A.MakeMove(State::Move::UP); break;
//		case 'S':
//		case 's': A.MakeMove(State::Move::DOWN); break;
//		case 'A':
//		case 'a': A.MakeMove(State::Move::LEFT); break;
//		case 'D':
//		case 'd': A.MakeMove(State::Move::RIGHT); break;
//		}
//
//	} while (key != 'q' && key != 'Q');
//	
//
//	return 0;	
//}