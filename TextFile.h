// TextFile.h
#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "File.h"

class Text : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
public:
    Text(const std::string& filename) : File(filename) {
    	App = "gedit";
    	magicNumber = "";
    }
    FileType getType() const override {
        return FileType::Text;
    }

};

#endif /* TEXTFILE_H */

