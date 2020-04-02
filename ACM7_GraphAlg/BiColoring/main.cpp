#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cstdint>

using namespace std;

class Graph {
public:
    uint16_t vertices;
    vector<list<uint16_t>> adjacency_list;

    explicit Graph(uint16_t vertices) : vertices(vertices), adjacency_list(vertices) {
    }

    Graph(Graph &&other) = default;

    void add_edge(uint16_t from, uint16_t to) {
        adjacency_list[from].emplace_back(to);
        adjacency_list[to].emplace_back(from);
    }
};

bool is_graph_bipartite(Graph &graph);

/**
 * Problem can be found on
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=37&page=show_problem&problem=945
 */
int main() {
    std::ios_base::sync_with_stdio(false);
    while (true) {
        uint16_t vertices{};

        cin >> vertices;
        if (vertices != 0) {
            Graph graph(vertices);
            uint16_t edge_count{};
            cin >> edge_count;
            for (uint16_t edge_id = 0; edge_id < edge_count ; edge_id++) {
                uint16_t from{}, to{};
                cin >> from >> to;
                graph.add_edge(from, to);
            }

            if (is_graph_bipartite(graph)) {
                cout << "BICOLORABLE." << endl;
            } else {
                cout << "NOT BICOLORABLE." << endl;
            }
        } else {
            break;
        }
    }
    return 0;
}

enum class Color {NONE, RED, BLUE};

bool is_graph_bipartite(Graph &graph) {
    vector<Color> color(graph.vertices, Color::NONE);

    queue<uint16_t> queue;
    color[0] = Color::RED;
    queue.push(0);

    while (not queue.empty()) {
        uint16_t cur = queue.front();
        queue.pop();
        for (uint16_t neighbor : graph.adjacency_list[cur]) {
            if (color[cur] == color[neighbor]) {
                return false;
            } else {
                if (color[neighbor] == Color::NONE) {
                    color[neighbor] = color[cur] == Color::RED ? Color::BLUE : Color::RED;
                    queue.push(neighbor);
                }
            }
        }
    }

    return true;
}
