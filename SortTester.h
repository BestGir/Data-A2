#pragma once
#include <chrono>
#include <iostream>
#include <functional>
#include <vector>
#include "ArrayGenerator.h"

class SortTester{
  public:
    std::vector<ArrayGenerator> random_data;
    std::vector<ArrayGenerator> almost_data;
    std::vector<ArrayGenerator> reverse_data;
    std::vector<long long> random_time;
    std::vector<long long> almost_time;
    std::vector<long long> reverse_time;
    SortTester() {
        for(int i = 500; i <= 10000; i += 100) {
            auto arr = ArrayGenerator(i);
            random_data.push_back(arr);
            arr.AlmostSort();
            almost_data.push_back(arr);
            arr.Reverse();
            reverse_data.push_back(arr);
        }
    }
    long long OneTest(ArrayGenerator &data, std::function<void(std::vector<int>&, int, int)> sortFunc) {
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(data.data_, 0, data.size_ - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }
    void Tests(std::function<void(std::vector<int>&, int, int)> sortFunc) {
        for(int i = 0; i <= 95; i += 1) {
            random_time.push_back(OneTest(random_data[i], sortFunc));
            almost_time.push_back(OneTest(almost_data[i], sortFunc));
            reverse_time.push_back(OneTest(reverse_data[i], sortFunc));
        }
    }
};

SortTester AvgTests(std::function<void(std::vector<int>&, int, int)> sortFunc, int n) {
    std::vector<SortTester> tests(n);
    SortTester ans;
    for(int i = 0; i < n; i++) {
        tests[i].Tests(sortFunc);
    }
    for(int i = 0; i < tests[0].random_time.size(); i++) {
        ans.random_time.push_back(0);
        ans.reverse_time.push_back(0);
        ans.almost_time.push_back(0);
        for(int j = 0; j < n; j++) {
            ans.random_time[i] += tests[j].random_time[i];
            ans.reverse_time[i] += tests[j].reverse_time[i];
            ans.almost_time[i] += tests[j].almost_time[i];
        }
        ans.almost_time[i] /= n;
        ans.random_time[i] /= n;
        ans.reverse_time[i] /= n;
    }
    return ans;
}