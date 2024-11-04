#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/converter.h"

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
    std::filesystem::path outputPath("./dist");

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <markdown-file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string markdownContent = readFile(filename);

    MarkdownConverter converter;
    std::string htmlContent = converter.convertToHTML(markdownContent);

    std::filesystem::path inputPath(filename);
    std::string outputFilename = (outputPath / (inputPath.stem().string() + ".html")).string();
    std::ofstream outFile(outputFilename);

    if (outFile) {
        outFile << htmlContent;
        std::cout << "HTML file generated: " << outputFilename << std::endl;
    } else {
        std::cerr << "An error occured while generating the file: " << outputFilename << std::endl;
    }

    return 0;
}