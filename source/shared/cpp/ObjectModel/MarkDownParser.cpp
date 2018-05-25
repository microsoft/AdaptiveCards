#include "pch.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include "MarkDownParser.h"

using namespace AdaptiveSharedNamespace;

MarkDownParser::MarkDownParser(const std::string &txt) : m_text(txt), m_hasHTMLTag(false)
{
}

// transforms string to html
std::string MarkDownParser::TransformToHtml()
{
    if (m_text.empty())
    {
        return "<p></p>";
    }
    // begin parsing html blocks
    ParseBlock();

    // process further what is parsed before outputting 
    // html string
    m_parsedResult.Translate();

    //add block tags such as <p> <ul>
    m_parsedResult.AddBlockTags();

    m_hasHTMLTag = m_parsedResult.HasHtmlTags();
    return m_parsedResult.GenerateHtmlString();
}

bool MarkDownParser::HasHtmlTags()
{
    return m_hasHTMLTag;
}
// MarkDown is consisted of Blocks, this methods parses blocks
void MarkDownParser::ParseBlock()
{
    std::stringstream stream(EscapeText());
    EmphasisParser parser;
    while (!stream.eof())
    {
        parser.ParseBlock(stream);
    }
    m_parsedResult.AppendParseResult(parser.GetParsedResult());
}

std::string MarkDownParser::EscapeText()
{
    std::string escaped;

    for (std::string::size_type i = 0; i < m_text.length(); i++)
    {
        switch (m_text[i])
        {
        case '<':
            escaped += "&lt;";
            break;
        case '>':
            escaped += "&gt;";
            break;
        case '"':
            escaped += "&quot;";
            break;
        case '&':
            escaped += "&amp;";
            break;
        default:
            escaped += m_text[i];
            break;
        }
    }

    return escaped;
}
