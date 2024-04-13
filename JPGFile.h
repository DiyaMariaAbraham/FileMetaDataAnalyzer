// JPGFile.h
#ifndef JPGFILE_H
#define JPGFILE_H

#include "File.h"

class JPG : public File {
protected:
	magicNumber = "FFD8FF";
	command = "xdg-open " + filename;
	App = "Image Viewer";
private:
    static Map<std::string, std::string> fileMarkers;
public:
    JPGFile(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","FFD8");
    	fileMarkers.insert("EOF","FFD9");
    	fileMarkers.insert("APP12","FFEC");
    	fileMarkers.insert("COM","FFFE");
    }

    FileType getType() const override {
        return FileType::JPG;
    }

};

#endif /* JPGFILE_H */

