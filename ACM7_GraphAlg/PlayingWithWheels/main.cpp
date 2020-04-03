#include <iostream>
#include <unordered_map>
#include <vector>
#include <array>
#include <limits>
#include <queue>

using namespace std;

constexpr size_t COMBINATIONS = 10000;

uint16_t load_combination();

int64_t get_amount_of_steps(uint16_t initial, uint16_t target, array<bool, COMBINATIONS> &forbidden);


vector<uint16_t> generate_neighbors(uint16_t state);

int main() {
    size_t test_cases{};
    cin >> test_cases;
    for (size_t test_case = 0; test_case < test_cases; ++test_case) {
        uint16_t initial = load_combination();
        uint16_t target = load_combination();

        size_t forbidden_count{};
        cin >> forbidden_count;
        array<bool, COMBINATIONS> forbidden{};
        for(size_t forbidden_idx = 0; forbidden_idx < forbidden_count; forbidden_idx++) {
            auto cur_forbidden = load_combination();
            forbidden[cur_forbidden] = true;
        }

        int64_t step_count = get_amount_of_steps(initial, target, forbidden);
        cout << step_count << endl;
    }

    return 0;
}

int64_t get_amount_of_steps(uint16_t initial, uint16_t target, array<bool, COMBINATIONS> &forbidden) {
    array<bool, COMBINATIONS> visited{};
    vector<int64_t> distance(COMBINATIONS, -1);

    queue<uint16_t> queue;

    distance[initial] = 0;
    visited[initial] = true;
    queue.push(initial);

    while(not queue.empty()) {
        uint16_t current = queue.front();
        queue.pop();
        if (current == target) {
            break;
        }
        int64_t cur_distance = distance[current];
        vector<uint16_t> neighbors = generate_neighbors(current);
        for (auto neighbor : neighbors) {
            if(not forbidden[neighbor] and not visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = cur_distance + 1;
                queue.push(neighbor);
            }
        }
    }

    return distance[target];
}

vector<uint16_t> generate_neighbors(uint16_t state) {
    vector<uint16_t> neighbors;
    neighbors.reserve(8);

    neighbors.push_back((state + 1000) % 10000);
    neighbors.push_back((state + 9000) % 10000);

    uint16_t hundreds_part = state % 1000;
    uint16_t thousands = state - hundreds_part;
    neighbors.push_back(thousands + ((hundreds_part + 100) % 1000));
    neighbors.push_back(thousands + ((hundreds_part + 900) % 1000));

    uint16_t tens_part = state % 100;
    uint16_t hundreds = state - tens_part;
    neighbors.push_back(hundreds + ((tens_part + 10) % 100));
    neighbors.push_back(hundreds + ((tens_part + 90) % 100));

    uint16_t units_part = state % 10;
    uint16_t tens = state - units_part;
    neighbors.push_back(tens + ((units_part + 1) % 10));
    neighbors.push_back(tens + ((units_part + 9) % 10));

    return neighbors;
}

uint16_t load_combination() {
    uint16_t combination{0};
    uint16_t num{};
    cin >> num;
    combination += num * 1000;
    cin >> num;
    combination += num * 100;
    cin >> num;
    combination += num * 10;
    cin >> num;
    combination += num;

    return combination;
}
