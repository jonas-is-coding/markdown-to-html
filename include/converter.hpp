#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <sstream>
#include <vector>
#include <regex>

#include "types.hpp"

class MarkdownConverter
{
public:
    std::string convertToHTML(const std::string &markdown)
    {
        std::string html;
        std::istringstream stream(markdown);
        std::string line;
        bool inList = false;

        while (std::getline(stream, line))
        {
            MarkdownLineType lineType = getLineType(line);

            switch (lineType)
            {
            case MarkdownLineType::Heading1:
                html += "<h1>" + convertInlineFormatting(line.substr(2)) + "</h1>\n";
                break;
            case MarkdownLineType::Heading2:
                html += "<h2>" + convertInlineFormatting(line.substr(3)) + "</h2>\n";
                break;
            case MarkdownLineType::Heading3:
                html += "<h3>" + convertInlineFormatting(line.substr(4)) + "</h3>\n";
                break;
            case MarkdownLineType::Heading4:
                html += "<h4>" + convertInlineFormatting(line.substr(5)) + "</h4>\n";
                break;
            case MarkdownLineType::Heading5:
                html += "<h5>" + convertInlineFormatting(line.substr(6)) + "</h5>\n";
                break;
            case MarkdownLineType::Heading6:
                html += "<h6>" + convertInlineFormatting(line.substr(7)) + "</h6>\n";
                break;
            case MarkdownLineType::Empty:
                checkLine(html, inList);
                html += "<br>\n";
                break;
            case MarkdownLineType::Link:
            {
                std::regex linkRegex(R"(\[(.+?)\]\((.+?)\))");
                line = std::regex_replace(line, linkRegex, "<a href=\"$2\">$1</a>");
                html += convertInlineFormatting(line);
                break;
            }
            case MarkdownLineType::ListItem:
                if (line.substr(0, 2) == "- ")
                {
                    if (!inList)
                    {
                        html += "<ul>\n";
                        inList = true;
                    }
                    html += "<li>" + convertInlineFormatting(line.substr(2)) + "</li>\n";
                }
                else
                {
                    checkLine(html, inList);
                    html += "<p>" + convertInlineFormatting(line) + "</p>\n";
                }
                break;
            case MarkdownLineType::Bold:
            {
                std::regex boldRegex(R"((\*\*|__)(.*?)\1)");
                html += std::regex_replace(convertInlineFormatting(line), boldRegex, "<strong>$2</strong>\n");
                break;
            }
            case MarkdownLineType::Italic:
            {
                std::regex italicRegex(R"(\*(.+?)\*)");
                html += std::regex_replace(convertInlineFormatting(line), italicRegex, "<em>$1</em>\n");
                break;
            }
            case MarkdownLineType::CodeBlock:
                html += "<pre><code>";
                while (std::getline(stream, line))
                {
                    if (line.rfind("```", 0) == 0)
                    {
                        html += "</code></pre>\n";
                        break;
                    }
                    html += convertInlineFormatting(line) + "\n";
                }
                break;
            case MarkdownLineType::InlineCode:
            {
                std::regex codeRegex(R"(`(.+?)`)");
                html += std::regex_replace(convertInlineFormatting(line), codeRegex, "<code>$1</code>");
                break;
            }
            case MarkdownLineType::Paragraph:
                html += "<p>" + convertInlineFormatting(line) + "</p>\n";
                break;
            default:
                break;
            }
        }

        checkLine(html, inList);
        return html;
    }

private:
    void checkLine(std::string &html, bool &inList)
    {
        if (inList)
        {
            html += "</ul>\n";
            inList = false;
        }
    }

    std::string convertInlineFormatting(const std::string &line)
    {
        std::string formatted = line;

        std::regex boldRegex(R"((\*\*|__)(.*?)\1)");
        formatted = std::regex_replace(formatted, boldRegex, "<strong>$2</strong>");

        std::regex italicRegex(R"((\*|_)(.*?)\1)");
        formatted = std::regex_replace(formatted, italicRegex, "<em>$2</em>");

        std::regex codeRegex(R"(`(.+?)`)");
        formatted = std::regex_replace(formatted, codeRegex, "<code>$1</code>");

        return formatted;
    }
};

#endif