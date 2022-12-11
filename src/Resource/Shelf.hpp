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
using std::vector;

using shelf_t = list<::PackageInfo>;

template <class T>
using Rc = shared_ptr<T>;

static constexpr time_t Max_Retention_Time = 2;
static constexpr size_t Big_Lim            = 50;
static constexpr size_t Mid_Lim            = 100;
static constexpr size_t Small_Lim          = 500;

static Rc<shelf_t> big_shelf   = std::make_shared<shelf_t>();
static Rc<shelf_t> mid_shelf   = std::make_shared<shelf_t>();
static Rc<shelf_t> small_shelf = std::make_shared<shelf_t>();

void remove_unpicked_packages() {
    using TimeManager::CurrentTime;
    auto if_outdated = [](const ::PackageInfo& info) {
        return CurrentTime - info.ArrivedTime > Max_Retention_Time;
    };

    auto new_big_shelf = std::make_shared<shelf_t>();
    std::copy_if(
        big_shelf->begin(),
        big_shelf->end(),
        std::back_inserter(*new_big_shelf),
        if_outdated
    );

    auto new_mid_shelf = std::make_shared<shelf_t>();
    std::copy_if(
        mid_shelf->begin(),
        mid_shelf->end(),
        std::back_inserter(*new_mid_shelf),
        if_outdated
    );

    auto new_small_shelf = std::make_shared<shelf_t>();
    std::copy_if(
        small_shelf->begin(),
        small_shelf->end(),
        std::back_inserter(*new_small_shelf),
        if_outdated
    );

    big_shelf.reset();
    big_shelf = new_big_shelf;

    mid_shelf.reset();
    mid_shelf = new_mid_shelf;

    small_shelf.reset();
    small_shelf = new_small_shelf;
}

void add_to_big(const ::PackageInfo& info) {
    if (big_shelf->size() < Big_Lim) {
        big_shelf->push_back(info);
    } else {
        cout << "大型货架已满，无法寄存！" << endl;
        cout << endl;
    }
}
void add_to_mid(const ::PackageInfo& info) {
    if (mid_shelf->size() < Mid_Lim) {
        mid_shelf->push_back(info);
    } else {
        cout << "中型货架已满，无法寄存！" << endl;
        cout << endl;
    }
}
void add_to_small(const ::PackageInfo& info) {
    if (small_shelf->size() < Small_Lim) {
        small_shelf->push_back(info);
    } else {
        cout << "小型货架已满，无法寄存！" << endl;
        cout << endl;
    }
}

} // namespace Shelf