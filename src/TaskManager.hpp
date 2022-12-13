/**
 * @file TaskManager.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "Global/TimeManager.hpp"
#include "Module/Depositor.hpp"
#include "Resource/Shelf.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace Tasks {

using std::cout, std::cin, std::endl;
using std::string;

enum class task_t : unsigned short {
    deposit,     /* store a package */
    query,       /* query packages by info */
    fetch,       /* pick a package */
    analyze,     /* analyze delivery data */
    time_update, /* update the time (date) */
    exit,        /* exit the program */
    unknown,     /* unknown task */
};

void show_task_info() {
    cout << "请选择你要执行的任务:" << endl;

    cout << "\t 1. 存放包裹 " << endl;
    cout << "\t 2. 查询包裹 " << endl;
    cout << "\t 3. 取出包裹 " << endl;
    cout << "\t 4. 数据分析 " << endl;
    cout << "\t 5. 更新日期 " << endl;
    cout << "\t 6. 退出程序 " << endl;
    cout << endl;

    cout << ">>> ";
}

string get_input() {
    string ret;
    cin >> ret;
    return ret;
}

void select_task() {
    while (true) {
        show_task_info();
        auto input = get_input();
        cout << endl;
        if (input == "1") {
            Module::Depositor::deposit();
        } else if (input == "2") {
            // TODO(eden): query
        } else if (input == "3") {
            // TODO(eden): fetch
        } else if (input == "4") {
            // TODO(eden): analyze
        } else if (input == "5") {
            TimeManager::update_time();
            Shelf::remove_outdated();
        } else if (input == "6") {
            cout << "谢谢使用..." << endl;
            cout << endl;
            exit(0);
        } else {
            cout << "功能暂未开发，请重新输入..." << endl;
            cout << endl;
        }
    }
};

} // namespace Tasks