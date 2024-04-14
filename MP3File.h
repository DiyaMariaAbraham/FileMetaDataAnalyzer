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
    friend class FileScorer;
public:
    MP3(const std::string& filename) : File(filename) {
 
    }

    FileType getType() const override {
        return FileType::MP3;
    }

};

#endif /* MP3FILE_H */

