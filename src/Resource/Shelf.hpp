/**
 * @file Shelf.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief ShelfPool
 * @version 0.1
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Global/Definations.hpp"
#include "../Global/TimeManager.hpp"

#include <algorithm>
#include <list>
#include <memory>
#include <ranges>

namespace Shelf {

using std::cout, std::endl;
using std::list;
using std::shared_ptr;

using shelf_t = list<::PackageInfo>;

static constexpr time_t Max_Retention_Time = 2;
static constexpr size_t Big_Lim            = 50;
static constexpr size_t Mid_Lim            = 100;
static constexpr size_t Small_Lim          = 500;

static shared_ptr<shelf_t> big_shelf   = std::make_shared<shelf_t>();
static shared_ptr<shelf_t> mid_shelf   = std::make_shared<shelf_t>();
static shared_ptr<shelf_t> small_shelf = std::make_shared<shelf_t>();

static void remove_outdated() {
    using TimeManager::CurrentTime;

    auto if_not_outdated = [](const ::PackageInfo& info) {
        return CurrentTime - info.ArrivedTime <= Max_Retention_Time;
    };

    auto new_big_shelf   = *big_shelf | std::views::filter(if_not_outdated);
    auto new_mid_shelf   = *mid_shelf | std::views::filter(if_not_outdated);
    auto new_small_shelf = *small_shelf | std::views::filter(if_not_outdated);

    // assign `new_big_shelf` to `*big_shelf`
    big_shelf.reset();
    big_shelf = std::make_shared<shelf_t>(new_big_shelf.begin(), new_big_shelf.end());

    // assign `new_mid_shelf` to `*mid_shelf`
    mid_shelf.reset();
    mid_shelf = std::make_shared<shelf_t>(new_mid_shelf.begin(), new_mid_shelf.end());

    // assign `new_small_shelf` to `*small_shelf`
    small_shelf.reset();
    small_shelf = std::make_shared<shelf_t>(new_small_shelf.begin(), new_small_shelf.end());

    cout << "已移除所有 `过期未取的` 包裹 ";
    cout << "(当前期限为 " << Max_Retention_Time << " 个时间单位)";
    cout << endl;
    cout << endl;
}

static void add_to_big(const ::PackageInfo& info) {
    if (big_shelf->size() < Big_Lim) {
        big_shelf->push_back(info);
    } else {
        cout << "大型货架已满，无法寄存！" << endl;
        cout << endl;
    }
}
static void add_to_mid(const ::PackageInfo& info) {
    if (mid_shelf->size() < Mid_Lim) {
        mid_shelf->push_back(info);
    } else {
        cout << "中型货架已满，无法寄存！" << endl;
        cout << endl;
    }
}
static void add_to_small(const ::PackageInfo& info) {
    if (small_shelf->size() < Small_Lim) {
        small_shelf->push_back(info);
    } else {
        cout << "小型货架已满，无法寄存！" << endl;
        cout << endl;
    }
}

} // namespace Shelf