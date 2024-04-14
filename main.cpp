// main.cpp
//Including File Headers
#include "File.h"
#include "FileType.h"
#include "PNGFile.h" 
#include "JPGFile.h" 
#include "BMPFile.h" 
#include "MP3File.h" 
#include "MP4File.h" 
#include "ZIPFile.h" 
#include "PDFFile.h"

#include <iostream>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


std::vector<std::string> files;

// Function to check if a file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    return file.good();
}

// Overloaded operator for file filtering
bool operator*(const std::string& filename, bool include) {
    return fileExists(filename) && include;
}

// Variadic template function to filter file paths based on file existence
template <typename... Args>
void filterFiles(Args... filenames) {
    std::vector<std::string> result;

    // Iterate through each filename
    ((filenames * true ? files.push_back(filenames) : void()), ...);

}

    // Base case for recursion
void processArgs() {
    // Base case: Do nothing when there are no more arguments
}

// Recursive function to unpack arguments from vector and pass to variadic function
template<typename T, typename... Args>
void processArgs(const std::vector<T>& vec, Args... args) {
    if (!vec.empty()) {
        // Unpack the first element of the vector and pass it along with remaining arguments
        filterFiles(args..., vec[0]);
        processArgs(std::vector<T>(vec.begin() + 1, vec.end()), args...);
    } else {
        // Base case: If vector is empty, call the base case function
        processArgs();
    }
}

int main(int argc, char *argv[]) {
    // Check if no command-line arguments are provided
    if (argc < 2) {
        // Prompt the user with correct usage instructions
        std::cerr << "Usage: " << argv[0] << " <absolute_file_path1> <absolute_file_path2> ..." << std::endl;
        std::cerr << "Please provide at least one absolute file path as a command-line argument." << std::endl;
        return 1; // Exit with error code 1
    }

    // Convert command-line arguments to vector of strings
    std::vector<std::string> args(argv + 1, argv + argc);

    // Filter the files
    processArgs(args);

    // Display the filtered files
    std::cout << "Filtered files:\n";
    for (const auto& file : files) {
        std::cout << file << std::endl;
    }

    return 0;
}

