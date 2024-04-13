// BMPFile.h
#ifndef BMPFILE_H
#define BMPFILE_H

#include "File.h"

class BMP : public File {
protected:
	magicNumber = "424d";
	command = "xdg-open " + filename;
	App = "Image Viewer";
private:
    static Map<std::string, std::string> fileMarkers;
public:
    BMPFile(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","424d");
    }

    FileType getType() const override {
        return FileType::BMP;
    }

};

#endif /* BMPFILE_H */

