#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>

template<typename T, typename... Ts>
struct is_one_of : std::disjunction<std::is_same<T, Ts>...> {};


enum class FileType {
    Unknown,
    Text,
    Image,
    Archive,
    Audio,
    Video,
    Executable,
    PDF,
    Word,
    PowerPoint,
    Excel
};

template<typename T>
struct FileTypeDetector;

template<>
struct FileTypeDetector<std::ifstream> {
    static FileType detect(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
            return FileType::Unknown;

        char magic_number[4]; 
        file.read(magic_number, sizeof(magic_number));

        std::cout << "Magic number: ";
        for(auto i : magic_number) {
            std::cout << std::hex << (int)(unsigned char)i << " "; /
        }
        std::cout << std::endl;

        
        if (magic_number[0] == '\x51' && magic_number[1] == '\x4B' && magic_number[2] == '\x03' && magic_number[3] == '\x04')
            return FileType::Archive; // ZIP file
        else if (magic_number[0] == '\xFF' && magic_number[1] == '\xD8' && magic_number[2] == '\xFF')
            return FileType::Image; // JPEG file
        else if (magic_number[0] == '\x49' && magic_number[1] == '\x44' && magic_number[2] == '\x33' && magic_number[3] == '\x03')
            return FileType::Audio; // MP3 file
        else if (magic_number[0] == '\x66' && magic_number[1] == '\x74' && magic_number[2] == '\x79' && magic_number[3] == '\x70')
            return FileType::Audio; // MP4 file
        else if (magic_number[0] == '\x89' && magic_number[1] == '\x50' && magic_number[2] == '\x4E' && magic_number[3] == '\x47')
            return FileType::Image; // PNG file
        else if (magic_number[0] == 'I' && magic_number[1] == 'I' && magic_number[2] == '\x00' && magic_number[3] == '\x10')
            return FileType::Executable; // EXE file
        else if (magic_number[0] == '\x25' && magic_number[1] == '\x50' && magic_number[2] == '\x44' && magic_number[3] == '\x46')
            return FileType::PDF; // PDF file
        else if (magic_number[0] == 'd' && magic_number[1] == 'o' && magic_number[2] == 'c' && magic_number[3] == 'x')
            return FileType::Word; // DOCX file
        else if (magic_number[0] == '\x50' && magic_number[1] == '\x4B' && magic_number[2] == '\x03' && magic_number[3] == '\x04')
            return FileType::PowerPoint; // PPTX file
        else if (magic_number[0] == 'x' && magic_number[1] == 'l' && magic_number[2] == 's' && magic_number[3] == 'x')
            return FileType::Excel; // XLSX file
        else
            std :: cout << "unknown"<<std::endl;
            return FileType::Unknown;
    }
};

template<FileType type>
struct FileOpener;

template<>
struct FileOpener<FileType::Archive> {
    static void suggest() {
        std::cout << "Open with file archiver" << std::endl;
    }
};

template<>
struct FileOpener<FileType::Image> {
    static void suggest() {
        std::cout << "Open with image viewer" << std::endl;
        std::string command = "xdg-open ";
        command += "/home/pes1ug21cs188/Desktop/Project/image1"; 
        int result = std::system(command.c_str());
        if (result != 0) {
            std::cerr << "Error: Failed to open the image file with Preview." << std::endl;
        }
    }
};

template<>
struct FileOpener<FileType::Audio> {
    static void suggest() {
        std::cout << "Open with media player" << std::endl;
        std::string command = "xdg-open ";
        command += "/home/pes1ug21cs188/Desktop/Project/video.mp4"; 
        int result = std::system(command.c_str());
        if (result != 0) {
            std::cerr << "Error: Failed to open the image file with Preview." << std::endl;
    }
  }
};

template<>
struct FileOpener<FileType::Executable> {
    static void suggest() {
        std::cout << "Open with system's default program" << std::endl;
    }
};

template<>
struct FileOpener<FileType::PDF> {
    static void suggest() {
        std::cout << "Open with PDF reader" << std::endl;
    }
};

template<>
struct FileOpener<FileType::Word> {
    static void suggest() {
        std::cout << "Open with word processor" << std::endl;
    }
};

template<>
struct FileOpener<FileType::PowerPoint> {
    static void suggest() {
        std::cout << "Open with image viewer" << std::endl;
        std::string command = "libreoffice --impress ";
        command += "/home/pes1ug21cs188/Desktop/Project/slides.odp"; 
        int result = std::system(command.c_str());
        if (result != 0) {
            std::cerr << "Error: Failed to open the image file with Preview." << std::endl;
        }
    }
};

template<>
struct FileOpener<FileType::Excel> {
    static void suggest() {
        std::cout << "Open with spreadsheet software" << std::endl;
    }
};

// Function to analyze file metadata
template<typename T>
void analyze_file(const std::string& filename) {
    FileType type = FileTypeDetector<T>::detect(filename);
    switch (type) {
        case FileType::Archive:
            FileOpener<FileType::Archive>::suggest();
            break;
        case FileType::Image:
            FileOpener<FileType::Image>::suggest();
            break;
        case FileType::Audio:
            FileOpener<FileType::Audio>::suggest();
            break;
        case FileType::Executable:
            FileOpener<FileType::Executable>::suggest();
            break;
        case FileType::PDF:
            FileOpener<FileType::PDF>::suggest();
            break;
        case FileType::Word:
            FileOpener<FileType::Word>::suggest();
            break;
        case FileType::PowerPoint:
            FileOpener<FileType::PowerPoint>::suggest();
            break;
        case FileType::Excel:
            FileOpener<FileType::Excel>::suggest();
            break;
        default:
            std::cout << "Unknown file type" << std::endl;
            break;
    }
}

int main() {
    // analyze_file<std::ifstream>("example.txt");
    analyze_file<std::ifstream>("/home/pes1ug21cs188/Desktop/Project/image1");
    // analyze_file<std::ifstream>("example.mp3");
    // analyze_file<std::ifstream>("example.zip");
     //analyze_file<std::ifstream>("/home/pes1ug21cs188/Desktop/Project/video.mp4");
    // analyze_file<std::ifstream>("/Users/diyam1/Desktop/GP/Project/ex1.png");
    // analyze_file<std::ifstream>("example.mov");
    // analyze_file<std::ifstream>("example.exe");
    // analyze_file<std::ifstream>("example.pdf");
    // analyze_file<std::ifstream>("example.docx");
    //analyze_file<std::ifstream>("/home/pes1ug21cs188/Desktop/Project/slides.odp");
    // analyze_file<std::ifstream>("example.xlsx");
    return 0;
}
