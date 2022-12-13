/**
 * @file Depositor.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Global/Definations.hpp"
#include "../Global/TimeManager.hpp"
#include "../Resource/Shelf.hpp"

#include <cstdlib>
#include <unordered_map>
#include <utility>

namespace Module {

using std::cout, std::cin, std::endl;
using std::string;
using std::unordered_map;
using TimeManager::time_t;

class Depositor {
    /* input information */
    string name        = "李田所";
    string phoneNumber = "11451419810";
    size_t packageSize = 1;
    time_t depositDate = TimeManager::CurrentTime;

    /* generated information */
    string packageNumber {};

    /* if successfully deposited a package */
    bool if_successfully_deposited = false;

    /* information-validness-table */
    unordered_map<string, bool> info_validness_map {
        { "手机号", true },
        { "包裹大小", true },
        { "寄存日期", true },
    };
    void check_phoneNumber_validness() {
        static constexpr size_t phoneNumber_len = 11;
        if (phoneNumber.size() != phoneNumber_len) {
            info_validness_map["手机号"] = false;
        }
    }
    void check_packageSize_validness() {
        if (packageSize > 3 || packageSize < 1) {
            info_validness_map["包裹大小"] = false;
        }
    }
    void check_depositDate_validness() {
        if (depositDate < TimeManager::CurrentTime) {
            info_validness_map["寄存日期"] = false;
        }
    }

private:
    /**
     * @brief generate the package number =>
     *      包裹类型 - `手机号后四位 + 日期 + 三位随机数`
     */
    void generate_packageNumber() {
        static constexpr size_t phoneNumber_len = 11;
        static constexpr size_t rand_len        = 3;
        static constexpr size_t DEX_UNIT        = 10;
        packageNumber.clear();
        srand(time(nullptr));
        packageNumber += std::to_string(packageSize);
        packageNumber += "-";
        packageNumber += phoneNumber.substr(phoneNumber_len - 4, 4);
        packageNumber += TimeManager::to_string(depositDate);
        for (size_t i = 0; i < rand_len; ++i) {
            packageNumber += std::to_string(rand() % DEX_UNIT);
        }
    }

    Depositor() = default;

    void set_name(const string& name) {
        this->name = name;
    }
    void set_phoneNumber(const string& phoneNumber) {
        this->phoneNumber = phoneNumber;
        check_phoneNumber_validness();
    }
    void set_packageSize(size_t packageSize) {
        this->packageSize = packageSize;
        check_packageSize_validness();
    }
    void set_depositDate(time_t depositDate) {
        this->depositDate = depositDate;
        check_depositDate_validness();
    }
    bool is_valid() {
        for (const auto& [key, value] : info_validness_map) {
            if (!value) {
                return false;
            }
        }
        return true;
    }
    void show_invalid_info() {
        cout << "您的输入中，存在以下几条无效信息: " << endl;
        for (const auto& [key, value] : info_validness_map) {
            if (!value) {
                cout << "\t" << key << " 无效" << endl;
            }
        }
        cout << "请重新输入..." << endl;
        cout << endl;

        // clear original input
        name.clear();
        phoneNumber.clear();
        packageSize = 1;
    }
    void input() {
        cout << "当前日期为: " << TimeManager::CurrentTime << endl;
        cout << "系统默认您在今天寄存包裹" << endl;
        cout << endl;
        string temp_name;
        string temp_phoneNumber;
        string temp_packageSize;
        cout << "请输入寄件人姓名: ";
        cin >> temp_name;
        cout << "请输入寄件人手机号 (11位): ";
        cin >> temp_phoneNumber;
        cout << "请输入包裹大小 (1-小, 2-中, 3-大): ";
        cin >> temp_packageSize;
        set_name(temp_name);
        set_phoneNumber(temp_phoneNumber);
        set_packageSize(std::stoi(temp_packageSize));
        cout << endl;
    }
    void give_info() {
        while (true) {
            input();
            if (is_valid()) {
                break;
            } else {
                show_invalid_info();
            }
        }
    }
    void show_packageNumber() {
        if (if_successfully_deposited) {
            cout << "您的包裹编号为: " << packageNumber << ", 请牢记" << endl;
            cout << endl;
        }
    }
    void try_to_store() {
        cout << "下面尝试为您寄存包裹..." << endl;
        cout << endl;

        ::PackageInfo toDeposit {
            .PackageNumber = packageNumber,
            .Name          = name,
            .PhoneNumber   = phoneNumber,
            .PackageSize   = packageSize,
            .DepositTime   = depositDate,
        };

        if_successfully_deposited = Shelf::add_package(toDeposit);
    }

public:
    static void deposit() {
        Depositor depositor;
        depositor.give_info();
        depositor.generate_packageNumber();
        depositor.try_to_store();
        depositor.show_packageNumber();
    }
};

} // namespace Module