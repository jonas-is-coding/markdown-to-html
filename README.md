# Markdown to HTML Converter

A fast and efficient C++ based Markdown to HTML converter with additional tools and integrations.

## Core Features

- Fast Markdown to HTML conversion using C++
- Support for standard Markdown syntax
- Minimal dependencies
- Command line interface
- Cross-platform compatibility (Windows, Linux, MacOS)

## Project Structure

```
markdown-converter/
├── src/                        # Core C++ source files
│   ├── main.cpp/               # C++ Source Code
│   └── markdown-converter/     # Executable File
├── include/                    # Header files
├── examples/                   # Example Files
├── tests/                      # Tests
└── integrations/               # IDE/Editor integrations
    └── vscode/                 # VS Code extension
```

## Building from Source

### Prerequisites

- C++17 compatible compiler
- CMake 3.15 or higher
- Make (on Unix systems) or Visual Studio (on Windows)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/markdown-converter

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
cmake --build .

# Run tests (optional)
ctest
```

## Usage

### Command Line

```bash
# Basic usage
./markdown-converter input.md output.html

# Show help
./markdown-converter --help

# Version information
./markdown-converter --version
```

### Using as a Library

```cpp
#include "markdown_converter.h"

int main() {
    MarkdownConverter converter;
    std::string markdown_content = "# Hello World\nThis is a test.";
    std::string html = converter.convert(markdown_content);
    return 0;
}
```

## Integrations

### VS Code Extension

A Visual Studio Code extension is available in the `integrations/vscode` directory. It provides a GUI interface for the converter within VS Code. See the extension's own README for detailed installation and usage instructions.

### Other IDEs/Editors

Contributions for integrations with other IDEs and text editors are welcome!

### Development Setup

1. Fork the repository
2. Set up the build environment as described above
3. Create a new branch for your feature
4. Make your changes
5. Run the tests
6. Submit a pull request

## Testing

```bash
# Run all tests
ctest

# Run specific test suite
ctest -R parser_tests

# Run tests with verbose output
ctest -V
```

## License

This project is licensed under the MIT License.

## Roadmap

- [ ] Support for extended Markdown syntax
- [ ] Custom style templates
- [ ] More editor integrations
- [ ] WebAssembly build
- [ ] Performance optimizations
- [ ] API for other programming languages

## Acknowledgments

- The CommonMark specification
- All contributors who have helped with code, bug reports, and suggestions

---

For questions and support, please open an issue in the GitHub repository.