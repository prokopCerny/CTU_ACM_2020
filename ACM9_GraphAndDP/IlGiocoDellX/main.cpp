/**
 * Problem found at https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=196
 */
#include <iostream>
#include <vector>
#include <queue>
#include <array>
using namespace std;


template <class T>
class Matrix {
public:
    size_t rows;
    size_t columns;
    std::vector<T> grid;

    Matrix(size_t rows, size_t columns, T default_value) :
            rows(rows),
            columns(columns),
            grid(rows*columns, default_value) {}

    size_t getIdx(size_t row, size_t col) const {
        return row*columns+col;
    }

    size_t getRow(size_t index) const {
        return index / columns;
    }

    size_t getCol(size_t index) const {
        return index % columns;
    }

    T& operator[] (size_t index) {
        return grid[index];
    }

    T& operator() (size_t row, size_t col) {
        return grid[getIdx(row, col)];
    }
};

enum class Player {BLACK, WHITE};

bool can_get_to_last_row(Matrix<Player> &board, vector<bool> &visited, size_t start_col);

Player get_winner(Matrix<Player> &board, const vector<size_t> &black_start_columns) {
    if (black_start_columns.empty()) {
        return Player::WHITE;
    }
    Player winner = Player::WHITE;

    vector<bool> visited(board.rows*board.columns, false);

    for (size_t start_col : black_start_columns) {
        if (not visited[board.getIdx(0, start_col)]) {
            if (can_get_to_last_row(board, visited, start_col)) {
                winner = Player::BLACK;
                break;
            }
        }
    }

    return winner;
}

bool can_get_to_last_row(Matrix<Player> &board, vector<bool> &visited, size_t start_col) {
    constexpr array<pair<int16_t, int16_t>, 6> offsets = {{ {-1, -1},
                                                            {-1, 0},
                                                            {0, -1},
                                                            {0, 1},
                                                            {1, 0},
                                                            {1, 1} }};

    queue<size_t> queue;
    visited[board.getIdx(0, start_col)] = true;
    queue.push(board.getIdx(0, start_col));

    while (not queue.empty()) {
        size_t cur_loc = queue.front();
        queue.pop();

        size_t cur_row = board.getRow(cur_loc);
        size_t cur_col = board.getCol(cur_loc);

        for (auto& offset : offsets) {
            int32_t nRow = cur_row + offset.first;
            int32_t nCol = cur_col + offset.second;
            if ( (nRow >= 0)
                 and (nRow < board.rows)
                 and (nCol >= 0)
                 and (nCol < board.columns)) {
                size_t neigh_coords = board.getIdx( (size_t) nRow, (size_t) nCol);
                if (not visited[neigh_coords]
                    and board[neigh_coords] == Player::BLACK) {
                    visited[neigh_coords] = true;
                    if (nRow == board.rows -1) {
                        return true;
                    }
                    queue.push(neigh_coords);
                }

            }
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    for (size_t game_number = 1; ; ++game_number) {
        uint16_t N{};
        cin >> N;

        if (N == 0) {
            break;
        }

        Matrix<Player> board(N, N, Player::WHITE);
        vector<size_t> black_start_cols;
        for (uint16_t row = 0; row < N; row++) {
            for (uint16_t col = 0; col < N; col++) {
                char cur_player{};
                cin >> cur_player;
                if (cur_player == 'b') {
                    board(row, col) = Player::BLACK;
                    if (row == 0) {
                        black_start_cols.push_back(col);
                    }
                }
            }
        }
        Player winner = get_winner(board, black_start_cols);
        cout << game_number << " " << (winner == Player::WHITE ? "W" : "B") << endl;

    }
    return 0;
}
