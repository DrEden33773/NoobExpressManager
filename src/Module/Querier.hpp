/**
 * @file Querier.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief a set of `query functions`
 * @version 0.1
 * @date 2022-12-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Global/PackageInfo.hpp"
#include "../Global/TimeManager.hpp"
#include "../Resource/Shelf.hpp"

#include <cstdlib>
#include <functional>
#include <unordered_map>
#include <utility>

namespace Module {

using std::cout, std::cin, std::endl;
using std::string;
using std::unordered_map;
using TimeManager::time_t;

class Querier {
    string nameToQuery;
    string phoneToQuery;
    string packageNumToQuery;

private:
    void input_query_mode() {
        cout << "在 `查询` 模块中，您可以通过以下选项，查询到对应姓名的所有包裹信息" << endl;
        cout << endl;
        cout << "请选择查询方式:" << endl;
        cout << "\t 1. 按姓名查询 " << endl;
        cout << "\t 2. 按电话查询 " << endl;
        cout << "\t 3. 按包裹号查询 " << endl;
        cout << endl;
        cout << ">>> ";
    }
    string get_input_mode() {
        string ret;
        cin >> ret;
        cout << endl;
        return ret;
    }
    void query_mode_selector() {
        while (true) {
            input_query_mode();
            auto input = get_input_mode();
            if (input == "1") {
                query_by_name();
                break;
            } else if (input == "2") {
                query_by_phone();
                break;
            } else if (input == "3") {
                query_by_package_num();
                break;
            } else {
                cout << "未实现功能，请重新输入..." << endl;
                cout << endl;
            }
        }
    }

private:
    void query_by_name() {
        cout << "请输入姓名 >>> ";
        cin >> nameToQuery;
        auto satisfied = Shelf ::merge_satisfied_name(nameToQuery);

        cout << endl;

        if (satisfied.empty()) {
            cout << "未找到对应姓名的包裹" << endl;
        } else {
            cout << "找到如下包裹:" << endl;
            for (const auto& package : satisfied) {
                cout << "\t" << package << endl;
            }
        }
        cout << endl;
    }
    void query_by_phone() {
        cout << "请输入电话 >>> ";
        cin >> phoneToQuery;
        auto satisfied = Shelf::merge_satisfied_phoneNumber(phoneToQuery);

        cout << endl;

        if (satisfied.empty()) {
            cout << "未找到对应电话的包裹" << endl;
        } else {
            cout << "找到如下包裹:" << endl;
            for (const auto& package : satisfied) {
                cout << "\t" << package << endl;
            }
        }
        cout << endl;
    }
    void query_by_package_num() {
        cout << "请输入包裹号 >>> ";
        cin >> packageNumToQuery;
        auto matched_name = Shelf::get_name_by_packageNumber(packageNumToQuery);
        auto satisfied    = Shelf::merge_satisfied_name(matched_name);

        cout << endl;

        if (satisfied.empty()) {
            cout << "未找到包裹号对应的取件人的包裹" << endl;
        } else {
            cout << "找到如下包裹:" << endl;
            for (const auto& package : satisfied) {
                cout << "\t" << package << endl;
            }
        }
        cout << endl;
    }

public:
    static void query() {
        Querier querier;
        querier.query_mode_selector();
    }
};

} // namespace Module