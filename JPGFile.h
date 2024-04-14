// JPGFile.h
#ifndef JPGFILE_H
#define JPGFILE_H

#include "File.h"

class JPG : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
public:
    JPG(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","FFD8");
    	fileMarkers.insert("EOF","FFD9");
    	fileMarkers.insert("APP12","FFEC");
    	fileMarkers.insert("COM","FFFE");
    	App = "Image Viewer";
    	magicNumber = "FFD8FF";
    }

    FileType getType() const override {
        return FileType::JPG;
    }

};

#endif /* JPGFILE_H */

