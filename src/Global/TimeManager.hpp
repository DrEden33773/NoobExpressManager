/**
 * @file TimeManager.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstddef>
#include <iostream>

namespace TimeManager {

using time_t    = size_t;
using time_type = size_t;
using std::cout, std::endl;

static time_t CurrentTime = 0;

static void update_time() {
    ++CurrentTime;
    cout << "已更新时间为: " << CurrentTime;
    cout << endl;
    cout << endl;
}

static std::string to_string(time_t time) {
    return std::to_string(time);
}

} // namespace TimeManager