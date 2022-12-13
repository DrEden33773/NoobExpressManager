/**
 * @file PackageInfo.hpp
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

#include <compare>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

struct PackageInfo {
    using string      = std::string;
    using string_view = std::string_view;
    using fstream     = std::fstream;
    using ostream     = std::ostream;
    using time_t      = TimeManager::time_t;

    static constexpr string_view seperator          = " ";
    static constexpr time_t      Max_Retention_Time = 2;

    string PackageNumber;
    string Name;
    string PhoneNumber;
    size_t PackageSize = 1;
    time_t DepositTime = 0;

    friend std::strong_ordering operator<=>(
        const PackageInfo& lhs,
        const PackageInfo& rhs
    ) {
        return lhs.PackageNumber <=> rhs.PackageNumber;
    }

    friend fstream& operator<<(
        fstream&           out,
        const PackageInfo& info
    ) {
        out << info.PackageNumber << seperator;
        out << info.Name << seperator;
        out << info.PhoneNumber << seperator;
        out << info.PackageSize << seperator;
        out << info.DepositTime << std::endl;
        return out;
    }
    friend ostream& operator<<(
        ostream&           out,
        const PackageInfo& info
    ) {
        out << info.PackageNumber << seperator;
        out << info.Name << seperator;
        out << info.PhoneNumber << seperator;
        out << info.PackageSize << seperator;
        out << info.DepositTime << std::endl;
        return out;
    }

    static bool if_not_outdated(const PackageInfo& info) {
        using TimeManager::CurrentTime;
        return CurrentTime - info.DepositTime <= Max_Retention_Time;
    }
    [[nodiscard]] bool if_same_name(const string& name) const {
        return Name == name;
    }
    [[nodiscard]] bool if_same_phoneNumber(const string& phoneNumber) const {
        return PhoneNumber == phoneNumber;
    }
    [[nodiscard]] bool if_same_packageNumber(const string& packageNumber) const {
        return PackageNumber == packageNumber;
    }
};