// File.h
#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <cstdlib>
#include "map_mimic.cpp" // Including custom map implementation

// Forward declaration of FileType
enum class FileType;

class File {
protected:
    static std::string magicNumber;
    std::string filename;
    static std::string App;
    std::string command;
    size_t size;

public:
    File(const std::string& filename) : filename(filename){
    	std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            size = file.tellg(); // Get the current position, which is the file size
            file.close();
        } else {
            // Handle error if the file cannot be opened
            throw std::runtime_error("Unable to open file: " + filename);
        }
    }

    virtual FileType getType() const = 0;
    virtual void openApplication() const{
    	std::system(command.c_str());
    }

    size_t getSize() const { return size; }

};

#endif /* FILE_H */
