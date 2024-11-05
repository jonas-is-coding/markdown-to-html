#ifndef TYPES_H
#define TYPES_H

enum class MarkdownLineType
{
    Heading1,
    Heading2,
    Heading3,
    Heading4,
    Heading5,
    Heading6,
    Paragraph,
    ListItem,
    Link,
    Bold,
    Italic,
    InlineCode,
    CodeBlock,
    Empty,
    Unknown
};

MarkdownLineType getLineType(const std::string &line)
{
    // Headings
    if (line.rfind("# ", 0) == 0)
        return MarkdownLineType::Heading1;
    if (line.rfind("## ", 0) == 0)
        return MarkdownLineType::Heading2;
    if (line.rfind("### ", 0) == 0)
        return MarkdownLineType::Heading3;
    if (line.rfind("#### ", 0) == 0)
        return MarkdownLineType::Heading4;
    if (line.rfind("##### ", 0) == 0)
        return MarkdownLineType::Heading5;
    if (line.rfind("###### ", 0) == 0)
        return MarkdownLineType::Heading6;
    // List Items
    if (line.rfind("- ", 0) == 0)
        return MarkdownLineType::ListItem;
    // Links
    std::regex linkRegex(R"(\[(.+?)\]\((.+?)\))");
    if (std::regex_search(line, linkRegex))
    {
        return MarkdownLineType::Link;
    }
    // Bold and Italic
    std::regex boldRegex(R"((\*\*|__)(.*?)\1)");
    if (std::regex_search(line, boldRegex))
    {
        return MarkdownLineType::Bold;
    }
    std::regex italicRegex(R"((\*|_)(.*?)\1)");
    if (std::regex_search(line, italicRegex))
    {
        return MarkdownLineType::Italic;
    }
    // Code Blocks and Inline Code
    if (line.rfind("```", 0) == 0)
    {
        return MarkdownLineType::CodeBlock;
    }
    std::regex inlineCodeRegex(R"(`(.+?)`)");
    if (std::regex_search(line, inlineCodeRegex))
    {
        return MarkdownLineType::InlineCode;
    }
    // Empty Line
    if (line.empty())
        return MarkdownLineType::Empty;
    // Paragraph
    return MarkdownLineType::Paragraph;
}

#endif