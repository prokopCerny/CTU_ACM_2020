/**
 * Problem found on
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1310
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cstdint>
#include <numeric>
#include <limits>
#include <cmath>
#include <tuple>
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

    WEIGHT kruskalForestMaxWeight(size_t number_of_edges_to_use) {
        //
        WEIGHT max_weight{0};
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
                max_weight = max(max_weight, cur_weight);
                used_edges++;
                if (used_edges == number_of_edges_to_use) {
                    return max_weight;
                }
            }
        }
        return numeric_limits<WEIGHT>::min();
    }
};



int main() {
    ios_base::sync_with_stdio(false);

    size_t test_cases{};
    cin >> test_cases;
    for (size_t test_case = 0; test_case < test_cases; ++test_case) {
        uint16_t satellite_channels{}, outposts{};
        cin >> satellite_channels >> outposts;

        vector<pair<int32_t, int32_t>> outpost_positions;
        outpost_positions.reserve(outposts);
        EdgeGraph<double> graph(outposts);
        for (size_t outpost_idx = 0; outpost_idx < outposts; ++outpost_idx) {
            int32_t x{}, y{};
            cin >> x >> y;
            for (size_t other_outpost_idx = 0; other_outpost_idx < outpost_idx; other_outpost_idx++) {
                auto& outpost = outpost_positions[other_outpost_idx];
                int32_t x_diff = x - outpost.first;
                int32_t y_diff = y - outpost.second;
                double distance = sqrt( double(x_diff * x_diff + y_diff * y_diff) );
                graph.addEdge(outpost_idx, other_outpost_idx, distance);
            }
            outpost_positions.emplace_back(x, y);
        }
        // we need to create a forest between stations using only this many connections
        // output of the problem is the maximum weight edge in the resulting forest
        size_t number_of_edges_to_use = outposts - satellite_channels;
        cout << fixed << setprecision(2) << graph.kruskalForestMaxWeight(number_of_edges_to_use) << endl;

    }
    return 0;
}
