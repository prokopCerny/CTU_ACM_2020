#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int32_t max_len_of_train(vector<uint64_t> &cars);

int main() {
    ios_base::sync_with_stdio(false);
    size_t cases{0};
    cin >> cases;
    for (size_t test_case = 0; test_case < cases; test_case++) {
        uint16_t number_of_cars{};
        cin >> number_of_cars;
        vector<uint64_t> cars(number_of_cars);
        for (size_t car = 0; car < number_of_cars; car++) {
            uint64_t weight{};
            cin >> weight;
            cars[car] = weight;
        }

        cout << max_len_of_train(cars) << endl;
    }
    return 0;
}

int32_t max_len_of_train(vector<uint64_t> &cars) {
    size_t N = cars.size();
    vector<int32_t> lis(N, 1);
    vector<int32_t> lds(N, 1);

    for (int64_t i = N-1; i >= 0; i--) {
        for (size_t j = i+1; j < N; ++j) {
            if (cars[j] > cars[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }

    for (int64_t i = N-1; i >= 0; i--) {
        for (size_t j = i+1; j < N; ++j) {
            if (cars[j] < cars[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }

    int32_t max_len{0};
    for(size_t i = 0; i < N; ++i) {
        max_len = max(max_len, (lis[i] + lds[i] - 1));
    }

    return max_len;
}
