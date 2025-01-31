#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::streampos binarySearchDate(std::ifstream& file, const std::string& date) {
    std::streampos left = 0;
    file.seekg(0, std::ios::end);
    std::streampos right = file.tellg();
    std::string line;

    while (left < right) {
        std::streampos mid = left + (right - left) / 2;
        file.seekg(mid);

        // Move to the start of the next line
        std::getline(file, line);
        if (file.tellg() == -1) {
            right = mid;
            continue;
        }

        std::getline(file, line);
        if (line.rfind(date, 0) == 0) {
            right = mid;
        } else if (line < date) {
            left = file.tellg();
        } else {
            right = mid;
        }
    }
    return left;
}

void extractLogs(const std::string& logFile, const std::string& date) {
    std::ifstream inputFile(logFile);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open log file." << std::endl;
        return;
    }

    std::string outputDir = "../output";
    if (!fs::exists(outputDir)) {
        fs::create_directory(outputDir);
    }

    std::string outputFile = outputDir + "/output_" + date + ".txt";
    std::ofstream output(outputFile);
    if (!output.is_open()) {
        std::cerr << "Error: Unable to create output file." << std::endl;
        return;
    }

    std::streampos startPos = binarySearchDate(inputFile, date);
    inputFile.seekg(startPos);
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.rfind(date, 0) != 0) {
            break;
        }
        output << line << "\n";
    }

    inputFile.close();
    output.close();
    std::cout << "Logs for " << date << " saved to " << outputFile << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        std::cerr << "Usage: " << argv[0] << " [<log_file>] <YYYY-MM-DD>" << std::endl;
        return 1;
    }

    std::string logFile = (argc == 2) ? "test_logs.log" : argv[1];
    std::string date = (argc == 2) ? argv[1] : argv[2];

    extractLogs(logFile, date);
    return 0;
}
