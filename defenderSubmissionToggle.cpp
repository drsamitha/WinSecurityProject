#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <cstdlib>

void setRegistryValue(HKEY rootKey, const std::string& subKey, const std::string& valueName, DWORD valueType, DWORD valueData) {
    HKEY key;
    LONG result = RegOpenKeyExA(rootKey, subKey.c_str(), 0, KEY_SET_VALUE, &key);

    if (result == ERROR_SUCCESS) {
        result = RegSetValueExA(key, valueName.c_str(), 0, valueType, reinterpret_cast<const BYTE*>(&valueData), sizeof(DWORD));

        if (result != ERROR_SUCCESS) {
            std::cerr << "Failed to set registry value: " << subKey << std::endl;
        }

        RegCloseKey(key);
    }
    else {
        std::cerr << "Failed to open registry key: " << subKey << std::endl;
    }
}

void deleteRegistryValue(HKEY rootKey, const std::string& subKey, const std::string& valueName) {
    HKEY key;
    LONG result = RegOpenKeyExA(rootKey, subKey.c_str(), 0, KEY_SET_VALUE, &key);

    if (result == ERROR_SUCCESS) {
        // Delete the registry value
        result = RegDeleteValueA(key, valueName.c_str());

        if (result != ERROR_SUCCESS) {
            std::cerr << "Failed to delete registry value: " << subKey << std::endl;
        }

        RegCloseKey(key);
    }
    else {
        std::cerr << "Failed to open registry key: " << subKey << std::endl;
    }
}

bool controlService(const std::string& serviceName, const std::string& command) {
    std::string netCommand = "net " + command + " " + serviceName;
    int result = std::system(netCommand.c_str());

    return result == 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ToggleServices.exe --enable/--disable" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    if (option == "--enable") {
        // Enable default settings (delete the registry value)
        deleteRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Spynet", "SubmitSamplesConsent");
        std::cout << "Enabled default settings." << std::endl;

        // Start the NIS service
        controlService("WdNisSvc", "start");
        std::cout << "Started WdNisSvc service." << std::endl;

        // Start the DoSvc service
        controlService("dosvc", "start");
        std::cout << "Started dosvc service." << std::endl;
    }
    else if (option == "--disable") {
        // Disable sample submission
        setRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Spynet", "SubmitSamplesConsent", REG_DWORD, 2);
        std::cout << "Disabled sample submission." << std::endl;

        // Stop the NIS service
        controlService("WdNisSvc", "stop");
        std::cout << "Stopped WdNisSvc service." << std::endl;

        // Stop the DoSvc service
        controlService("dosvc", "stop");
        std::cout << "Stopped dosvc service." << std::endl;
    }
    else {
        std::cerr << "Invalid option. Use --enable or --disable." << std::endl;
        return 1;
    }

    return 0;
}
