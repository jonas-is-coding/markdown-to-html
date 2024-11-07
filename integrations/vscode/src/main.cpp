#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include "../include/converter.hpp"

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;

    if (file) {
        buffer << file.rdbuf(); 
        return buffer.str(); 
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return "";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <markdown-file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string markdownContent = readFile(filename);

    if (markdownContent.empty()) {
        std::cerr << "Fehler beim Lesen des Markdown-Inhalts." << std::endl;
        return 1;
    }

    MarkdownConverter converter;
    std::string htmlContent = converter.convertToHTML(markdownContent);

    std::filesystem::path inputPath(filename);
    std::string outputFilename = (inputPath.parent_path() / (inputPath.stem().string() + ".html")).string();
    std::ofstream outFile(outputFilename);

    if (outFile) {
        outFile << htmlContent;
        std::cout << "HTML file generated: " << outputFilename << std::endl;
    } else {
        std::cerr << "An error occurred while generating the file: " << outputFilename << std::endl;
    }

    return 0;
}