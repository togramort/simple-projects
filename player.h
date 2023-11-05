#include <vector>
#include <string>

class Player {
public:
	virtual void get_move(std::vector<std::vector<std::string>>& board, std::string mark);
	//int is_win(std::vector<std::vector<std::string>>& board);
};

class HumanPlayer : public Player {
public:
	void get_move(std::vector<std::vector<std::string>>& board, std::string mark) override;
};

class AiPlayer : public Player {
public:
	void get_move(std::vector<std::vector<std::string>>& board, std::string mark) override;

private:
	int minimax(std::vector<std::vector<std::string>>& board, int depth, bool is_max, std::string mark);
};