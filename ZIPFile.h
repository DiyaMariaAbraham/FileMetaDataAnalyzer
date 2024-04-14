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
    friend class FileScorer;
public:
    ZIP(const std::string& filename) : File(filename) {
    
    }

    FileType getType() const override {
        return FileType::ZIP;
    }

};

#endif /* ZIPFILE_H */

