#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

bool isNotificationDisplayed = false;



void DisplayNotification(const wchar_t* modifiedFile) {
    // Get the current time
    auto now = std::chrono::system_clock::now();

    // Static variable to store the last time the function was called
    static auto lastCallTime = std::chrono::system_clock::now();

    // Get the difference in seconds between now and the last call time
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastCallTime).count();

    // If the function was called less than 30 seconds ago, return without displaying the notification
    if (duration < 30) {
        // Display the modified file name
        std::wcout << L"File modified: " << modifiedFile << std::endl;

        // Set the flag to indicate that the notification is not being displayed
        isNotificationDisplayed = false;
        return;
    }

    // Display the modified file name
    std::wcout << L"File modified: " << modifiedFile << std::endl;

    // Execute PowerShell script on file modification
    system("powershell -ExecutionPolicy Bypass -File show_notification.ps1");

    // Set the flag to indicate that the notification is not being displayed
    isNotificationDisplayed = false;

    // Update the last call time
    lastCallTime = now;
}

void MonitorCurrentDirectory() {
    // Get the current directory
    wchar_t currentDirectory[MAX_PATH];
    GetCurrentDirectoryW(MAX_PATH, currentDirectory);

    // Display information about the state of the program
    std::wcout << L"Monitoring directory: " << currentDirectory << std::endl;

    // Create a directory handle
    HANDLE hDir = CreateFileW(
        currentDirectory,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
        NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Error opening directory: " << GetLastError() << std::endl;
        return;
    }

    char buffer[4096];
    OVERLAPPED overlapped = { 0 };
    DWORD bytesRead;

    while (true) {
        // Display information about the state of the loop
        std::wcout << L"While loop activated." << std::endl;

        // Start asynchronous directory change notification
        ReadDirectoryChangesW(
            hDir,
            &buffer,
            sizeof(buffer),
            TRUE,
            FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesRead,
            &overlapped,
            NULL
        );

        // Wait for the asynchronous operation to complete
        if (GetOverlappedResult(hDir, &overlapped, &bytesRead, TRUE)) {
            FILE_NOTIFY_INFORMATION* pInfo = (FILE_NOTIFY_INFORMATION*)buffer;

            // Check if a notification is not currently being displayed
            if (!isNotificationDisplayed) {
                while (pInfo) {
                    if (pInfo->Action == FILE_ACTION_MODIFIED) {
                        // Convert UNICODE file name to wide char string
                        wchar_t modifiedFile[MAX_PATH];
                        wmemcpy(modifiedFile, pInfo->FileName, pInfo->FileNameLength / sizeof(wchar_t));
                        modifiedFile[pInfo->FileNameLength / sizeof(wchar_t)] = L'\0';

                        // Set the flag to indicate that a notification is being displayed
                        isNotificationDisplayed = true;

                        // Display the notification
                        DisplayNotification(modifiedFile);
                    }

                    pInfo = pInfo->NextEntryOffset ? (FILE_NOTIFY_INFORMATION*)((char*)pInfo + pInfo->NextEntryOffset) : NULL;
                }

                // Sleep to avoid rapid iterations
                Sleep(1000); // Adjust the sleep time as needed
            }
        } else {
            std::wcerr << L"Error reading directory changes: " << GetLastError() << std::endl;
            break;
        }
    }

    // Display information about the end of the program
    std::wcout << L"Exiting the program." << std::endl;

    // Close the directory handle
    CloseHandle(hDir);
}

int main() {
    MonitorCurrentDirectory();

    return 0;
}
