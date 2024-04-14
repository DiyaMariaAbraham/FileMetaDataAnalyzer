// main.cpp

#include <sstream>
#include <type_traits>
#include <iomanip>
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
    PDF,
    Count // Special enum member to represent the count of file types
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
            std::cout << "File Size:" << size << "(in bytes)" << std::endl;
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
    template<typename T, typename>
    friend class FileProcessor;
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
    template<typename T, typename>
    friend class FileProcessor;
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
    template<typename T, typename>
    friend class FileProcessor;
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
    template<typename T, typename>
    friend class FileProcessor;
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
    template<typename T, typename>
    friend class FileProcessor;
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
    template<typename T, typename>
    friend class FileProcessor;
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
	template<typename T, typename>
	friend class FileProcessor;
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
    template<typename T, typename>
    friend class FileProcessor;
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


template<typename T, typename = std::enable_if_t<std::is_base_of_v<File, T>>>
class FileProcessor {
public:
    // Constructor
    FileProcessor() {}

    // Process method
    static void Process(T& file) {
        // Process the file using a generic lambda
        auto processFile = [](auto&& file) {
            std::cout << "Open file with " << file.App << "? (y/n): ";
            char a;
            std::cin >> a;
            if(a=='y' || a=='Y'){
            	file.openApplication();
            }
            else return;
	};
        // Call the generic lambda to process the file
        processFile(std::forward<T>(file));
    }
};


// Define FileTypeTrait to determine if a type is a subclass of File
template<typename T>
struct FileTypeTrait {
    static constexpr bool value = std::is_base_of<File, T>::value;
};



// Define the FileTypeToFile template
template <FileType FileTypeValue>
struct FileTypeToFile;

// Specialization of FileTypeToFile template for each FileType value
template <>
struct FileTypeToFile<FileType::Text> {
    using type = Text;
};

template <>
struct FileTypeToFile<FileType::PNG> {
    using type = PNG;
};

template <>
struct FileTypeToFile<FileType::JPG> {
    using type = JPG;
};

template <>
struct FileTypeToFile<FileType::BMP> {
    using type = BMP;
};

template <>
struct FileTypeToFile<FileType::MP3> {
    using type = MP3;
};

template <>
struct FileTypeToFile<FileType::MP4> {
    using type = MP4;
};

template <>
struct FileTypeToFile<FileType::ZIP> {
    using type = ZIP;
};

template <>
struct FileTypeToFile<FileType::PDF> {
    using type = PDF;
};


class FileScorer {
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
    
	template<typename... Types>
	    static FileType getMaxScoredFileType(int (&scores)[static_cast<int>(FileType::Count)]) {
		FileType maxType = FileType::PNG; // Initialize with a default value
		int maxScore = -1;
		for (int i = 0; i < static_cast<int>(FileType::Count); ++i) {
		    if (scores[i] > maxScore) {
		        maxScore = scores[i];
		        maxType = static_cast<FileType>(i);
		    }
		}
		return maxType;
	    }
    // Scoring Algorithm
    static void score(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file: " << filename << std::endl;
            return;
        }

        std::cout << "Scoring file: " << filename << std::endl;

        // Array to store scores for each file type
        int scores[static_cast<int>(FileType::Count)] = {0};

        // Read the first few bytes to match magic numbers
        const int maxMagicNumberLength = getMaxMagicNumberLength();
        char magicNumberBuffer[maxMagicNumberLength] = {0};
        file.read(magicNumberBuffer, maxMagicNumberLength);

        // Check magic numbers and update scores
        for (int i = 0; i < static_cast<int>(FileType::Count); ++i) {
            FileType type = static_cast<FileType>(i);
            std::string magicNumber = getMagicNumber(type);
            int magicNumberLength = magicNumber.length();
            std::string bufferHex = "";
            for (int j = 0; j < magicNumberLength; ++j) {
                bufferHex += byteToHexString(magicNumberBuffer[j]);
            }
            bufferHex = bufferHex.substr(0, (magicNumber.size()/2)*2);
            if (magicNumberLength > 0 &&
                magicNumberLength <= maxMagicNumberLength &&
                bufferHex == magicNumber) {
                scores[i] += 200;
            }
        }

        // Reset file position to beginning
        file.seekg(0);
	/*
        // Get the total size of the file
	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// Initialize variables for tracking progress
	long long bytesProcessed = 0;
	int lastPercentage = -1;

	// Loop until end of file
	while (file.peek() != EOF) {
	    // Display progress percentage
	    bytesProcessed = file.tellg();
	    int currentPercentage = static_cast<int>((bytesProcessed * 100) / fileSize);
	    if (currentPercentage != lastPercentage) {
		std::cout << "Progress: " << currentPercentage << "%" << std::endl;
		lastPercentage = currentPercentage;
	    }

	    // Perform marker checks
	    checkMarker(file, PNG::fileMarkers, scores, FileType::PNG);
	    checkMarker(file, JPG::fileMarkers, scores, FileType::JPG);
	    checkMarker(file, BMP::fileMarkers, scores, FileType::BMP);
	    checkMarker(file, MP3::fileMarkers, scores, FileType::MP3);
	    checkMarker(file, MP4::fileMarkers, scores, FileType::MP4);
	    checkMarker(file, ZIP::fileMarkers, scores, FileType::ZIP);
	    checkMarker(file, PDF::fileMarkers, scores, FileType::PDF);
	}
	*/
	
	char byte;

