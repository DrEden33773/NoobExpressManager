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

#include "../Global/PackageInfo.hpp"
#include "../Global/TimeManager.hpp"

#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <ranges>

namespace Shelf {

using std::cout, std::endl;
using std::list;
using std::shared_ptr;
using std::string;
using std::unordered_map;

using shelf_t = list<::PackageInfo>;

static constexpr size_t Big_Lim   = 50;
static constexpr size_t Mid_Lim   = 100;
static constexpr size_t Small_Lim = 500;

static shared_ptr<shelf_t> big_shelf   = std::make_shared<shelf_t>();
static shared_ptr<shelf_t> mid_shelf   = std::make_shared<shelf_t>();
static shared_ptr<shelf_t> small_shelf = std::make_shared<shelf_t>();

static void remove_outdated() {
    // filt
    auto new_big_shelf = *big_shelf
        | std::views::filter(PackageInfo::if_not_outdated);
    auto new_mid_shelf = *mid_shelf
        | std::views::filter(PackageInfo::if_not_outdated);
    auto new_small_shelf = *small_shelf
        | std::views::filter(PackageInfo::if_not_outdated);

    // assign `new_big_shelf` to `*big_shelf`
    big_shelf.reset();
    big_shelf = std::make_shared<shelf_t>(
        new_big_shelf.begin(),
        new_big_shelf.end()
    );

    // assign `new_mid_shelf` to `*mid_shelf`
    mid_shelf.reset();
    mid_shelf = std::make_shared<shelf_t>(
        new_mid_shelf.begin(),
        new_mid_shelf.end()
    );

    // assign `new_small_shelf` to `*small_shelf`
    small_shelf.reset();
    small_shelf = std::make_shared<shelf_t>(
        new_small_shelf.begin(),
        new_small_shelf.end()
    );

    cout << "已移除所有 `过期未取的` 包裹 ";
    cout << "(当前期限为 " << PackageInfo::Max_Retention_Time << " 个时间单位)";
    cout << endl;
    cout << endl;
}

static auto add_to_big(const ::PackageInfo& info) {
    if (big_shelf->size() < Big_Lim) {
        auto it = std::lower_bound(
            big_shelf->begin(),
            big_shelf->end(),
            info
        );
        big_shelf->insert(it, info);
        cout << "已将包裹 " << info.PackageNumber << " 寄存到大型货架" << endl;
        cout << endl;
        return true;
    } else {
        cout << "大型货架已满，无法寄存！本次寄存失败，请选择其他尺寸！" << endl;
        cout << endl;
        return false;
    }
    return false;
}
static auto add_to_mid(const ::PackageInfo& info) {
    if (mid_shelf->size() < Mid_Lim) {
        auto it = std::lower_bound(
            mid_shelf->begin(),
            mid_shelf->end(),
            info
        );
        mid_shelf->insert(it, info);
        cout << "已将包裹 " << info.PackageNumber << " 寄存到中型货架" << endl;
        cout << endl;
        return true;
    } else {
        cout << "中型货架已满，无法寄存！本次寄存失败，请选择其他尺寸！" << endl;
        cout << endl;
        return false;
    }
    return false;
}
static auto add_to_small(const ::PackageInfo& info) {
    if (small_shelf->size() < Small_Lim) {
        auto it = std::lower_bound(
            small_shelf->begin(),
            small_shelf->end(),
            info
        );
        small_shelf->insert(it, info);
        cout << "已将包裹 " << info.PackageNumber << " 寄存到小型货架" << endl;
        cout << endl;
        return true;
    } else {
        cout << "小型货架已满，无法寄存！本次寄存失败，请选择其他尺寸！" << endl;
        cout << endl;
        return false;
    }
    return false;
}
static auto add_package(const ::PackageInfo& info) {
    bool if_success = true;
    switch (info.PackageSize) {
    case 3:
        if_success = add_to_big(info);
        break;
    case 2:
        if_success = add_to_mid(info);
        break;
    case 1:
        if_success = add_to_small(info);
        break;
    }
    return if_success;
}

static auto merge_satisfied_phoneNumber(const string& phoneNumber) {
    auto if_same_PhoneNumber =
        [&phoneNumber](const ::PackageInfo& info) {
            return info.if_same_name(phoneNumber);
        };

    auto new_big_shelf = *big_shelf
        | std::views::filter(if_same_PhoneNumber);
    auto new_mid_shelf = *mid_shelf
        | std::views::filter(if_same_PhoneNumber);
    auto new_small_shelf = *small_shelf
        | std::views::filter(if_same_PhoneNumber);

    // merge
    auto new_shelf = shelf_t(
        new_big_shelf.begin(),
        new_big_shelf.end()
    );
    new_shelf.insert(
        new_shelf.end(),
        new_mid_shelf.begin(),
        new_mid_shelf.end()
    );
    new_shelf.insert(
        new_shelf.end(),
        new_small_shelf.begin(),
        new_small_shelf.end()
    );

    // return
    return new_shelf;
}
static auto merge_satisfied_name(const string& name) {
    auto if_same_name =
        [&name](const ::PackageInfo& info) {
            return info.if_same_name(name);
        };

    auto new_big_shelf = *big_shelf
        | std::views::filter(if_same_name);
    auto new_mid_shelf = *mid_shelf
        | std::views::filter(if_same_name);
    auto new_small_shelf = *small_shelf
        | std::views::filter(if_same_name);

    // merge
    auto new_shelf = shelf_t(
        new_big_shelf.begin(),
        new_big_shelf.end()
    );
    new_shelf.insert(
        new_shelf.end(),
        new_mid_shelf.begin(),
        new_mid_shelf.end()
    );
    new_shelf.insert(
        new_shelf.end(),
        new_small_shelf.begin(),
        new_small_shelf.end()
    );

    // return
    return new_shelf;
}
static auto get_name_by_packageNumber(const string& packageNumToQuery) {
    using it_t           = decltype(big_shelf->begin());
    using shelf_it_map_t = unordered_map<shared_ptr<shelf_t>, it_t>;

    shelf_it_map_t shelf_it_map {
        { big_shelf, big_shelf->begin() },
        { mid_shelf, mid_shelf->begin() },
        { small_shelf, small_shelf->begin() },
    };
    string name;

    for (auto& [shelf, it] : shelf_it_map) {
        it = std::find_if(
            it,
            shelf->end(),
            [&packageNumToQuery](const ::PackageInfo& info) {
                return info.if_same_packageNumber(packageNumToQuery);
            }
        );
        if (it != shelf->end()) {
            name = it->Name;
            break;
        }
    }
    return name;
}

} // namespace Shelf