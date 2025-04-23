#include <execution>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int main()
{
    vector<int> data = {1, 2, 3, 4, 5};
    double mean = accumulate(data.begin(), data.end(), 0.0) / data.size();
    double sq_sum = accumulate(data.begin(), data.end(), 0.0, [mean](double acc, int val){return acc + (val-mean) * (val-mean);});

    double variance = sq_sum / data.size();
    cout << "ave : " << mean << endl;
    cout << "var : " << variance << endl;

    vector<int> vec(1'000'000); 
    iota(vec.begin(), vec.end(), 0);
    shuffle(vec.begin(), vec.end(), mt19937(random_device{}()));

    auto start = chrono::high_resolution_clock::now();
    sort(execution::par, vec.begin(), vec.end());
    //sort(vec.begin(), vec.end());
    auto end = chrono::high_resolution_clock::now();

    cout << "spend time : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" <<endl;

    return 0;
}
