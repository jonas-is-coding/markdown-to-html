#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <sstream>
#include <vector>
#include <regex>

#include "types.h"

class MarkdownConverter {
public:
    std::string convertToHTML(const std::string &markdown) {
        std::string html;
        std::istringstream stream(markdown);
        std::string line;

        bool inList = false;

        while (std::getline(stream, line)) {
            MarkdownLineType lineType = getLineType(line);

            switch (lineType) {
                case MarkdownLineType::Heading1:
                    html += "<h1>" + line.substr(2) + "</h1>\n";
                    break;
                case MarkdownLineType::Heading2:
                    html += "<h2>" + line.substr(3) + "</h2>\n";
                    break;
                case MarkdownLineType::Heading3:
                    html += "<h3>" + line.substr(4) + "</h3>\n";
                    break;
                case MarkdownLineType::Heading4:
                    html += "<h4>" + line.substr(5) + "</h4>\n";
                    break;
                case MarkdownLineType::Heading5:
                    html += "<h5>" + line.substr(6) + "</h5>\n";
                    break;
                case MarkdownLineType::Heading6:
                    html += "<h6>" + line.substr(7) + "</h6>\n";
                    break;
                case MarkdownLineType::Empty:
                    checkLine(html, inList);
                    html += "<br>\n";
                    break;
                case MarkdownLineType::Link: {
                    std::regex linkRegex(R"(\[(.+?)\]\((.+?)\))");
                    line = std::regex_replace(line, linkRegex, "<a href=\"$2\">$1</a>");
                }
                    html += line;
                    break;
                case MarkdownLineType::ListItem:
                    if (line.substr(0, 2) == "- ") {
                        if (!inList) {
                            html += "<ul>\n";
                            inList = true;
                        }
                        html += "<li>" + line.substr(2) + "</li>\n";
                    } else if (std::isdigit(line[0]) && line[1] == '.') {
                        if (!inList) {
                            html += "<ol>\n";
                            inList = true;
                        }
                        html += "<li>" + line.substr(line.find_first_of(' ') + 1) + "</li>\n";
                    } else {
                        checkLine(html, inList);
                        html += "<p>" + line + "</p>\n";
                    }
                    break;
                case MarkdownLineType::Paragraph:
                    html += "<p>" + line + "</p>\n";
                    break;
                default:
                    break;
            }
        }

        checkLine(html, inList);
        return html;
    }

private:
    void checkLine(std::string &html, bool &inList) {
        if (inList) {
            html += "</ul>\n";
            inList = false;
        }
    }
};

#endif