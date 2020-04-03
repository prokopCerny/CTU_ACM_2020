/**
 * WRONG IDEA, THOUGHT THE PROBLEM WAS A MAXFLOW TASK, BUT IT'S NOT
 * but this file does contain a Ford-Fulkerson implementation
 * Problem found on
 * https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1040
 */
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cstdint>
#include <limits>
#include <cmath>

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

    size_t getIdx(size_t row, size_t col) {
        return row*columns+col;
    }

    size_t getRow(size_t index) {
        return index / columns;
    }

    size_t getCol(size_t index) {
        return index % columns;
    }

    T& operator[] (size_t index) {
        return grid[index];
    }

    T& operator() (size_t row, size_t col) {
        return grid[getIdx(row, col)];
    }
};

bool exists_augmenting_path(Matrix<int64_t> &residual_graph, size_t source, size_t sink, vector<int64_t> &parent) {
    //bfs
    vector<bool> visited(residual_graph.rows, false);
    queue<size_t> queue;
    queue.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (not queue.empty()) {
        size_t cur = queue.front();
        queue.pop();
        for (size_t neighbor = 0; neighbor < residual_graph.columns; neighbor++){
            if (not visited[neighbor] and residual_graph(cur, neighbor) > 0) {
                visited[neighbor] = true;
                parent[neighbor] = cur;
                queue.push(neighbor);
            }
        }
    }

    return visited[sink];
}

uint64_t get_max_flow(Matrix<int64_t> &graph, size_t source, size_t sink) {
    Matrix<int64_t> residualGraph(graph);
    vector<int64_t> parent(graph.rows, -1);
    uint64_t max_flow{0};

    while(exists_augmenting_path(residualGraph, source, sink, parent)) {
        int64_t path_flow = numeric_limits<int64_t>::max();
        for(size_t v = sink; v != source; v = parent[v]) {
            size_t u = parent[v];
            path_flow = min(path_flow, residualGraph(u, v));
        }

#ifdef MY_DEBUG
        if (path_flow < 0) {
            cerr << "WTF NEGATIVE FLOW" << endl;
            exit(-1);
        }
#endif

        for(size_t v = sink; v != source; v = parent[v]) {
            size_t u = parent[v];
            residualGraph(u, v) -= path_flow;
            residualGraph(v, u) += path_flow;
        }

        max_flow += (uint64_t) path_flow;
    }

    return max_flow;
}

int main() {
    ios_base::sync_with_stdio(false);

    uint16_t vertices{}, edges{};
    size_t scenario_counter{0};
    while (true) {
        cin >> vertices >> edges;
        if (vertices == 0 and edges == 0) {
            break;
        }
        scenario_counter++;
        Matrix<int64_t> graph(vertices, vertices, 0);

        for (size_t edge_idx = 0; edge_idx < edges; edge_idx++) {
            uint16_t from{}, to{};
            int64_t capacity{};

            cin >> from >> to >> capacity;
            from--; to--;
            // undirected graph
            graph(from, to) = capacity;
            graph(to, from) = capacity;
        }

        uint16_t source{}, sink{};
        int64_t amount_of_people{};

        cin >> source >> sink >> amount_of_people;
        source--; sink--;

        auto max_flow = get_max_flow(graph, source, sink);
        auto minimum_number_of_trips = (uint64_t) ceil(amount_of_people / (double) max_flow);

        cout << "Scenario #" << scenario_counter << endl;
        cout << "Minimum Number of Trips = " << minimum_number_of_trips << endl;

    }
    return 0;
}
