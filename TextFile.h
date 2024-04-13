// TextFile.h
#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "File.h"

class Text : public File {
protected:
	magicNumber = "";
	command= "gedit " + filename;
	App = "gedit";
public:
    FileType getType() const override {
        return FileType::Text;
    }

};

#endif /* TEXTFILE_H */

