/**
 * @file FileManager.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace FileManager {

namespace fs = std::filesystem;

namespace Dir {
    /* root */
    static const fs::path Root = "Files";
} // namespace Path

namespace Filename {
    static const fs::path ActionLog = Dir::Root / "action_log.txt";
    static const fs::path ShelfLog  = Dir::Root / "shelf_log.txt";
} // namespace Filename

/* all_path in a vec */
static const std::vector<fs::path> all_path {
    Dir::Root,
};

static void create_all_dir() {
    std::for_each(
        all_path.begin(),
        all_path.end(),
        [](const fs::path& curr) {
            if (!fs::exists(curr)) {
                try {
                    fs::create_directories(curr);
                } catch (fs::filesystem_error& e) {
                    std::cout << "Could not create directory, because: " << e.what() << std::endl;
                }
            }
        }
    );
}
static void check_all_dir_existence() {
    std::for_each(
        all_path.begin(),
        all_path.end(),
        [](const fs::path& curr) {
            if (!fs::exists(curr)) {
                throw std::runtime_error("A directory is NOT exist!");
            }
        }
    );
}

static void dir_init() {
    create_all_dir();
    check_all_dir_existence();
    std::cout << "Dir_Init Succeeded!" << std::endl;
    std::cout << std::endl;
}
static void log_file_init() {
    /// @attention this will clean `detail.txt` during each run

    using std::cout;
    using std::endl;
    using std::fstream;

    fstream action_file;
    action_file.open(Filename::ActionLog, fstream::out | fstream::trunc);
    if (!action_file.is_open()) {
        throw std::runtime_error("Cannot create `action_log.txt`!");
    }
    action_file.close();
    cout << "Successfully => Init `action_log.txt`" << endl;
    cout << endl;

    fstream shelf_file;
    shelf_file.open(Filename::ShelfLog, fstream::out | fstream::trunc);
    if (!shelf_file.is_open()) {
        throw std::runtime_error("Cannot create `shelf_log.txt`!");
    }
    shelf_file.close();
    cout << "Successfully => Init `shelf_log.txt`" << endl;
    cout << endl;
}
static void init_all() {
    dir_init();
    log_file_init();
}

} // namespace FileManager