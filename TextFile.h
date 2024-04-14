// TextFile.h
#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "File.h"

class Text : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
	friend class FileScorer;
public:
    Text(const std::string& filename) : File(filename) {
    	
    }
    FileType getType() const override {
        return FileType::Text;
    }

};

#endif /* TEXTFILE_H */

