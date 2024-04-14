// PNGFile.h
#ifndef PNGFILE_H
#define PNGFILE_H

#include "File.h"

class PNG : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
    friend class FileScorer;
public:
    PNG(const std::string& filename) : File(filename) {
    	
    }

    FileType getType() const override {
        return FileType::PNG;
    }

};

#endif /* PNGFILE_H */

