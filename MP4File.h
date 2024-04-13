// MP4File.h
#ifndef MP4FILE_H
#define MP4FILE_H

#include "File.h"

class MP4 : public File {
protected:
	magicNumber = "0000002066747970";
	command = "xdg-open " + filename;
	App = "Default Video Player";
private:
    Map<std::string, std::string> fileMarkers;
public:
    MP4File(const std::string& filename) : File(filename) {
    	fileMarkers.insert("EOF","0000002066747970");
    }

    FileType getType() const override {
        return FileType::MP4;
    }

};

#endif /* MP4FILE_H */

