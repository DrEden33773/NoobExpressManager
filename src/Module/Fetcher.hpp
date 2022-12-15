/**
 * @file Fetcher.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
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
#include <optional>
#include <unordered_map>
#include <utility>

namespace Module {

using std::cout, std::cin, std::endl;
using std::nullopt;
using std::optional;
using std::string;
using TimeManager::time_t;

class Fetcher {
    string phone;
    string packageNum;

private:
    void fetch_one_by_package_num() {
        cout << "请输入包裹号 >>> ";
        cin >> packageNum;

        auto the_fetched = Shelf::fetch_one_by_packageNumber(packageNum);

        if (!the_fetched.first) {
            cout << "未查询到包裹号！没有取出任何包裹！" << endl;
        } else {
            cout << "成功取出包裹！取出的包裹信息如下：" << endl;
            cout << "\t" << *(the_fetched.second) << endl;
        }
        cout << endl;
    }
    void fetch_all_by_phone() {
        cout << "请输入电话号码 >>> ";
        cin >> phone;

        auto all_fetched = Shelf::fetch_all_by_phone(phone);

        if (all_fetched.empty()) {
            cout << "未查询到电话号码！没有取出任何包裹！" << endl;
        } else {
            cout << "成功取出包裹！取出的包裹信息如下：" << endl;
            for (const auto& package : all_fetched) {
                cout << "\t" << package << endl;
            }
        }
        cout << endl;
    }
    void fetch_all_by_package_num() {
        cout << "请输入包裹号 >>> ";
        cin >> packageNum;

        phone            = Shelf::get_phone_by_packageNumber(packageNum);
        auto all_fetched = Shelf::fetch_all_by_phone(phone);

        if (all_fetched.empty()) {
            cout << "未查询到包裹号！没有取出任何包裹！" << endl;
        } else {
            cout << "成功取出包裹！取出的包裹信息如下：" << endl;
            for (const auto& package : all_fetched) {
                cout << "\t" << package << endl;
            }
        }
        cout << endl;
    }

private:
    void input_fetch_mode() {
        cout << "在 `取件` 模块中，您可以通过以下选项，取出 `一个` 或 `所有相关` 包裹" << endl;
        cout << endl;
        cout << "请选择取件模式:" << endl;
        cout << "\t 1. 用电话号码，取出所有相关包裹 " << endl;
        cout << "\t 2. 用包裹号，索引电话号码，取出所有相关包裹 " << endl;
        cout << "\t 3. 只取出包裹号对应的单个包裹 " << endl;
        cout << endl;
        cout << ">>> ";
    }
    string get_input_mode() {
        string ret;
        cin >> ret;
        cout << endl;
        return ret;
    }
    void fetch_mode_selector() {
        while (true) {
            input_fetch_mode();
            auto mode = get_input_mode();
            if (mode == "1") {
                fetch_all_by_phone();
                break;
            } else if (mode == "2") {
                fetch_all_by_package_num();
                break;
            } else if (mode == "3") {
                fetch_one_by_package_num();
                break;
            } else {
                cout << "未实现功能，请重新输入..." << endl;
                cout << endl;
            }
        }
    }

public:
    static void fetch() {
        Fetcher fetcher;
        fetcher.fetch_mode_selector();
    }
};

} // namespace Module