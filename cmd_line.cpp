#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
#include <cstdlib>

using namespace std;

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
    Excel,
    XML
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
            std::cout << std::hex << (int)(unsigned char)i << " "; 
        }
        std::cout << std::endl;

        // Check magic numbers or other criteria to determine file type
        if (magic_number[0] == '\x51' && magic_number[1] == '\x4B' && magic_number[2] == '\x03' && magic_number[3] == '\x04')
            return FileType::Archive; // ZIP file
        else if (magic_number[0] == '\xFF' && magic_number[1] == '\xD8' && magic_number[2] == '\xFF')
            return FileType::Image; // JPEG file
        else if (magic_number[0] == '\x49' && magic_number[1] == '\x44' && magic_number[2] == '\x33' && magic_number[3] == '\x04')
            return FileType::Audio; // MP3 file
        else if (magic_number[0] == '\x66' && magic_number[1] == '\x74' && magic_number[2] == '\x79' && magic_number[3] == '\x70')
            return FileType::Audio; // MP4 file
        else if (magic_number[0] == '\x89' && magic_number[1] == '\x50' && magic_number[2] == '\x4E' && magic_number[3] == '\x47')
            return FileType::Image; // PNG file
        else if (magic_number[0] == '\x3C' && magic_number[1] == '\x6E' && magic_number[2] == '\x6F' && magic_number[3] == '\x74')
            return FileType::Executable; // XML file
        else if (magic_number[0] == '\x25' && magic_number[1] == '\x50' && magic_number[2] == '\x44' && magic_number[3] == '\x46')
            return FileType::PDF; // PDF file
        else if (magic_number[0] == '\x3C' && magic_number[1] == '\x48' && magic_number[2] == '\x74' && magic_number[3] == '\x6D')
            return FileType::Executable; // HTML file
        else if (magic_number[0] == '\x50' && magic_number[1] == '\x4B' && magic_number[2] == '\x03' && magic_number[3] == '\x04')
            return FileType::PowerPoint; // ODP file
        else if (magic_number[0] == 'x' && magic_number[1] == 'l' && magic_number[2] == 's' && magic_number[3] == 'x')
            return FileType::Excel; // XLSX file
        else
            std :: cout << "unknown"<<std::endl;
            return FileType::Unknown;
    }
};

// Suggestions for opening different file types
template<FileType type>
struct FileOpener;

template<>
struct FileOpener<FileType::Archive> {
    static void suggest(const std::string& filename) {
        std::cout << "Open with file archiver" << std::endl;
    }
};

template<>
struct FileOpener<FileType::Image> {
    static void suggest(const std::string& filename) {
        char response;
        std::cout << "Do you want to open with the image viewer? (y/n): ";
        std::cin >> response;
        if (std::tolower(response) == 'y') {
            std::string command = "eog " + filename;
            int result = std::system(command.c_str());
            if (result != 0) {
                std::cerr << "Error: Failed to open the image file with Preview." << std::endl;
            }
        }
    }
};

template<>
struct FileOpener<FileType::Audio> {
    static void suggest(const std::string& filename) {
        std::cout << "Open with media player" << std::endl;
        char response;
        std::cout << "Do you want to open with the Videos? (y/n): ";
        std::cin >> response;
        if (std::tolower(response) == 'y'){
            std::string command = "totem " + filename;
            int result = std::system(command.c_str());
            if (result != 0) {
                std::cerr << "Error: Failed to open the image file with Preview." << std::endl;
            }
        }
    }
};

template<>
struct FileOpener<FileType::Executable> {
    static void suggest(const std::string& filename) {
        char response;
        std::cout << "How do you want to open the file?" << std::endl;
        std::cout << "1. Open with a text editor" << std::endl;
        std::cout << "2. Open with Firefox" << std::endl;
        std::cout << "3. Open with Vim" << std::endl;
        std::cout << "Enter your choice (1/2/3): ";
        std::cin >> response;

        switch (response) {
            case '1': {
                std::string command = "nano " + filename; // Open with gedit
                int result = std::system(command.c_str());
                if (result != 0) {
                    std::cerr << "Error: Failed to open the file with gedit." << std::endl;
                }
                break;
            }
            case '2': {
                std::string command = "firefox " + filename; // Open with Firefox
                int result = std::system(command.c_str());
                if (result != 0) {
                    std::cerr << "Error: Failed to open the file with Firefox." << std::endl;
                }
                break;
            }
            case '3': {
                std::string command = "vim " + filename; // Open with Vim
                int result = std::system(command.c_str());
                if (result != 0) {
                    std::cerr << "Error: Failed to open the file with Vim." << std::endl;
                }
                break;
            }
            default:
                std::cerr << "Invalid choice" << std::endl;
                break;
        }
    }
};

template<>
struct FileOpener<FileType::PDF> {
    static void suggest(const std::string& filename) {
        char response;
        std::cout << "Do you want to open with the Document viewer? (y/n): ";
        std::cin >> response;
        if (std::tolower(response) == 'y'){
            std::string command = "evince " + filename;
            int result = std::system(command.c_str());
            if (result != 0) {
                std::cerr << "Error: Failed to open the pdf file." << std::endl;
            }
        }
    }
};

template<>
struct FileOpener<FileType::Word> {
    static void suggest(const std::string& filename) {
        std::cout << "Open with word processor" << std::endl;
    }
};

template<>
struct FileOpener<FileType::PowerPoint> {
    static void suggest(const std::string& filename) {
        char response;
        std::cout << "Do you want to open with the LibreOffice? (y/n): ";
        std::cin >> response;
        if (std::tolower(response) == 'y'){
            std::string command = "libreoffice --impress " + filename;
            int result = std::system(command.c_str());
            if (result != 0) {
                std::cerr << "Error: Failed to open the image file with Preview." << std::endl;
            }
        }
    }
};

template<>
struct FileOpener<FileType::Excel> {
    static void suggest(const std::string& filename) {
        std::cout << "Open with spreadsheet software" << std::endl;
    }
};


// Function to analyze file metadata
template<typename T>
void analyze_file(const std::string& filename) {
    FileType type = FileTypeDetector<T>::detect(filename);
    switch (type) {
        case FileType::Archive:
            FileOpener<FileType::Archive>::suggest(filename);
            break;
        case FileType::Image:
            FileOpener<FileType::Image>::suggest(filename);
            break;
        case FileType::Audio:
            FileOpener<FileType::Audio>::suggest(filename);
            break;
        case FileType::Executable:
            FileOpener<FileType::Executable>::suggest(filename);
            break;
        case FileType::PDF:
            FileOpener<FileType::PDF>::suggest(filename);
            break;
        case FileType::Word:
            FileOpener<FileType::Word>::suggest(filename);
            break;
        case FileType::PowerPoint:
            FileOpener<FileType::PowerPoint>::suggest(filename);
            break;
        case FileType::Excel:
            FileOpener<FileType::Excel>::suggest(filename);
            break;
        default:
            std::cout << "Unknown file type" << std::endl;
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    analyze_file<std::ifstream>(filename);

    return 0;
}
