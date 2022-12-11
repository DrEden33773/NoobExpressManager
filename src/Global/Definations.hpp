/**
 * @file Definations.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "TimeManager.hpp"
#include <string>

struct PackageInfo {
    using string = std::string;
    using time_t = TimeManager::time_t;
    string PackageNumber;
    string Name;
    string PhoneNumber;
    size_t PackageType = 1;
    time_t ArrivedTime = 0;
};