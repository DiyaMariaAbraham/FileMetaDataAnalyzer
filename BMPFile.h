// BMPFile.h
#ifndef BMPFILE_H
#define BMPFILE_H

#include "File.h"

class BMP : public File {
protected:
private:
public:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
    BMP(const std::string& filename) : File(filename) {
    }
	static void initialize(){
    	fileMarkers.insert("SOF","424d");
    	magicNumber = "424d";
    	App = "Image Viewer";
	}
    FileType getType() const override {
        return FileType::BMP;
    }

};

#endif /* BMPFILE_H */

