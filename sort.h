//
// Created by Kotozzavrik on 08.07.2023.
//

#ifndef YADRO2____SORT_H
#define YADRO2____SORT_H

#include <algorithm>
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include "config.hpp"

class sort {
public:

    static void my_merge(std::vector<int32_t>& arr, int32_t left, int32_t right);
    static std::string external_merge ( std::vector<std::string> tapes, config config_);

};


#endif //YADRO2____SORT_H
