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

    static constexpr string_view seperator = " ";

    using time_t = TimeManager::time_t;
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
};