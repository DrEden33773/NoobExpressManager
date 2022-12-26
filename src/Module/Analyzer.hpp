/**
 * @file Analyzer.hpp
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
#include <unordered_map>
#include <utility>

namespace Module {

using std::cout, std::endl, std::cin;
using std::string;

class Analyzer {
    void show_all_package_info() {
        cout << "下面将列出所有的货架中所有包裹的信息" << endl;
        cout << endl;
        Shelf::show_all_shelf();
    }

    void show_option() {
        cout << "在 `分析` 模块中，您可以执行如下的操作：" << endl;
        cout << "\t 1. 列出所有的货架中所有包裹的信息" << endl;
        cout << endl;
        cout << ">>> ";
    }
    string get_input() {
        string ret;
        cin >> ret;
        cout << endl;
        return ret;
    }
    void option_selector() {
        while (true) {
            show_option();
            auto input = get_input();
            if (input == "1") {
                show_all_package_info();
                break;
            } else {
                cout << "未实现功能，请重新输入..." << endl;
                cout << endl;
            }
        }
    }

public:
    static void analyze() {
        Analyzer analyzer;
        analyzer.option_selector();
    }
};

} // namespace Module