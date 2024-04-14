// MP3File.h
#ifndef MP3FILE_H
#define MP3FILE_H

#include "File.h"

class MP3 : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
public:
    MP3(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","494433");
    	App = "RhythmBox";
    	magicNumber = "494433";
    }

    FileType getType() const override {
        return FileType::MP3;
    }

};

#endif /* MP3FILE_H */

