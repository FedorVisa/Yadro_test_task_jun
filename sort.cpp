//
// Created by Kotozzavrik on 08.07.2023.
//

#include "sort.h"

void merge(std::vector<int32_t>& arr, int32_t left, int32_t mid, int32_t right) {
    int32_t n1 = mid - left + 1;
    int32_t n2 = right - mid;

    std::vector<int32_t> leftArr(n1);
    std::vector<int32_t> rightArr(n2);

    for (int32_t i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int32_t j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int32_t i = 0;
    int32_t j = 0;
    int32_t k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void sort::my_merge(std::vector<int32_t>& arr, int32_t left, int32_t right) {
    if (left < right) {
        int32_t mid = left + (right - left) / 2;
        my_merge(arr, left, mid);
        my_merge(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

