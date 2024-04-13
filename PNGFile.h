// PNGFile.h
#ifndef PNGFILE_H
#define PNGFILE_H

#include "File.h"

class PNG : public File {
protected:
	magicNumber = "89504E470D0A1A0A";
	command = "xdg-open " + filename;
	App = "Image Viewer";
private:
    static Map<std::string, std::string> fileMarkers;
public:
    PNGFile(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","89504E470D0A1A0A");
    	fileMarkers.insert("EOF","49454E44");
    	fileMarkers.insert("IHDR","49484452");
    	fileMarkers.insert("PLTE","504C5445");
    	fileMarkers.insert("PLTE","49444154");
    }

    FileType getType() const override {
        return FileType::PNG;
    }

};

#endif /* PNGFILE_H */

