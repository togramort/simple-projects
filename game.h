#include <vector>

class Game {
public:

    void print_board(std::vector<std::vector<std::string>>& board);
    void start_game();
    void play_game(int choice);
    int is_win(std::vector<std::vector<std::string>>& board);
};