/**
 * Problem can be found at
 * https://www.spoj.com/problems/PT07Z/
 */
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cstdint>
#include <limits>
#include <tuple>

using namespace std;

class Graph {
public:
    uint64_t vertices;
    vector<list<uint64_t>> adjacency_list;

    explicit Graph(uint64_t vertices) : vertices(vertices), adjacency_list(vertices) {}

    Graph(Graph &&other) = default;

    void add_edge(uint64_t from, uint64_t to) {
        adjacency_list[from].emplace_back(to);
        adjacency_list[to].emplace_back(from);
    }
};

pair<uint64_t, uint64_t> find_farthest_from_node(Graph &tree, uint64_t start_node) {
    vector<uint64_t> distance(tree.vertices, numeric_limits<uint64_t>::max());
    vector<bool> visited(tree.vertices, false);
    uint64_t max_dist = 0;
    uint64_t max_dist_node = 0;
    queue<uint64_t> queue;

    distance[start_node] = 0;
    visited[start_node] = true;
    queue.push(start_node);

    while (not queue.empty()) {
        uint64_t current = queue.front();
        queue.pop();
        uint64_t cur_dist = distance[current];
        if (cur_dist > max_dist) {
            max_dist = cur_dist;
            max_dist_node = current;
        }
        for (auto neighbor : tree.adjacency_list[current]) {
            if (not visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = cur_dist + 1;
                queue.push(neighbor);
            }
        }
    }

    return make_pair(max_dist, max_dist_node);

}

int main() {
    uint64_t nodes{};
    cin >> nodes;
    Graph tree(nodes);
    for (size_t edge_idx = 0; edge_idx < nodes - 1; edge_idx++) {
        uint64_t from{}, to{};
        cin >> from >> to;
        tree.add_edge(from - 1, to - 1);
    }

    uint64_t max_dist{}, max_dist_node{};

    tie(max_dist, max_dist_node) = find_farthest_from_node(tree, 0);
    tie(max_dist, max_dist_node) = find_farthest_from_node(tree, max_dist_node);
    cout << max_dist << endl;
    return 0;
}
