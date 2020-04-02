/**
 * Problem can be found at
 * https://www.spoj.com/problems/MICEMAZE/
 */
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cstdint>
#include <limits>
#include <set>
#include <tuple>

using namespace std;

class WeightedGraph {
public:
    uint64_t vertices;
    vector<list<pair<uint64_t, uint64_t>>> adjacency_list;

    explicit WeightedGraph(uint64_t vertices) : vertices(vertices), adjacency_list(vertices) {}

    WeightedGraph(WeightedGraph &&other) = default;

    void add_edge(uint64_t from, uint64_t to, uint64_t cost) {
        adjacency_list[from].emplace_back(to, cost);
    }
};

uint64_t dijkstra(WeightedGraph &graph, uint64_t exit, uint64_t timer);

int main() {
    uint64_t nodes{}, exit_cell{}, timer{}, edges{};
    cin >> nodes >> exit_cell >> timer >> edges;
    exit_cell--;

    WeightedGraph graph(nodes);

    for(uint64_t edge_idx = 0; edge_idx < edges; edge_idx++) {
        uint64_t from{}, to{}, cost{};
        cin >> from >> to >> cost;
        //need to reverse edges
        graph.add_edge(to-1, from-1, cost);
    }

    uint64_t how_many_reached_exit = dijkstra(graph, exit_cell, timer);

    cout << how_many_reached_exit << endl;

    return 0;
}

uint64_t dijkstra(WeightedGraph &graph, uint64_t exit, uint64_t timer) {
    vector<uint64_t> distance(graph.vertices, numeric_limits<uint64_t>::max());
    set<pair<uint64_t, uint64_t>> queue;

    distance[exit] = 0;
    queue.insert(std::make_pair(0, exit));

    uint64_t escaped = 0;

    while (not queue.empty()) {
        auto cur_state_pair = *(queue.begin());
        queue.erase(queue.begin());

        uint64_t cost = cur_state_pair.first;
        uint64_t cur_state = cur_state_pair.second;

        if (cost <= timer) {
            escaped++;
        } else {
            return escaped;
        }

        for (auto neighbor_pair : graph.adjacency_list[cur_state]) {
            uint64_t neighbor = neighbor_pair.first;
            uint64_t cost = neighbor_pair.second;
            if (distance[neighbor] > distance[cur_state] + cost) {
                if (distance[neighbor] != numeric_limits<uint64_t>::max()) {
                    queue.erase(queue.find(make_pair(distance[neighbor], neighbor)));
                }

                distance[neighbor] = distance[cur_state] + cost;
                queue.insert(make_pair(distance[neighbor], neighbor));
            }
        }


    }
    return escaped;
}
