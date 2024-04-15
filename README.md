**File Metadata Analyzer** <br />
The File Metadata Analyzer is a tool designed to determine file types by analyzing the headers of the files and comparing them with known file headers. This project supports the identification of the following file types: Text, PNG, JPG, BMP, MP3, MP4, ZIP, HTML, and PDF.

*Features*
File Type Detection: The tool filters out invalid files and scores the inputted files based on possible file types. Bytes of the file are read and matched with known headers of existing file types, resulting in a list of scores for each file. The file type with the highest score is determined to be the most likely type of the file.

Enhanced Accuracy: Unlike simple Magic Number mapping, which can be tampered with using a hex editor, this tool offers a more effective method for file type identification by considering various factors beyond just the magic number.

Support for Extensionless Files: The tool is capable of determining file types for files that do not have extensions, providing more comprehensive analysis capabilities.

Application Suggestions: The tool suggests applications with which the file can be opened, based on its determined type. This feature enhances user convenience by providing direct access to appropriate applications for different file types.

*Usage*
To use the File Metadata Analyzer, follow these steps:

Input Files: Provide the absolute file paths of the files you want to analyze as command-line arguments.

File Analysis: The tool will analyze each file, determine its type, and provide a list of scores for each file type.

Application Suggestions: Based on the determined file type, the tool will suggest applications with which the file can be opened.

*Example Usage*
./a.out file1 file2 file3






