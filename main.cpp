// main.cpp
#include <iostream>

//Including File Headers
#include "FileType.h"
#include "File.h"
#include "PNGFile.h" 
#include "JPGFile.h" 
#include "BMPFile.h" 
#include "MP3File.h" 
#include "MP4File.h" 
#include "ZIPFile.h" 
#include "PDFFile.h"

int main(int argc, char *argv[]) {
    // Check if a command-line argument is provided
    if (argc != 2) {
        // Prompt the user with usage instructions
        std::cerr << "Usage: " << argv[0] << " <full_absolute_filepath>" << std::endl;
        std::cerr << "Please provide the full absolute filepath as a command line argument." << std::endl;
        return 1; // Exit with error code 1
    }

    // Extract the filename from the command-line argument
    std::string filename = argv[1];

    // Proceed with further processing using the filename...
    
    return 0;
}
