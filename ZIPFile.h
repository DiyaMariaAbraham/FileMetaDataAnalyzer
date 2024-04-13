// ZIPFile.h
#ifndef ZIPFILE_H
#define ZIPFILE_H

#include "File.h"

class ZIP : public File {
protected:
	magicNumber = "504B0304";
	command = "xdg-open " + filename;
	App = "Archive Manager";
private:
    Map<std::string, std::string> fileMarkers;
public:
    ZIPFile(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","504B0304");
    	fileMarkers.insert("EOF","504B0506");
    	fileMarkers.insert("Central Directory File Header","504B0102");
    	fileMarkers.insert("Optional Data Descriptor","504B0708");
    }

    FileType getType() const override {
        return FileType::ZIP;
    }

};

#endif /* ZIPFILE_H */

