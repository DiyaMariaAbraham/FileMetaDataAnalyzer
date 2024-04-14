// MP4File.h
#ifndef MP4FILE_H
#define MP4FILE_H

#include "File.h"

class MP4 : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
public:
    MP4(const std::string& filename) : File(filename) {
    	fileMarkers.insert("EOF","0000002066747970");
    	App = "Default Video Player";
    	magicNumber = "0000002066747970";
    }

    FileType getType() const override {
        return FileType::MP4;
    }

};

#endif /* MP4FILE_H */