        while (file.get(byte)) {
            std::string byteStr(1, byte); // Convert char to string
            checkMarker(byteStr, PNG::fileMarkers, scores, FileType::PNG);
            checkMarker(byteStr, JPG::fileMarkers, scores, FileType::JPG);
            checkMarker(byteStr, BMP::fileMarkers, scores, FileType::BMP);
            checkMarker(byteStr, MP3::fileMarkers, scores, FileType::MP3);
            checkMarker(byteStr, MP4::fileMarkers, scores, FileType::MP4);
            checkMarker(byteStr, ZIP::fileMarkers, scores, FileType::ZIP);
            checkMarker(byteStr, PDF::fileMarkers, scores, FileType::PDF);
        }


        // Print scores
        for (int i = 0; i < static_cast<int>(FileType::Count); ++i) {
            std::cout << "Score for " << getFileTypeName(static_cast<FileType>(i)) << ": " << scores[i] << std::endl;
        }

        file.close();
        
    // Get the FileType with the maximum score
    FileType maxScoredType = getMaxScoredFileType(scores);

    // Create an object of the appropriate class based on the FileType
    switch (maxScoredType) {
        case FileType::PNG:{
            PNG pngFile(filename);
            FileProcessor<PNG>::Process(pngFile);
            break;
            }
        case FileType::JPG:{
            JPG jpgFile(filename);
            FileProcessor<JPG>::Process(jpgFile);
            break;
            }
        case FileType::BMP:{
            BMP bmpFile(filename);
            FileProcessor<BMP>::Process(bmpFile);
            break;
            }
        case FileType::MP3:{
            MP3 mp3File(filename);
            FileProcessor<MP3>::Process(mp3File);
            break;
            }
        case FileType::MP4:{
            MP4 mp4File(filename);
            FileProcessor<MP4>::Process(mp4File);
            break;
            }
        case FileType::ZIP:{
            ZIP zipFile(filename);
            FileProcessor<ZIP>::Process(zipFile);
            break;
            }
        case FileType::PDF:{
            PDF pdfFile(filename);
            FileProcessor<PDF>::Process(pdfFile);
            break;
            }
    }
}
private:
    // Helper function to convert byte to hexadecimal string
    static std::string byteToHexString(unsigned char byte) {
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        return ss.str();
    }

    //checkMarker function
    /*
    static void checkMarker(std::ifstream& file, const Map<std::string, std::string>& markers, int scores[], FileType type) {
    std::streampos originalPos = file.tellg(); // Save original file position
    for (auto it = markers.begin(); it != markers.end(); it++) {
        std::string marker = (*it).value;
        int markerLength = marker.length();
        std::string bufferHex;
        char byte;
        bool match = true;
        for (int j = 0; j < markerLength; ++j) {
            if (!file.get(byte)) {
                match = false; // Unable to read enough bytes from the file
                break;
            }
            bufferHex += byteToHexString(byte);
        }
        bufferHex = bufferHex.substr(0, (marker.size()/2)*2);
        //std::cout<<"Marker:"<<marker<<"\t"<<"buffer:"<<bufferHex<<std::endl;
        if (match && bufferHex == marker) {
            scores[static_cast<int>(type)]++;
            break; // Exit loop after the first match
        }
        // Move the file pointer back to its original position
        file.seekg(originalPos);
    }
}
*/

	static void checkMarker(const std::string& byte, const Map<std::string, std::string>& markers, int scores[], FileType type) {
	    for (auto it = markers.begin(); it != markers.end(); it++) {
		std::string marker = (*it).value;
		int markerLength = marker.length();
		std::string bufferHex = "";
		for (int j = 0; j < markerLength; ++j) {
		    bufferHex += byteToHexString(marker[j]);
		}
		bufferHex = bufferHex.substr(0, (markerLength / 2) * 2);
		std::string byteHex = byteToHexString(byte[0]);
		if (bufferHex.find(byteHex) != std::string::npos) {
		    scores[static_cast<int>(type)]++;
		    break; // Exit loop after the first match
		}
	    }
	}



    static std::string getFileTypeName(FileType type) {
        switch (type) {
            case FileType::PNG: return "PNG";
            case FileType::JPG: return "JPG";
            case FileType::BMP: return "BMP";
            case FileType::MP3: return "MP3";
            case FileType::MP4: return "MP4";
            case FileType::ZIP: return "ZIP";
            case FileType::PDF: return "PDF";
            default: return "Unknown";
        }
    }

    static std::string getMagicNumber(FileType type) {
        switch (type) {
            case FileType::PNG: return PNG::magicNumber;
            case FileType::JPG: return JPG::magicNumber;
            case FileType::BMP: return BMP::magicNumber;
            case FileType::MP3: return MP3::magicNumber;
            case FileType::MP4: return MP4::magicNumber;
            case FileType::ZIP: return ZIP::magicNumber;
            case FileType::PDF: return PDF::magicNumber;
            default: return ""; // No magic number for other file types
        }
    }

    static int getMaxMagicNumberLength() {
        // Get the maximum magic number length among all supported file types
        int maxMagicNumberLength = 0;
        maxMagicNumberLength = std::max(maxMagicNumberLength, static_cast<int>(PNG::magicNumber.length()));
        maxMagicNumberLength = std::max(maxMagicNumberLength, static_cast<int>(JPG::magicNumber.length()));
        maxMagicNumberLength = std::max(maxMagicNumberLength, static_cast<int>(BMP::magicNumber.length()));
        maxMagicNumberLength = std::max(maxMagicNumberLength, static_cast<int>(ZIP::magicNumber.length()));
        maxMagicNumberLength = std::max(maxMagicNumberLength, static_cast<int>(PDF::magicNumber.length()));
        return maxMagicNumberLength;
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

    for(auto &i : files){
    	FileScorer::score(i);
    }
    return 0;
}

