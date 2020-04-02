/**
 * Problem found on
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2671
 */

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cstdint>
#include <limits>
#include <array>

using namespace std;

template <class T>
class Grid {
public:
    size_t rows;
    size_t columns;
    std::vector<T> grid;

    Grid(size_t rows, size_t columns, T default_value) : rows(rows), columns(columns), grid(rows*columns, default_value) {}

    size_t getIdx(size_t row, size_t col) {
        return row*columns+col;
    }

    size_t getRow(size_t index) {
        return index / columns;
    }

    size_t getCol(size_t index) {
        return index % columns;
    }
};

enum class Maze {EMPTY, WALL};

int64_t can_joe_escape_and_when(Grid<Maze> &maze, size_t joe_idx, vector<size_t> &fires_idxs);

Grid<uint32_t> create_fire_visit_times(Grid<Maze> &maze, vector<size_t> &fires_idxs);

int64_t can_joe_escape_and_when(Grid<Maze> &maze, size_t joe_idx, vector<size_t> &fires_idxs) {
    size_t start_row = maze.getRow(joe_idx);
    size_t start_col = maze.getCol(joe_idx);

    if ( (start_row == 0)
         or (start_row == maze.rows - 1)
         or (start_col == 0)
         or (start_col == maze.columns - 1)) {
        return 1;
    }

    Grid<uint32_t> fire_visit_times = create_fire_visit_times(maze, fires_idxs);
    constexpr array<pair<int8_t, int8_t>, 4> offsets = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

    Grid<bool> visited(maze.rows, maze.columns, false);
    Grid<uint32_t> joe_visit_times(maze.rows, maze.columns, numeric_limits<uint32_t>::max());

    queue<size_t> queue;

    visited.grid[joe_idx] = true;
    joe_visit_times.grid[joe_idx] = 0;
    queue.push(joe_idx);



    while (not queue.empty()) {
        size_t cur_joe = queue.front();
        queue.pop();
        size_t cur_row = maze.getRow(cur_joe);
        size_t cur_col = maze.getCol(cur_joe);

        uint32_t cur_joe_time = joe_visit_times.grid[cur_joe];

        for (auto& offset : offsets) {
            int64_t nRow = cur_row + offset.first;
            int64_t nCol = cur_col + offset.second;
            if ( (nRow >= 0)
                 and (nRow < maze.rows)
                 and (nCol >= 0)
                 and (nCol < maze.columns)) {

                size_t neighbor_coords = maze.getIdx( (size_t) nRow, (size_t) nCol);
                if (not visited.grid[neighbor_coords]
                    and maze.grid[neighbor_coords] == Maze::EMPTY
                    and fire_visit_times.grid[neighbor_coords] > cur_joe_time + 1) {
                    if ( (nRow == 0)
                         or (nRow == maze.rows - 1)
                         or (nCol == 0)
                         or (nCol == maze.columns - 1)) {
                        return cur_joe_time + 2;
                    }
                    joe_visit_times.grid[neighbor_coords] = cur_joe_time + 1;
                    visited.grid[neighbor_coords] = true;
                    queue.push(neighbor_coords);
                }

            }
        }

    }

    return -1;
}

Grid<uint32_t> create_fire_visit_times(Grid<Maze> &maze, vector<size_t> &fires_idxs) {
    constexpr array<pair<int8_t, int8_t>, 4> offsets = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

    Grid<bool> visited(maze.rows, maze.columns, false);
    Grid<uint32_t> fire_visit_times(maze.rows, maze.columns, numeric_limits<uint32_t>::max());

    queue<size_t> queue;

    for(auto fire: fires_idxs) {
        visited.grid[fire] = true;
        fire_visit_times.grid[fire] = 0;
        queue.push(fire);
    }

    while (not queue.empty()) {
        size_t current_fire = queue.front();
        queue.pop();
        size_t cur_row = maze.getRow(current_fire);
        size_t cur_col = maze.getCol(current_fire);

        uint32_t cur_fire_time = fire_visit_times.grid[current_fire];

        for (auto& offset : offsets) {
            int64_t nRow = cur_row + offset.first;
            int64_t nCol = cur_col + offset.second;
            if ( (nRow >= 0)
                and (nRow < maze.rows)
                and (nCol >= 0)
                and (nCol < maze.columns)) {

                size_t neighbor_coords = maze.getIdx( (size_t) nRow, (size_t) nCol);
                if (not visited.grid[neighbor_coords]
                    and maze.grid[neighbor_coords] == Maze::EMPTY) {
                    fire_visit_times.grid[neighbor_coords] = cur_fire_time + 1;
                    visited.grid[neighbor_coords] = true;
                    queue.push(neighbor_coords);
                }

            }
        }

    }

    return fire_visit_times;
}


int main() {
    ios_base::sync_with_stdio(false);

    size_t test_cases{};
    cin >> test_cases;

    for(size_t test_case = 0; test_case < test_cases; test_case++) {
        size_t rows{}, cols{};
        cin >> rows >> cols;
        Grid<Maze> maze(rows, cols, Maze::EMPTY);
        size_t joe_idx{};
        vector<size_t> fires_idxs;
        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                char curPos{};
                cin >> curPos;
                switch (curPos) {
                    case '#':
                        maze.grid[maze.getIdx(row, col)] = Maze::WALL;
                        break;
                    case 'J':
                        joe_idx = maze.getIdx(row, col);
                        break;
                    case 'F':
                        fires_idxs.push_back(maze.getIdx(row, col));
                        break;
                    default:
                        break;
                }
            }
        }

        int64_t minutes_to_escape = can_joe_escape_and_when(maze, joe_idx, fires_idxs);
        if (minutes_to_escape < 0) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << minutes_to_escape << endl;
        }

    }
    return 0;
}
