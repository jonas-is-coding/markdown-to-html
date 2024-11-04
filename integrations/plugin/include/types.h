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
    Empty,
    Unknown
};

MarkdownLineType getLineType(const std::string &line)
{
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
    if (line.rfind("- ", 0) == 0) 
        return MarkdownLineType::ListItem;
    std::regex linkRegex(R"(\[(.+?)\]\((.+?)\))");
    if (std::regex_search(line, linkRegex)) {
        return MarkdownLineType::Link;
    }
    if (line.empty())
        return MarkdownLineType::Empty;
    return MarkdownLineType::Paragraph;
}

#endif