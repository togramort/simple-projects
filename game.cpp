#include <iostream>
#include <vector>
#include <string>
#include "game.h"
#include "player.h"


std::vector<std::vector<std::string>> start_board = {
    {"1", "2", "3"},
    {"4", "5", "6"},
    {"7", "8", "9"}
};

void Game::print_board(std::vector<std::vector<std::string>>& board) {
    std::cout << "+---+---+---+\n";
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            std::cout << "| " << board[i][j] << " ";
        }
        std::cout << "|\n";
        std::cout << "+---+---+---+\n";
    }
}

void Game::start_game() {
    std::cout << "\nwelcome to this maybe awesome tic tac toe game! which mode would you prefer?\n";
    std::cout << "[1] singleplayer (vs ai)\n[2] multiplayer (vs your real friend)\n[3] exit ;(\n";
    std::string input;
    std::cin >> input;
    if (!std::isdigit(input[0])) {
        std::cout << "\nclever but no.. no letters please\n";
        Game::start_game();
    }

    int choice = std::stoi(input);
    if (choice == 1) {
        std::cout << "\nooof youre a brave one! for that i let you to start first as { player 1 (X) }\n";
        Game::play_game(choice);
    } else if (choice == 2) {
        std::cout << "\nthats cool you have a friend.. soo decide who will go first as { player 1 (X) }\n";
        Game::play_game(choice);
    } else if (choice == 3) {
        std::cout << "\nthx for beeing with me :) have a great day~~~\n";
        exit(3);
    } else {
        std::cout << "\033[31m" << "\ni see sth went wrong... its okay try again :)\n" << "\033[0m";
        Game::start_game();
    }
}

void Game::play_game(int choice) {
    std::vector<std::vector<std::string>> board = start_board;
    HumanPlayer p1;
    Player* p2 = nullptr;

    if (choice == 1) {
        p2 = new AiPlayer();
    } else if (choice == 2) {
        p2 = new HumanPlayer();
    }
    int res;
    Game::print_board(board);
    std::string mark1 = "X";
    std::string mark2 = "O";
    while (true) {
        p1.get_move(board, mark1);
        Game::print_board(board);
        if (is_win(board) == 1) {
            std::cout << "\033[35m" << "\n\nGAME OVER! WINNER: " << mark2 << "\033[0m";
            break;
        } else if (is_win(board) == -1) {
            std::cout << "\033[35m" << "\n\nGAME OVER! WINNER: " << mark1 << "\033[0m";
            break;
        } else if (is_win(board) == 0) {
            std::cout << "\033[35m" << "\n\nGAME OVER! TIE~~~" << "\033[0m";
            break;
        }
        p2->get_move(board, mark2);
        Game::print_board(board);
        if (is_win(board) == 1) {
            std::cout << "\033[35m" << "\n\nGAME OVER! WINNER: " << mark2 << "\033[0m";
            break;
        }
        else if (is_win(board) == -1) {
            std::cout << "\033[35m" << "\n\nGAME OVER! WINNER: " << mark1 << "\033[0m";
            break;
        }
        else if (is_win(board) == 0) {
            std::cout << "\033[35m" << "\n\nGAME OVER! TIE~~~" << "\033[0m";
            break;
        }
    }

    std::cout << "\nnice game! wanna continue and play another one? (y/n)\n";
    char input;
    std::cin >> input;
    if (std::tolower(input) == 'y') {
        Game::start_game();
    } else {
        std::cout << "\nthx for beeing with me :) have a great day~~~\n";
        exit(5);
    }
}

int Game::is_win(std::vector<std::vector<std::string>>& board) {
    // return 
    // 3 - win
    // 2 - tie
    // 1 - continue playing

    for (auto row : board) {
        if (row[0] == row[1] && row[1] == row[2]) {
            if (row[0] == "O") {
                return +1;
            }
            else if (row[0] == "X") {
                return -1;
            }
        }
    }

    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == "O") {
                return +1;
            }
            else if (board[0][col] == "X") {
                return -1;
            }
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == "O") {
            return +1;
        }
        else if (board[0][0] == "X") {
            return -1;
        }
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == "O") {
            return +1;
        }
        else if (board[0][2] == "X") {
            return -1;
        }
    }

    for (auto row : board) {
        for (auto cell : row) {
            if (cell != "X" && cell != "O") {
                return 3;
            }
        }
    }

    return 0;
}