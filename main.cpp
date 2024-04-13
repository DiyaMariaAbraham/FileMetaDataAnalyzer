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
    // Check if no command-line arguments are provided
    if (argc < 2) {
        // Prompt the user with correct usage instructions
        std::cerr << "Usage: " << argv[0] << " <absolute_file_path1> <absolute_file_path2> ..." << std::endl;
        std::cerr << "Please provide at least one absolute file path as a command-line argument." << std::endl;
        return 1; // Exit with error code 1
    }

    
    
    return 0;
}
