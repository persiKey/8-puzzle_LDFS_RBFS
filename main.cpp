#include <iostream>
#include "State.h"
#include "SearchAlgs.h"

using std::cout;
using std::cin;

void ManualSolving(State s)
{
	char key;
	do
	{
		s.PrintState();
		s.PrintMovesAvail();
		cout << "Is final:" << std::boolalpha << s.IsFinal() << '\n';
		key = cin.get();
		std::cin.ignore();
		switch (key)
		{
		case 'W':
		case 'w': s.DoMove(State::Move::UP); break;
		case 'S':
		case 's': s.DoMove(State::Move::DOWN); break;
		case 'A':
		case 'a': s.DoMove(State::Move::LEFT); break;
		case 'D':
		case 'd': s.DoMove(State::Move::RIGHT); break;
		}

	} while (key != 'q' && key != 'Q');
}


int main()
{
	srand(time(0));

	char key;
	State state;
	cout << "State:\n";
	state.PrintState();
	do
	{
		cout << "\n1 - Generate new\n"
			"2 - Enter\n"
			"3 - Try yourself\n"
			"4 - LDFS\n"
			"5 - RBFS + manhatten euristic\n";
		key = cin.get();
		cin.ignore();
		switch (key)
		{
		case '1': state = State(); 
			cout << "\nNew state:\n"; state.PrintState(); break;
		case '2': state.EditState(); break;
		case '3': ManualSolving(state); break;
		case '4': LimitedDFS(state); break;
		case '5': RecursiveBestFS(state); break;
		default:
			break;
		}

	} while (key != 'e' && key != 'E');
	
	return 0;
}