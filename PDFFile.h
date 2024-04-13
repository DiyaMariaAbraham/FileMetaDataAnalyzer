// PDFFile.h
#ifndef PDFFILE_H
#define PDFFILE_H

#include "File.h"

class PDF : public File {
protected:
	magicNumber = "25504446";
	command = "evince " + filename;
	App = "Document Viewer";
private:
    static Map<std::string, std::string> fileMarkers;
public:
    PDFFile(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","25504446");
    	fileMarkers.insert("EOF","2525454F46");
    }

    FileType getType() const override {
        return FileType::PDF;
    }

};

#endif /* PDFFILE_H */

