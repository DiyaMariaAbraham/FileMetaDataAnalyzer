#include <iostream>
#include <string>
#include <fstream>
#include <type_traits>

// Type traits for file types
template<typename T>
struct is_image_file : std::false_type {};

template<typename T>
struct is_text_file : std::false_type {};

template<>
struct is_image_file<std::string> : std::true_type {};

template<>
struct is_text_file<std::string> : std::true_type {};

// Template for file metadata analyzer
template<typename... Args>
class FileMetaDataAnalyzer {
public:
    // Constructor
    FileMetaDataAnalyzer(Args... args) : metadata(args...) {}

    // Analyze method using fold expression
    void analyze() {
        std::cout << "Analyzing file metadata..." << std::endl;
        process_metadata(metadata...);
    }

private:
    // Variadic tuple for storing metadata
    std::tuple<Args...> metadata;

    // Process metadata using lambda templates
    template<typename T>
    void process_metadata(const T& data) {
        // Example: Print metadata
        std::cout << "Metadata: " << data << std::endl;
    }

    // Process multiple metadata using fold expression
    template<typename... Ts>
    void process_metadata(const Ts&... data) {
        (process_metadata(data), ...);
    }
};

// Specialization for image files
template<>
class FileMetaDataAnalyzer<std::string> {
public:
    FileMetaDataAnalyzer(std::string filepath) : filepath(filepath) {}

    void analyze() {
        std::cout << "Analyzing image file: " << filepath << std::endl;
        // Additional image-specific analysis...
    }

private:
    std::string filepath;
};

// Specialization for text files
template<>
class FileMetaDataAnalyzer<std::ifstream> {
public:
    FileMetaDataAnalyzer(std::ifstream& file) : file(file) {}

    void analyze() {
        std::cout << "Analyzing text file..." << std::endl;
        // Additional text-specific analysis...
    }

private:
    std::ifstream& file;
};

// Template friendship example
template<typename... Args>
class FriendAnalyzer {
    template<typename... T>
    friend class FileMetaDataAnalyzer;
};

int main() {
    // Example usage
    FileMetaDataAnalyzer<std::string, std::ifstream> analyzer("image.jpg", std::ifstream("text.txt"));
    analyzer.analyze();

    return 0;
}
