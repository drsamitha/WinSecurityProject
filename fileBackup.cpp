#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

void CopyFileToTemp(std::string filePath) {
    FILE* tempFile = std::tmpfile();
    if (tempFile == nullptr) {
        std::cout << "Failed to create temporary file.\n\n";
        return;
    }

    std::ifstream src(filePath, std::ios::binary);
    char buffer[4096];
    while (src.read(buffer, sizeof(buffer)))
        fwrite(buffer, 1, src.gcount(), tempFile);

    std::cout << "Copied file: " << filePath << " to a temporary file.\n\n";

    // Close the temporary file. The file is automatically deleted when the program exits or when the file is closed.
    std::fclose(tempFile);
}

int main() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    std::string currentDir = std::string(buffer).substr(0, pos);

    std::cout << "Monitoring directory: " << currentDir << "\n\n";

    HANDLE hDir = CreateFile(currentDir.c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                              NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

    if (hDir == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to open directory.\n\n";
        return 1;
    }

    FILE_NOTIFY_INFORMATION Buffer[1024];
    DWORD BytesReturned;

    while (true) {
        if ( ReadDirectoryChangesW(hDir, &Buffer, sizeof(Buffer), TRUE, FILE_NOTIFY_CHANGE_LAST_ACCESS, &BytesReturned, NULL, NULL) ) {
            FILE_NOTIFY_INFORMATION* fni = (FILE_NOTIFY_INFORMATION*)&Buffer;
            if (fni->Action == FILE_ACTION_MODIFIED) {
                std::wstring fileNameW(fni->FileName, fni->FileNameLength / sizeof(wchar_t));
                std::string fileName(fileNameW.begin(), fileNameW.end());
                std::string fullPath = currentDir + "\\" + fileName;

                // Check if the modified file is a regular file and not a directory
                DWORD attributes = GetFileAttributes(fullPath.c_str());
                if (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    std::cout << "File read: " << fileName << "\n\n";
                    CopyFileToTemp(fullPath);
                }
            }
        }
    }

    CloseHandle(hDir);
    return 0;
}
