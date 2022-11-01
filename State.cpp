#include "State.h"
#include <vector>
#include <iostream>
#include <random>

using std::vector;
using std::cout;
using std::cin;

State::State()
{
	vector<int> UNUM(TOKEN_COUNT);

	do
	{
		UNUM.resize(TOKEN_COUNT);
		for (int i = 0; i < TOKEN_COUNT - 1; i++)
		{
			UNUM[i] = i;
		}
		UNUM[TOKEN_COUNT - 1] = ' ' - '1';

		for (int i = 0; i < TOKEN_COUNT; i++)
		{
			int ind = rand() % UNUM.size();
			field[i] = '1' + UNUM[ind];
			UNUM.erase(UNUM.begin() + ind);
		}
	} while (!IsSolvable());

	empty_pos = std::find(field, field + TOKEN_COUNT, ' ') - field;
	CalcMovesAvail();
}

bool State::operator==(const State& A) const
{
	for (size_t i = 0; i < TOKEN_COUNT; i++)
	{
		if (this->field[i] != A.field[i])
			return false;
	}
	return true;
}

void State::CalcMovesAvail()
{
	moves_avail = 0;
	size_t val = empty_pos + 1;
	size_t cmp = val % 3;
	if (val < 7)
		Moves[moves_avail++] = Move::UP;
	if (2 == cmp)
	{
		Moves[moves_avail++] = Move::LEFT;
		Moves[moves_avail++] = Move::RIGHT;
	}
	else
		Moves[moves_avail++] = cmp ? Move::LEFT : Move::RIGHT;

	if (3 < val)
		Moves[moves_avail++] = Move::DOWN;

}

bool State::IsSolvable()
{
	int inv_count = 0;
	for (size_t i = 0; i < TOKEN_COUNT-1; i++)
	{
		for (size_t k = i+1; k < TOKEN_COUNT; k++)
		{
			if (field[i] > field[k] &&
				field[i] != ' ' &&
				field[k] != ' ')
				++inv_count;
		}
	}
	return !(inv_count % 2);
}

void State::PrintState()
{
	const int BORDER_LEN = 2 + TOKEN_COUNT;
	for (int i = 0; i < BORDER_LEN; i++)
		cout << "*";
	cout << '\n';
	for (size_t i = 0; i < 3; i++)
	{
		cout << '*';
		for (size_t k = 0; k < 3; k++)
		{
			cout << '|' << field[i * 3 + k] << '|';
		}
		cout << "*\n";

	}

	for (int i = 0; i < BORDER_LEN; i++)
		cout << "*";

	cout << '\n';
}

void State::PrintMovesAvail()
{
	 auto move_name = [](State::Move m) {
		switch (m)
		{
		case State::Move::UP: return "UP";
		case State::Move::DOWN: return "DOWN";
		case State::Move::LEFT: return "LEFT";
		case State::Move::RIGHT: return "RIGHT";
		}
	};

	cout << "Moves available:" << moves_avail << '\n';
	for (size_t i = 0; i < moves_avail; i++)
	{
		cout << move_name(Moves[i]) << '\n';
	}
}

void State::EditState()
{
	auto is_correct = [this](char field[TOKEN_COUNT]) {
		using std::find;
		char* field_end = field + this->TOKEN_COUNT;
		if (field_end == find(field, field_end, ' '))
			return false;
		for (size_t i = 0; i < this->TOKEN_COUNT - 1; i++)
		{
			if (field_end == find(field, field_end, '1' + i))
				return false;
		}
		return true;
	};
	cout << "Enter the matrix:\n";

	do
	{
		for (size_t i = 0; i < TOKEN_COUNT; ++i)
		{
			field[i] = cin.get();
			if (cin.peek() == '\n')
				cin.ignore();
		}

		PrintState();

		if (!is_correct(field))
		{
			cout << "Data entered incorrect. Try again\n";
		}
		else if (!IsSolvable())
		{
			cout << "Entered State is unsolvable. Try again\n";
		}
		else
		{
			empty_pos = std::find(field, field + TOKEN_COUNT, ' ') - field;
			CalcMovesAvail();
			break;
		}
	} while (true);
}

bool State::IsFinal()
{
	if (field[0] == '1' &&
		field[1] == '2' &&
		field[2] == '3' &&
		field[3] == '4' &&
		field[4] == '5' &&
		field[5] == '6' &&
		field[6] == '7' &&
		field[7] == '8')
		return true;

	return false;
}

void State::DoMove(Move m)
{
	switch (m)
	{
	case State::Move::UP:
		std::swap(field[empty_pos], field[empty_pos + 3]);
		empty_pos += 3;
		break;
	case State::Move::DOWN:
		std::swap(field[empty_pos], field[empty_pos - 3]);
		empty_pos -= 3;
		break;
	case State::Move::LEFT:
		std::swap(field[empty_pos], field[empty_pos + 1]);
		++empty_pos;
		break;
	case State::Move::RIGHT:
		std::swap(field[empty_pos], field[empty_pos - 1]);
		--empty_pos;
		break;
	}
	CalcMovesAvail();
}