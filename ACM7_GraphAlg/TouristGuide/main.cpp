/**
 * Problem found on
 * https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1040
 */
#include <iostream>
#include <vector>
#include <list>
#include <cstdint>
#include <limits>
#include <cmath>
#include <set>
#include <tuple>

using namespace std;


class WeightedGraph {
public:
    size_t vertices;
    vector<list<pair<size_t, uint64_t>>> adjacency_list;

    explicit WeightedGraph(size_t vertices) : vertices(vertices), adjacency_list(vertices) {}

    WeightedGraph(WeightedGraph &&other) = default;

    void add_edge(size_t from, size_t to, uint64_t cost) {
        adjacency_list[from].emplace_back(to, cost);
    }
};

uint64_t find_bottleneck_edge_cost(WeightedGraph &graph, size_t source, size_t sink) {
    vector<uint64_t> max_capacity(graph.vertices, 0);
    set<pair<uint64_t, size_t>> queue;

    max_capacity[source] = numeric_limits<uint64_t>::max();
    queue.insert(make_pair(max_capacity[source], source));

    while (not queue.empty()) {
        uint64_t cur_capacity{}; size_t cur{};

        tie(cur_capacity, cur) = *queue.rbegin();
        queue.erase(std::next(queue.rbegin()).base());

        if (cur == sink) {
            return cur_capacity;
        }

        for (auto& neighbor_pair : graph.adjacency_list[cur]) {
            uint64_t neighbor_capacity{}; size_t neighbor{};
            tie(neighbor, neighbor_capacity) = neighbor_pair;

            uint64_t can_reach_through_cur = min(neighbor_capacity, cur_capacity);
            if (can_reach_through_cur > max_capacity[neighbor]) {
                if (max_capacity[neighbor] != 0) {
                    queue.erase(queue.find(make_pair(max_capacity[neighbor], neighbor)));
                }

                max_capacity[neighbor] = can_reach_through_cur;
                queue.emplace(max_capacity[neighbor], neighbor);
            }
        }
    }
    return numeric_limits<uint64_t>::max();
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
        WeightedGraph graph(vertices);

        for (size_t edge_idx = 0; edge_idx < edges; edge_idx++) {
            uint16_t from{}, to{};
            int64_t capacity{};

            cin >> from >> to >> capacity;
            from--; to--; // 1 indexed in input
            capacity--; // The tourist guide must go with the group through each edge
            // undirected graph
            graph.add_edge(from, to, capacity);
            graph.add_edge(to, from, capacity);
        }

        uint16_t source{}, sink{};
        int64_t amount_of_people{};

        cin >> source >> sink >> amount_of_people;
        source--; sink--;

        auto bottleneck = find_bottleneck_edge_cost(graph, source, sink);
        auto minimum_number_of_trips = (uint64_t) ceil(amount_of_people / double(bottleneck));

        cout << "Scenario #" << scenario_counter << endl;
        cout << "Minimum Number of Trips = " << minimum_number_of_trips << endl << endl;

    }
    return 0;
}
