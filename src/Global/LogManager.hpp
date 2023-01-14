/**
 * @file LogManager.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../Resource/Shelf.hpp"
#include "FileManager.hpp"
#include "PackageInfo.hpp"

namespace LogManager {

using std::fstream;
using std::string;
using std::string_view;

static constexpr string_view BIG_SHELF = "大型货架：";
static constexpr string_view MID_SHELF = "中型货架：";
static constexpr string_view SML_SHELF = "小型货架：";

static void sync_shelf_log() {
    fstream shelf_file;
    shelf_file.open(FileManager::Filename::ShelfLog, fstream::out);
    if (!shelf_file.is_open()) {
        throw std::runtime_error("无法打开货架日志文件");
    }

    // 1. big_shelf
    shelf_file << BIG_SHELF << "\n";
    shelf_file << "\n";
    shelf_file << "\t" << PackageInfo::identifier << "\n";
    for (const auto& package : *Shelf::big_shelf) {
        shelf_file << "\t" << package << "\n";
    }
    shelf_file << "\n";

    // 2. mid_shelf
    shelf_file << MID_SHELF << "\n";
    shelf_file << "\n";
    shelf_file << "\t" << PackageInfo::identifier << "\n";
    for (const auto& package : *Shelf::mid_shelf) {
        shelf_file << "\t" << package << "\n";
    }
    shelf_file << "\n";

    // 3. small_shelf
    shelf_file << SML_SHELF << "\n";
    shelf_file << "\n";
    shelf_file << "\t" << PackageInfo::identifier << "\n";
    for (const auto& package : *Shelf::small_shelf) {
        shelf_file << "\t" << package << "\n";
    }
    shelf_file << "\n";

    shelf_file.close();
}

} // namespace LogManager