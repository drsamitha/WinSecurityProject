#include <iostream>
#include <chrono>
#include "filesystem.hpp"
#include <string>
#include <windows.h>

namespace fs = ghc::filesystem;

void copy_file_to_backup(const fs::path& file_path, const fs::path& backup_path) {
    auto last_write_time = fs::last_write_time(file_path);
    auto now = std::chrono::system_clock::now();
    auto age = std::chrono::duration_cast<std::chrono::seconds>(now - last_write_time).count();
    if (age > 60) {
        fs::copy(file_path, backup_path, fs::copy_options::overwrite_existing);
    }
}

void copy_files_to_backup_folder(const fs::path& folder_path) {
    fs::path backup_folder_path = folder_path / "backup";
    if (!fs::exists(backup_folder_path)) {
        fs::create_directory(backup_folder_path);
    }
    else {
        std::string narrow_path = backup_folder_path.string();
        SetFileAttributesA(narrow_path.c_str(), FILE_ATTRIBUTE_HIDDEN);
    }
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            fs::path backup_path = backup_folder_path / entry.path().filename();
            copy_file_to_backup(entry.path(), backup_path);
        }
    }
}

int main() {
    fs::path folder_path = fs::current_path();
    copy_files_to_backup_folder(folder_path);
    return 0;
}
