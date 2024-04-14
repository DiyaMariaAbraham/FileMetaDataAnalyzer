// ZIPFile.h
#ifndef ZIPFILE_H
#define ZIPFILE_H

#include "File.h"

class ZIP : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
public:
    ZIP(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","504B0304");
    	fileMarkers.insert("EOF","504B0506");
    	fileMarkers.insert("Central Directory File Header","504B0102");
    	fileMarkers.insert("Optional Data Descriptor","504B0708");
    	App = "Archive Manager";
    	magicNumber = "504B0304";
    }

    FileType getType() const override {
        return FileType::ZIP;
    }

};

#endif /* ZIPFILE_H */

