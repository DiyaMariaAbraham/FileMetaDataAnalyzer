// PDFFile.h
#ifndef PDFFILE_H
#define PDFFILE_H

#include "File.h"

class PDF : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
public:
    PDF(const std::string& filename) : File(filename) {
    	fileMarkers.insert("SOF","25504446");
    	fileMarkers.insert("EOF","2525454F46");
    	App = "Document Viewer";
    	magicNumber = "25504446";
    }

    FileType getType() const override {
        return FileType::PDF;
    }

};

#endif /* PDFFILE_H */

