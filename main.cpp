// main.cpp


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "map_mimic.cpp" // Including custom map implementation

// Forward declaration for FileScorer class
class FileScorer;

enum class FileType {
    Unknown,
    Text,
    PNG,
    JPG,
    BMP,
    MP3,
    MP4,
    ZIP,
    PDF
};

class File {
private:
protected:
	std::string filename;
    std::string command;
    size_t size;

public:
    File(const std::string& filename) : filename(filename){
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (file.is_open()) {
        	command = "xdg-open "+filename;
            size = file.tellg(); // Get the current position, which is the file size
            file.close();
        } else {
            // Handle error if the file cannot be opened
            throw std::runtime_error("Unable to retrieve file size: " + filename);
        }
    }

    virtual FileType getType() const = 0;
    virtual void openApplication() const {
        std::system(command.c_str());
    }

    size_t getSize() const { return size; }

};


class BMP : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
    friend class FileScorer;
public:
    BMP(const std::string& filename) : File(filename) {
    }
    static void initialize(){
    	BMP::magicNumber = "424d";
    	App = "Image Viewer";
	fileMarkers.insert("SOF","424d");
    }
    FileType getType() const override {
        return FileType::BMP;
    }

};

std::string BMP::magicNumber;
std::string BMP::App;
Map<std::string, std::string> BMP::fileMarkers;


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
    static void initialize(){
	fileMarkers.insert("SOF","FFD8");
  	fileMarkers.insert("EOF","FFD9");

    	fileMarkers.insert("APP12","FFEC");

    	fileMarkers.insert("COM","FFFE");

    	App = "Image Viewer";
    	magicNumber = "FFD8FF";
    }
    FileType getType() const override {
        return FileType::JPG;
    }

};

std::string JPG::magicNumber;
std::string JPG::App;
Map<std::string, std::string> JPG::fileMarkers;


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
    static void initialize(){
    	fileMarkers.insert("SOF","494433");

    	App = "RhythmBox";

    	magicNumber = "494433";
	
    }
    FileType getType() const override {
        return FileType::MP3;
    }

};
std::string MP3::magicNumber;
std::string MP3::App;
Map<std::string, std::string> MP3::fileMarkers;




class MP4 : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
    static Map<std::string, std::string> fileMarkers;
    friend class FileScorer;
public:
    MP4(const std::string& filename) : File(filename) {
    	
    }
    static void initialize(){
    	fileMarkers.insert("EOF","0000002066747970");

    	App = "Default Video Player";

    	magicNumber = "0000002066747970";
	
    }
    FileType getType() const override {
        return FileType::MP4;
    }

};
std::string MP4::magicNumber;
std::string MP4::App;
Map<std::string, std::string> MP4::fileMarkers;

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
    static void initialize(){
    	fileMarkers.insert("SOF","25504446");

    	fileMarkers.insert("EOF","2525454F46");

    	App = "Document Viewer";

    	magicNumber = "25504446";
	
    }
    FileType getType() const override {
        return FileType::PDF;
    }

};
std::string PDF::magicNumber;
std::string PDF::App;
Map<std::string, std::string> PDF::fileMarkers;


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
    static void initialize(){
    	fileMarkers.insert("SOF","89504E470D0A1A0A");

    	fileMarkers.insert("EOF","49454E44");

    	fileMarkers.insert("IHDR","49484452");

    	fileMarkers.insert("PLTE","504C5445");

    	fileMarkers.insert("PLTE","49444154");

    	App = "Image Viewer";

    	magicNumber = "89504E470D0A1A0A";
	
    }
    FileType getType() const override {
        return FileType::PNG;
    }
};
std::string PNG::magicNumber;
std::string PNG::App;
Map<std::string, std::string> PNG::fileMarkers;

class Text : public File {
protected:
private:
	static std::string magicNumber;
	static std::string App;
	friend class FileScorer;
public:
    Text(const std::string& filename) : File(filename) {
    	
    }
    static void initialize(){
    	Text::App = "gedit";

    	Text::magicNumber = "";
	
    }
    FileType getType() const override {
        return FileType::Text;
    }

};
std::string Text::magicNumber;
std::string Text::App;

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
    static void initialize(){
    	ZIP::fileMarkers.insert("SOF","504B0304");

    	ZIP::fileMarkers.insert("EOF","504B0506");

    	ZIP::fileMarkers.insert("Central Directory File Header","504B0102");

    	ZIP::fileMarkers.insert("Optional Data Descriptor","504B0708");

    	ZIP::App = "Archive Manager";

    	ZIP::magicNumber = "504B0304";
	
    }
    FileType getType() const override {
        return FileType::ZIP;
    }

};
std::string ZIP::magicNumber;
std::string ZIP::App;
Map<std::string, std::string> ZIP::fileMarkers;


std::vector<std::string> files;

class FileScorer{
public:
	static void initializer(){
	BMP::initialize();
	JPG::initialize();
    	MP3::initialize();
    	MP4::initialize();
    	PDF::initialize();
	PNG::initialize();
    	Text::initialize();
	ZIP::initialize();
	}
	
};

// Function to check if a file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    return file.good();
}

// Overloaded operator for file filtering
bool operator*(const std::string& filename, bool include) {
    return fileExists(filename) && include;
}

// Variadic template function to filter file paths based on file existence
template <typename... Args>
void filterFiles(Args... filenames) {
    std::vector<std::string> result;

    // Iterate through each filename
    ((filenames * true ? files.push_back(filenames) : void()), ...);

}

    // Base case for recursion
void processArgs() {
    // Base case: Do nothing when there are no more arguments
}

// Recursive function to unpack arguments from vector and pass to variadic function
template<typename T, typename... Args>
void processArgs(const std::vector<T>& vec, Args... args) {
    if (!vec.empty()) {
        // Unpack the first element of the vector and pass it along with remaining arguments
        filterFiles(args..., vec[0]);
        processArgs(std::vector<T>(vec.begin() + 1, vec.end()), args...);
    } else {
        // Base case: If vector is empty, call the base case function
        processArgs();
    }
}

int main(int argc, char *argv[]) {

	//Static Member Initialization:
	FileScorer::initializer();
    // Check if no command-line arguments are provided
    if (argc < 2) {
        // Prompt the user with correct usage instructions
        std::cerr << "Usage: " << argv[0] << " <absolute_file_path1> <absolute_file_path2> ..." << std::endl;
        std::cerr << "Please provide at least one absolute file path as a command-line argument." << std::endl;
        return 1; // Exit with error code 1
    }

    // Convert command-line arguments to vector of strings
    std::vector<std::string> args(argv + 1, argv + argc);

    // Filter the files
    processArgs(args);


    return 0;
}

