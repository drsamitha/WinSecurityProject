#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


// Function to read websites from a file
std::vector<std::string> readWebsites(std::string filename) {
    std::vector<std::string> websites;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        websites.push_back(line);
    }

    file.close();
    return websites;
}

// Function to check if a website is already in the hosts file
bool isWebsiteBlocked(std::string website) {
    std::ifstream hostsFile("C:\\Windows\\System32\\drivers\\etc\\hosts");
    std::string line;

    while (std::getline(hostsFile, line)) {
        std::istringstream iss(line);
        std::string ip, domain;

        if (!(iss >> ip >> domain)) { break; } // error

        if (domain == website) {
            return true;
        }
    }

    return false;
}

// Function to block websites
void blockWebsites(std::vector<std::string> websites) {
    // Check if a backup of the hosts file already exists
    std::ifstream infile("C:\\Windows\\System32\\drivers\\etc\\hosts.bak");
    if (!infile.good()) {
        // Backup the original hosts file
        std::ifstream src("C:\\Windows\\System32\\drivers\\etc\\hosts", std::ios::binary);
        std::ofstream dst("C:\\Windows\\System32\\drivers\\etc\\hosts.bak", std::ios::binary);
        dst << src.rdbuf();
    }

    // Open the hosts file in append mode
    std::ofstream hostsFile;
    hostsFile.open("C:\\Windows\\System32\\drivers\\etc\\hosts", std::ios_base::app);

    // Check if the file is open
    if (hostsFile.is_open()) {
        // Loop through the list of websites
        for (std::string website : websites) {
            // Check if the website is already blocked
            if (!isWebsiteBlocked(website)) {
                // Write to the hosts file
                hostsFile << "0.0.0.0 " << website << "\n";
            }
        }

        // Close the file
        hostsFile.close();
    } else {
        // Print an error message if the file couldn't be opened
        std::cout << "Unable to open hosts file." << std::endl;
    }
}

int main() {
    // Read the list of websites from a file
    std::vector<std::string> websites = readWebsites("domainHost.txt");

    // Call the function to block the websites
    blockWebsites(websites);

    return 0;
}
