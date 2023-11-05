#include "player.h"
#include "game.h"
#include <iostream>
#include <random>
#include <string>
#include <algorithm>

void HumanPlayer::get_move(std::vector<std::vector<std::string>>& board, std::string mark) {
	int num;
	if (mark == "X") {
		num = 1;
	} else {
		num = 2;
	}
	
	bool valid_move = false;
	while (!valid_move) {
		std::cout << "\033[32m" << "\n{ player" << num << " (" << mark << ") }" << "\033[0m" << "\nchoose your move(press 1 - 9) : ";
		std::string input;
		std::cin >> input;
		if (std::isdigit(input[0])) {
			int move = std::stoi(input);
			if (move > 0 && move < 10) {
				if (board[(move - 1) / 3][(move - 1) % 3] != "X" && board[(move - 1) / 3][(move - 1) % 3] != "O") {
					board[(move - 1) / 3][(move - 1) % 3] = mark;
					valid_move = true;
				}
				else {
					std::cout << "\033[31m" << "\noopsie there've been a move already\n" << "\033[0m";
					valid_move = false;
				}
			}
			else {
				std::cout << "\033[31m" << "\nwatch yourself huh!\n" << "\033[0m";
				valid_move = false;
			}
		} else {
			std::cout << "\033[31m" << "\nclever but no.. no letters please\n" << "\033[0m";
			valid_move = false;
		}
	}
}

int AiPlayer::minimax(std::vector<std::vector<std::string>>& board, int depth, bool is_max, std::string mark) {
	Game game;
	int res = game.is_win(board);
	//std::cout << "\nits a ressssss: " << res << "\n";
	if (res == 1) {
		return 1;
	}
	else if (res == -1) {
		return -1;
	}
	else if (res == 0) {
		return 0;
	}

	if (is_max) {
		int best = -1000;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (board[i][j] != "X" && board[i][j] != "O") {
					std::string temp = board[i][j];
					board[i][j] = mark;
					best = std::max(best, minimax(board, depth + 1, !is_max, "X"));
					board[i][j] = temp;
					//std::cout << "\ntemp2 in max" << temp1 << "\n";
				}
			}
		}
		return best;
	} else if (!is_max) {
		int best = 1000;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (board[i][j] != "X" && board[i][j] != "O") {
					std::string temp = board[i][j];
					board[i][j] = mark;
					best = std::min(best, minimax(board, depth + 1, is_max, "O"));
					board[i][j] = temp;
				}
			}
		}
		return best;
	}
}

void AiPlayer::get_move(std::vector<std::vector<std::string>>& board, std::string mark) {
	std::cout << "\033[36m" << "\n{ player2 (O) }" << "\033[0m" << "\nai is thinking...\n";
	int best_val = -1000;
	int best_row, best_col;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] != "X" && board[i][j] != "O") {
				std::string temp = board[i][j];
				board[i][j] = mark;
				int move_val = minimax(board, 0, false, "X");
				board[i][j] = temp;

				if (move_val > best_val) {
					best_row = i;
					best_col = j;
					best_val = move_val;
				}
			}
		}
	}
	board[best_row][best_col] = mark;
}

void Player::get_move(std::vector<std::vector<std::string>>& board, std::string mark) {
	std::vector<std::string> numbers;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			std::string temp = board[i][j];
			if (std::isdigit(temp[0])) {
				numbers.emplace_back(temp);
			}
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, numbers.size());
	int idx = dist(gen);
	int new_move = std::stoi(numbers[idx]);

	board[(new_move - 1) / 3][(new_move - 1) % 3] = "O";
}