//
// Created by Kotozzavrik on 08.07.2023.
//

#include <iostream>
#include "sort.h"
#include "yadroException.hpp"

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

std::string sort::external_merge(std::vector<std::string> tapes, config config_) {

    std::srand(static_cast<unsigned>(std::time(0)));
    while (tapes.size() > 1) {
        std::vector<std::string> new_temp_files;
        for (int i = 0; i < tapes.size(); i += 2) {
            std::ifstream file1(tapes[i]);
            std::ifstream file2(tapes[i + 1]);
            std::string newTempFile =
                    config_.get_path() + "\\" + "temp_" + std::to_string(std::rand()%1000) +
                    ".txt";
            std::ofstream tempOutput(newTempFile);
            if (!tempOutput) {
                std::cerr << "File does not exists ";
                throw yadroException(yadroException::ExceptionType::FileNotFound);
            }
            int num1, num2;
            file1 >> num1;
            file2 >> num2;
            while (file1 && file2) {
                if (num1 <= num2) {
                    tempOutput << num1 << " ";
                    file1 >> num1;
                } else {
                    tempOutput << num2 << " ";
                    file2 >> num2;
                }
            }
            while (file1) {
                tempOutput << num1 << " ";
                file1 >> num1;
            }

            while (file2) {
                tempOutput << num2 << " ";
                file2 >> num2;
            }
            file1.close();
            file2.close();
            tempOutput.close();
            new_temp_files.push_back(newTempFile);
        }
        for (const std::string& tempFile : tapes) {
            std::remove(tempFile.c_str());
        }

        tapes = new_temp_files;
    }
    return tapes[0];
}

