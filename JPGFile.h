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
    friend class FileScorer;
public:
    JPG(const std::string& filename) : File(filename) {
   
    }

    FileType getType() const override {
        return FileType::JPG;
    }

};

#endif /* JPGFILE_H */

