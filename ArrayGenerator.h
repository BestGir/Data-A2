#pragma once
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

class ArrayGenerator {
  public:
    size_t size_;
    std::vector<int> data_;
    ArrayGenerator() {
        size_ = 0;
    }
    ArrayGenerator(size_t n) {
        data_.resize(n);
        size_ = n;
        for(int i = 0; i < n; i++) {
            data_[i] = rand() % 6000;
        }
    }
    void Sort() {
        std::sort(data_.begin(), data_.end());
    }

    void Reverse() {
        Sort();
        for(int i = 0; i < size_/2; i++) {
            std::swap(data_[i], data_[size_ - i - 1]);
        }
    }

    void AlmostSort() {
        Sort();
        size_t n = size_;
        int cnt = 1;
        while(n > 0) {
            n /= 2;
            cnt += 2;
        }
        for(int i = 0; i < cnt; i++) {
            size_t ind_first = rand() % size_;
            size_t ind_second = rand() % size_;
            std::swap(data_[ind_first], data_[ind_second]);
        }
    }
};
