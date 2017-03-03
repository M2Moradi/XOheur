#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int GAME_STATE_CONTINUE = 0;
const int GAME_STATE_WON_X = 1;
const int GAME_STATE_WON_O = 2;
const int GAME_STATE_DRAW = 3;

void print_game (int game_state, bool x_first)
{
	char board[3][3];
	char player = x_first ? 'X' : 'O';
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) board[i][j] = ' ';
	while (game_state)
	{
		int cdig = game_state % 10 - 1;
		board[cdig % 3][cdig / 3] = player;
		player = (player == 'X') ? 'O' : 'X';
		game_state /= 10;
	}
	cout << " " << board[0][0] << " | " << board[1][0] << " | " << board[2][0] << endl;
	cout << "---+---+---" << endl;
	cout << " " << board[0][1] << " | " << board[1][1] << " | " << board[2][1] << endl;
	cout << "---+---+---" << endl;
	cout << " " << board[0][2] << " | " << board[1][2] << " | " << board[2][2] << endl;
}

int check_state (int game, bool x_first)
{
	char buf[9];
	for (int i = 0; i < 9; i++)
		buf[i] = ' ';
	int oc = 0;
	while (game)
	{
		buf[game % 10 - 1] = x_first ? 'X' : 'O';
		x_first = !x_first;
		game /= 10;
		oc++;
	}
	for (int i = 0; i < 9; i += 3)
		if (buf[i] == buf[i + 1] & buf[i + 1] == buf[i + 2] & buf[i + 2] != ' ')
			return (buf[i] == 'X') ? GAME_STATE_WON_X : GAME_STATE_WON_O;
	for (int i = 0; i < 3; i++)
		if (buf[i] == buf[i + 3] & buf[i + 3] == buf[i + 6] & buf[i + 6] != ' ')
			return (buf[i] == 'X') ? GAME_STATE_WON_X : GAME_STATE_WON_O;
	if (buf[0] == buf[4] & buf[4] == buf[8] & buf[0] != ' ')
		return (buf[0] == 'X') ? GAME_STATE_WON_X : GAME_STATE_WON_O;
	if (buf[2] == buf[4] & buf[4] == buf[6] & buf[2] != ' ')
		return (buf[2] == 'X') ? GAME_STATE_WON_X : GAME_STATE_WON_O;
	if (oc == 9)
		return GAME_STATE_DRAW;
	return GAME_STATE_CONTINUE;
}

bool check_valid(int game, int move)
{
	if (move < 1 | move > 9)
		return false;
	bool used[10];
	for (int i = 0; i < 10; i++)
		used[i] = false;
	while (game)
	{
		used[game % 10] = true;
		game /= 10;
	}
	return !used[move];
}

int main()
{
	srand(time(NULL));
	string sin = "";
	while (sin != "cpu" & sin != "player")
	{
		cout << "vs Player / CPU? (cpu/player)" << endl;
		cin >> sin;
	}
	bool vs_cpu = (sin == "cpu");
	cout << "X first? (Y/n)" << endl;
	char ch;
	cin >> ch;
	bool x_first = 0;
	bool cturn = 1;
	if (ch == 'n') x_first = 1;
	int game = 0;
	bool q = 0;
	while (!q)
	{
		system("cls");
		print_game(game, x_first);
		int cstate = check_state(game, x_first);
		switch (cstate)
		{
			case GAME_STATE_WON_X: 
				cout << "Congrats! X has won." << endl;
				q = true;
				break;
			case GAME_STATE_WON_O:
				cout << "Congrats! O has won." << endl;
				q = true;
				break;
			case GAME_STATE_DRAW:
				cout << "Sorry mate. It's a draw!" << endl;
				q = true;
				break;
			case GAME_STATE_CONTINUE:
				bool valid = false;
				int move;
				while (!valid)
				{
					if ((!cturn) & vs_cpu)
					{
						move = rand() % 10;
						valid = check_valid(game, move);
						//cout <<  move << ", " << valid << endl;
					}
					else
					{
						cout << (x_first ? "O" : "X") << " move: ";
						char chmove;
						cin >> chmove;
						move = int(chmove) - int('0');
						valid = check_valid(game, move);
						if (!valid)
							cout << "Invalid move! Try again." << endl;
					}
				}
				game = game * 10 + move;
				x_first = !x_first;
				cturn = !cturn;
				break;
		}
	}
	return 0;
}
