/**
 * Problem found on https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2678
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <tuple>
#include <limits>
#include <algorithm>

using namespace std;

class UnionFind {
    size_t set_count;
    vector<uint64_t> rank;
    vector<size_t> parent;

public:
    explicit UnionFind(size_t count) :
            set_count(count),
            rank(count, 0),
            parent(count) {

        iota(parent.begin(), parent.end(), 0); // fill with 0, 1, 2, ... , set_count-1
    }

    size_t find(size_t vertex) {
        if (vertex != parent[vertex]) {
            parent[vertex] = find(parent[vertex]);
        }
        return parent[vertex];
    }

    void merge(size_t u, size_t v) {
        size_t set_u = find(u);
        size_t set_v = find(v);

        if (rank[set_u] > rank[set_v]) {
            parent[set_v] = set_u;
        } else {
            parent[set_u] = set_v;
        }

        if (rank[set_u] == rank[set_v]) {
            rank[set_v]++;
        }
    }
};

template <class WEIGHT>
class EdgeGraph {
public:
    size_t vertices;
    vector<pair<WEIGHT, pair<size_t, size_t>>> edges;

    explicit EdgeGraph(size_t vertices) : vertices(vertices) {}

    void addEdge(size_t from, size_t to, WEIGHT weight) {
        edges.push_back( {weight, {from, to}} );
    }

    WEIGHT kruskalMinCost() {
        size_t number_of_edges_to_use = vertices-1;
        WEIGHT cost = 0;
        sort(edges.begin(), edges.end());

        UnionFind components(vertices);

        size_t used_edges{0};

        for (auto& edge : edges) {
            WEIGHT cur_weight = edge.first;

            size_t from{}, to{};
            tie(from, to) = edge.second;

            size_t from_component = components.find(from);
            size_t to_component = components.find(to);
            if (from_component != to_component) {
                components.merge(from_component, to_component);
                cost += cur_weight;
                used_edges++;
                if (used_edges == number_of_edges_to_use) {
                    return cost;
                }
            }
        }
        return numeric_limits<WEIGHT>::max();
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    size_t junctions{}, roads{};
    while (cin >> junctions >> roads, not (junctions == 0 and roads == 0)) {
        EdgeGraph<uint32_t> graph(junctions);
        uint64_t total_cost{0};
        for (size_t road_idx = 0; road_idx < roads; ++road_idx) {
            uint32_t from{}, to{}, cost{};
            cin >> from >> to >> cost;
            total_cost += cost;
            graph.addEdge(from, to, cost);
        }
        uint32_t can_save = graph.kruskalMinCost();
        cout << total_cost - can_save << endl;
    }
    return 0;
}
