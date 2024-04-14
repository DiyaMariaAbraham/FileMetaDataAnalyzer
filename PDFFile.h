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
    friend class FileScorer;
public:
    PDF(const std::string& filename) : File(filename) {
    	
    }

    FileType getType() const override {
        return FileType::PDF;
    }

};

#endif /* PDFFILE_H */

