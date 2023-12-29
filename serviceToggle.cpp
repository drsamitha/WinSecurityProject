#include <iostream>
#include <windows.h>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: service_manager <option>" << std::endl;
        std::cout << "Options: --start, --stop" << std::endl;
        return 1;
    }

    std::string option = argv[1];

    // Change service names based on the actual service names
    std::string service1 = "dmwappushsvc";
    std::string service2 = "diagtrack";

    if (option == "--stop") {
        // Stop services
        if (!::ShellExecute(NULL, "runas", "net", ("stop " + service1).c_str(), NULL, SW_HIDE)) {
            std::cerr << "Failed to stop service: " << service1 << std::endl;
            return 1;
        }

        if (!::ShellExecute(NULL, "runas", "net", ("stop " + service2).c_str(), NULL, SW_HIDE)) {
            std::cerr << "Failed to stop service: " << service2 << std::endl;
            return 1;
        }

        std::cout << "Services stopped successfully." << std::endl;
    } else if (option == "--start") {
        // Start services
        if (!::ShellExecute(NULL, "runas", "net", ("start " + service1).c_str(), NULL, SW_HIDE)) {
            std::cerr << "Failed to start service: " << service1 << std::endl;
            return 1;
        }

        if (!::ShellExecute(NULL, "runas", "net", ("start " + service2).c_str(), NULL, SW_HIDE)) {
            std::cerr << "Failed to start service: " << service2 << std::endl;
            return 1;
        }

        std::cout << "Services started successfully." << std::endl;
    } else {
        std::cout << "Invalid option: " << option << std::endl;
        std::cout << "Options: --start, --stop" << std::endl;
        return 1;
    }

    return 0;
}
